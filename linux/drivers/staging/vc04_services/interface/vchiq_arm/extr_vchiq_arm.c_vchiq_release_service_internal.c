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
struct vchiq_service {int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  VCHIQ_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  vchiq_release_internal (int /*<<< orphan*/ ,struct vchiq_service*) ; 

VCHIQ_STATUS_T
vchiq_release_service_internal(struct vchiq_service *service)
{
	return vchiq_release_internal(service->state, service);
}