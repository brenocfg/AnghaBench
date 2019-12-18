#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vchiq_state {struct vchiq_shared_state* remote; } ;
struct vchiq_slot_info {int dummy; } ;
struct vchiq_shared_state {int slot_first; int slot_last; int slot_sync; } ;
struct vchiq_service {struct vchiq_state* state; } ;
struct vchiq_header {int msgid; } ;
typedef  int /*<<< orphan*/  VCHIQ_SERVICE_HANDLE_T ;

/* Variables and functions */
 int SLOT_INDEX_FROM_DATA (struct vchiq_state*,void*) ; 
 struct vchiq_slot_info* SLOT_INFO_FROM_INDEX (struct vchiq_state*,int) ; 
 int VCHIQ_MSGID_CLAIMED ; 
 struct vchiq_service* find_service_by_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_message_sync (struct vchiq_state*,struct vchiq_header*) ; 
 int /*<<< orphan*/  release_slot (struct vchiq_state*,struct vchiq_slot_info*,struct vchiq_header*,struct vchiq_service*) ; 
 int /*<<< orphan*/  unlock_service (struct vchiq_service*) ; 

void
vchiq_release_message(VCHIQ_SERVICE_HANDLE_T handle,
		      struct vchiq_header *header)
{
	struct vchiq_service *service = find_service_by_handle(handle);
	struct vchiq_shared_state *remote;
	struct vchiq_state *state;
	int slot_index;

	if (!service)
		return;

	state = service->state;
	remote = state->remote;

	slot_index = SLOT_INDEX_FROM_DATA(state, (void *)header);

	if ((slot_index >= remote->slot_first) &&
		(slot_index <= remote->slot_last)) {
		int msgid = header->msgid;

		if (msgid & VCHIQ_MSGID_CLAIMED) {
			struct vchiq_slot_info *slot_info =
				SLOT_INFO_FROM_INDEX(state, slot_index);

			release_slot(state, slot_info, header, service);
		}
	} else if (slot_index == remote->slot_sync)
		release_message_sync(state, header);

	unlock_service(service);
}