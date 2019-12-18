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
struct vchiq_state {int unused_service; struct vchiq_service** services; } ;
struct vchiq_service {scalar_t__ srvstate; scalar_t__ instance; scalar_t__ ref_count; } ;
typedef  scalar_t__ VCHIQ_INSTANCE_T ;

/* Variables and functions */
 scalar_t__ VCHIQ_SRVSTATE_FREE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  service_spinlock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct vchiq_service *
next_service_by_instance(struct vchiq_state *state, VCHIQ_INSTANCE_T instance,
			 int *pidx)
{
	struct vchiq_service *service = NULL;
	int idx = *pidx;

	spin_lock(&service_spinlock);
	while (idx < state->unused_service) {
		struct vchiq_service *srv = state->services[idx++];

		if (srv && (srv->srvstate != VCHIQ_SRVSTATE_FREE) &&
			(srv->instance == instance)) {
			service = srv;
			WARN_ON(service->ref_count == 0);
			service->ref_count++;
			break;
		}
	}
	spin_unlock(&service_spinlock);

	*pidx = idx;

	return service;
}