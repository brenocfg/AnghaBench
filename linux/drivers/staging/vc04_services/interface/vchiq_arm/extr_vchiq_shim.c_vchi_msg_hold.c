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
typedef  int /*<<< orphan*/  uint32_t ;
struct vchiq_header {int /*<<< orphan*/  size; void* data; } ;
struct vchi_held_msg {struct vchiq_header* message; struct opaque_vchi_service_t* service; } ;
struct shim_service {scalar_t__ handle; int /*<<< orphan*/  queue; } ;
struct opaque_vchi_service_t {int dummy; } ;
typedef  int int32_t ;
typedef  scalar_t__ VCHI_SERVICE_HANDLE_T ;
typedef  scalar_t__ VCHI_FLAGS_T ;

/* Variables and functions */
 scalar_t__ VCHI_FLAGS_BLOCK_UNTIL_OP_COMPLETE ; 
 scalar_t__ VCHI_FLAGS_NONE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ vchiu_queue_is_empty (int /*<<< orphan*/ *) ; 
 struct vchiq_header* vchiu_queue_pop (int /*<<< orphan*/ *) ; 

int32_t vchi_msg_hold(VCHI_SERVICE_HANDLE_T handle,
	void **data,
	uint32_t *msg_size,
	VCHI_FLAGS_T flags,
	struct vchi_held_msg *message_handle)
{
	struct shim_service *service = (struct shim_service *)handle;
	struct vchiq_header *header;

	WARN_ON((flags != VCHI_FLAGS_NONE) &&
		(flags != VCHI_FLAGS_BLOCK_UNTIL_OP_COMPLETE));

	if (flags == VCHI_FLAGS_NONE)
		if (vchiu_queue_is_empty(&service->queue))
			return -1;

	header = vchiu_queue_pop(&service->queue);

	*data = header->data;
	*msg_size = header->size;

	/*
	 * upcast the VCHIQ_SERVICE_HANDLE_T which is an int
	 * to a pointer and stuff it in the held message.
	 * This pointer is opaque to everything except
	 * vchi_held_msg_release which simply downcasts it back
	 * to an int.
	 */

	message_handle->service =
		(struct opaque_vchi_service_t *)(long)service->handle;
	message_handle->message = header;

	return 0;
}