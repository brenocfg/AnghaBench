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
struct TYPE_2__ {void* userdata; } ;
struct vchiq_service {TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  VCHIQ_SERVICE_HANDLE_T ;

/* Variables and functions */
 struct vchiq_service* handle_to_service (int /*<<< orphan*/ ) ; 

void *
vchiq_get_service_userdata(VCHIQ_SERVICE_HANDLE_T handle)
{
	struct vchiq_service *service = handle_to_service(handle);

	return service ? service->base.userdata : NULL;
}