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
struct vchiq_service_quota {int slot_use_count; int slot_quota; int message_quota; int message_use_count; int /*<<< orphan*/  quota_event; } ;
struct vchiq_service {int auto_close; size_t localport; int sync; int trace; int /*<<< orphan*/  srvstate; TYPE_1__* state; } ;
typedef  int /*<<< orphan*/  VCHIQ_STATUS_T ;
typedef  int VCHIQ_SERVICE_OPTION_T ;
typedef  int /*<<< orphan*/  VCHIQ_SERVICE_HANDLE_T ;
struct TYPE_2__ {int default_slot_quota; int default_message_quota; struct vchiq_service_quota* service_quotas; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCHIQ_ERROR ; 
#define  VCHIQ_SERVICE_OPTION_AUTOCLOSE 132 
#define  VCHIQ_SERVICE_OPTION_MESSAGE_QUOTA 131 
#define  VCHIQ_SERVICE_OPTION_SLOT_QUOTA 130 
#define  VCHIQ_SERVICE_OPTION_SYNCHRONOUS 129 
#define  VCHIQ_SERVICE_OPTION_TRACE 128 
 int /*<<< orphan*/  VCHIQ_SRVSTATE_HIDDEN ; 
 int /*<<< orphan*/  VCHIQ_SRVSTATE_LISTENING ; 
 int /*<<< orphan*/  VCHIQ_SUCCESS ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct vchiq_service* find_service_by_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_service (struct vchiq_service*) ; 

VCHIQ_STATUS_T
vchiq_set_service_option(VCHIQ_SERVICE_HANDLE_T handle,
	VCHIQ_SERVICE_OPTION_T option, int value)
{
	struct vchiq_service *service = find_service_by_handle(handle);
	VCHIQ_STATUS_T status = VCHIQ_ERROR;

	if (service) {
		switch (option) {
		case VCHIQ_SERVICE_OPTION_AUTOCLOSE:
			service->auto_close = value;
			status = VCHIQ_SUCCESS;
			break;

		case VCHIQ_SERVICE_OPTION_SLOT_QUOTA: {
			struct vchiq_service_quota *service_quota =
				&service->state->service_quotas[
					service->localport];
			if (value == 0)
				value = service->state->default_slot_quota;
			if ((value >= service_quota->slot_use_count) &&
				 (value < (unsigned short)~0)) {
				service_quota->slot_quota = value;
				if ((value >= service_quota->slot_use_count) &&
					(service_quota->message_quota >=
					 service_quota->message_use_count)) {
					/* Signal the service that it may have
					** dropped below its quota */
					complete(&service_quota->quota_event);
				}
				status = VCHIQ_SUCCESS;
			}
		} break;

		case VCHIQ_SERVICE_OPTION_MESSAGE_QUOTA: {
			struct vchiq_service_quota *service_quota =
				&service->state->service_quotas[
					service->localport];
			if (value == 0)
				value = service->state->default_message_quota;
			if ((value >= service_quota->message_use_count) &&
				 (value < (unsigned short)~0)) {
				service_quota->message_quota = value;
				if ((value >=
					service_quota->message_use_count) &&
					(service_quota->slot_quota >=
					service_quota->slot_use_count))
					/* Signal the service that it may have
					** dropped below its quota */
					complete(&service_quota->quota_event);
				status = VCHIQ_SUCCESS;
			}
		} break;

		case VCHIQ_SERVICE_OPTION_SYNCHRONOUS:
			if ((service->srvstate == VCHIQ_SRVSTATE_HIDDEN) ||
				(service->srvstate ==
				VCHIQ_SRVSTATE_LISTENING)) {
				service->sync = value;
				status = VCHIQ_SUCCESS;
			}
			break;

		case VCHIQ_SERVICE_OPTION_TRACE:
			service->trace = value;
			status = VCHIQ_SUCCESS;
			break;

		default:
			break;
		}
		unlock_service(service);
	}

	return status;
}