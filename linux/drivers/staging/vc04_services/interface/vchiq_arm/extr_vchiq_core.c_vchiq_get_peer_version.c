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
struct vchiq_service {short peer_version; } ;
typedef  scalar_t__ VCHIQ_STATUS_T ;
typedef  int /*<<< orphan*/  VCHIQ_SERVICE_HANDLE_T ;

/* Variables and functions */
 scalar_t__ VCHIQ_ERROR ; 
 scalar_t__ VCHIQ_SUCCESS ; 
 struct vchiq_service* find_service_by_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_service (struct vchiq_service*) ; 
 scalar_t__ vchiq_check_service (struct vchiq_service*) ; 

VCHIQ_STATUS_T
vchiq_get_peer_version(VCHIQ_SERVICE_HANDLE_T handle, short *peer_version)
{
	VCHIQ_STATUS_T status = VCHIQ_ERROR;
	struct vchiq_service *service = find_service_by_handle(handle);

	if (!service ||
	    (vchiq_check_service(service) != VCHIQ_SUCCESS) ||
	    !peer_version)
		goto exit;
	*peer_version = service->peer_version;
	status = VCHIQ_SUCCESS;

exit:
	if (service)
		unlock_service(service);
	return status;
}