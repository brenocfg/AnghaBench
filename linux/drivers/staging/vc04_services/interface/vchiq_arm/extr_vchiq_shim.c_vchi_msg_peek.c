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
struct shim_service {int /*<<< orphan*/  queue; } ;
typedef  int int32_t ;
typedef  scalar_t__ VCHI_SERVICE_HANDLE_T ;
typedef  scalar_t__ VCHI_FLAGS_T ;

/* Variables and functions */
 scalar_t__ VCHI_FLAGS_BLOCK_UNTIL_OP_COMPLETE ; 
 scalar_t__ VCHI_FLAGS_NONE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ vchiu_queue_is_empty (int /*<<< orphan*/ *) ; 
 struct vchiq_header* vchiu_queue_peek (int /*<<< orphan*/ *) ; 

int32_t vchi_msg_peek(VCHI_SERVICE_HANDLE_T handle,
	void **data,
	uint32_t *msg_size,
	VCHI_FLAGS_T flags)
{
	struct shim_service *service = (struct shim_service *)handle;
	struct vchiq_header *header;

	WARN_ON((flags != VCHI_FLAGS_NONE) &&
		(flags != VCHI_FLAGS_BLOCK_UNTIL_OP_COMPLETE));

	if (flags == VCHI_FLAGS_NONE)
		if (vchiu_queue_is_empty(&service->queue))
			return -1;

	header = vchiu_queue_peek(&service->queue);

	*data = header->data;
	*msg_size = header->size;

	return 0;
}