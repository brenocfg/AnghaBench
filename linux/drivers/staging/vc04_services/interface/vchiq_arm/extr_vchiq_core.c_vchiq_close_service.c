#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vchiq_service {size_t srvstate; int /*<<< orphan*/  localport; TYPE_1__* state; int /*<<< orphan*/  remove_event; } ;
typedef  scalar_t__ VCHIQ_STATUS_T ;
typedef  int /*<<< orphan*/  VCHIQ_SERVICE_HANDLE_T ;
struct TYPE_2__ {scalar_t__ slot_handler_thread; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ VCHIQ_ERROR ; 
 int /*<<< orphan*/  VCHIQ_POLL_TERMINATE ; 
 scalar_t__ VCHIQ_RETRY ; 
 size_t VCHIQ_SRVSTATE_FREE ; 
 size_t VCHIQ_SRVSTATE_HIDDEN ; 
 size_t VCHIQ_SRVSTATE_LISTENING ; 
 size_t VCHIQ_SRVSTATE_OPEN ; 
 scalar_t__ VCHIQ_SUCCESS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ current ; 
 struct vchiq_service* find_service_by_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_service_closing (struct vchiq_service*) ; 
 int /*<<< orphan*/  request_poll (TYPE_1__*,struct vchiq_service*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * srvstate_names ; 
 int /*<<< orphan*/  unlock_service (struct vchiq_service*) ; 
 scalar_t__ vchiq_close_service_internal (struct vchiq_service*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_core_log_level ; 
 int /*<<< orphan*/  vchiq_log_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_log_warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

VCHIQ_STATUS_T
vchiq_close_service(VCHIQ_SERVICE_HANDLE_T handle)
{
	/* Unregister the service */
	struct vchiq_service *service = find_service_by_handle(handle);
	VCHIQ_STATUS_T status = VCHIQ_SUCCESS;

	if (!service)
		return VCHIQ_ERROR;

	vchiq_log_info(vchiq_core_log_level,
		"%d: close_service:%d",
		service->state->id, service->localport);

	if ((service->srvstate == VCHIQ_SRVSTATE_FREE) ||
		(service->srvstate == VCHIQ_SRVSTATE_LISTENING) ||
		(service->srvstate == VCHIQ_SRVSTATE_HIDDEN)) {
		unlock_service(service);
		return VCHIQ_ERROR;
	}

	mark_service_closing(service);

	if (current == service->state->slot_handler_thread) {
		status = vchiq_close_service_internal(service,
			0/*!close_recvd*/);
		WARN_ON(status == VCHIQ_RETRY);
	} else {
	/* Mark the service for termination by the slot handler */
		request_poll(service->state, service, VCHIQ_POLL_TERMINATE);
	}

	while (1) {
		if (wait_for_completion_interruptible(&service->remove_event)) {
			status = VCHIQ_RETRY;
			break;
		}

		if ((service->srvstate == VCHIQ_SRVSTATE_FREE) ||
			(service->srvstate == VCHIQ_SRVSTATE_LISTENING) ||
			(service->srvstate == VCHIQ_SRVSTATE_OPEN))
			break;

		vchiq_log_warning(vchiq_core_log_level,
			"%d: close_service:%d - waiting in state %s",
			service->state->id, service->localport,
			srvstate_names[service->srvstate]);
	}

	if ((status == VCHIQ_SUCCESS) &&
		(service->srvstate != VCHIQ_SRVSTATE_FREE) &&
		(service->srvstate != VCHIQ_SRVSTATE_LISTENING))
		status = VCHIQ_ERROR;

	unlock_service(service);

	return status;
}