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
struct vchiq_state {struct vchiq_service** services; } ;
struct vchiq_service {scalar_t__ srvstate; scalar_t__ ref_count; } ;

/* Variables and functions */
 unsigned int VCHIQ_PORT_MAX ; 
 scalar_t__ VCHIQ_SRVSTATE_FREE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  service_spinlock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchiq_core_log_level ; 
 int /*<<< orphan*/  vchiq_log_info (int /*<<< orphan*/ ,char*,int) ; 

struct vchiq_service *
find_service_by_port(struct vchiq_state *state, int localport)
{
	struct vchiq_service *service = NULL;

	if ((unsigned int)localport <= VCHIQ_PORT_MAX) {
		spin_lock(&service_spinlock);
		service = state->services[localport];
		if (service && (service->srvstate != VCHIQ_SRVSTATE_FREE)) {
			WARN_ON(service->ref_count == 0);
			service->ref_count++;
		} else
			service = NULL;
		spin_unlock(&service_spinlock);
	}

	if (!service)
		vchiq_log_info(vchiq_core_log_level,
			"Invalid port %d", localport);

	return service;
}