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
struct vchiq_header {int dummy; } ;
struct shim_service {int /*<<< orphan*/  handle; int /*<<< orphan*/  queue; } ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  scalar_t__ VCHI_SERVICE_HANDLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  vchiq_release_message (int /*<<< orphan*/ ,struct vchiq_header*) ; 
 struct vchiq_header* vchiu_queue_pop (int /*<<< orphan*/ *) ; 

int32_t vchi_msg_remove(VCHI_SERVICE_HANDLE_T handle)
{
	struct shim_service *service = (struct shim_service *)handle;
	struct vchiq_header *header;

	header = vchiu_queue_pop(&service->queue);

	vchiq_release_message(service->handle, header);

	return 0;
}