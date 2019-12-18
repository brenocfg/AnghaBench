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
struct shim_service {int /*<<< orphan*/  handle; } ;
typedef  int int32_t ;
typedef  scalar_t__ VCHI_SERVICE_HANDLE_T ;
typedef  scalar_t__ VCHIQ_STATUS_T ;

/* Variables and functions */
 scalar_t__ VCHIQ_SUCCESS ; 
 int /*<<< orphan*/  service_free (struct shim_service*) ; 
 scalar_t__ vchiq_close_service (int /*<<< orphan*/ ) ; 
 int vchiq_status_to_vchi (scalar_t__) ; 

int32_t vchi_service_close(const VCHI_SERVICE_HANDLE_T handle)
{
	int32_t ret = -1;
	struct shim_service *service = (struct shim_service *)handle;

	if (service) {
		VCHIQ_STATUS_T status = vchiq_close_service(service->handle);
		if (status == VCHIQ_SUCCESS)
			service_free(service);

		ret = vchiq_status_to_vchi(status);
	}
	return ret;
}