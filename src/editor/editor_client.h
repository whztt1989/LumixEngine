#pragma once


#include "core/lumix.h"
#include "core/delegate_list.h"

namespace Lumix
{

	class EditorServer;
	struct Entity;
	struct EntityPositionEvent;
	struct EntitySelectedEvent;
	struct PropertyListEvent;
	struct ServerMessage;
	struct Vec3;

	class LUMIX_ENGINE_API EditorClient
	{
		public:
			typedef DelegateList<void(PropertyListEvent&)> PropertyListCallback;
			typedef DelegateList<void(EntitySelectedEvent&)> EntitySelectedCallback;
			typedef DelegateList<void(EntityPositionEvent&)> EntityPositionCallback;

		public:
			EditorClient() { m_impl = NULL; }

			bool create(const char* base_path, EditorServer& server);
			void destroy();
			void onMessage(const uint8_t* data, int size);
			void addEntity();
			void toggleGameMode();
			void lookAtSelected();
			void addComponent(uint32_t type);
			void mouseDown(int x, int y, int button);
			void mouseUp(int x, int y, int button);
			void mouseMove(int x, int y, int dx, int dy, int flags);
			void requestProperties(uint32_t type_crc);
			void setComponentProperty(const char* component, const char* property, const void* value, int32_t length);
			void navigate(float forward, float right, float speed);
			void loadUniverse(const char* path);
			void saveUniverse(const char* path);
			void setEntityPosition(int32_t entity, const Vec3& position);
			void setWireframe(bool is_wireframe);
			const char* getBasePath() const;
			PropertyListCallback& propertyListReceived();
			EntitySelectedCallback& entitySelected();
			EntityPositionCallback& entityPositionReceived();

		private:
			struct EditorClientImpl* m_impl;
	};

} // ~namespace Lumix