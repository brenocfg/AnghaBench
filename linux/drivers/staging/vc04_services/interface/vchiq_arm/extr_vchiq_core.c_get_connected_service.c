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
struct vchiq_service {scalar_t__ srvstate; unsigned int remoteport; } ;

/* Variables and functions */
 scalar_t__ VCHIQ_SRVSTATE_OPEN ; 
 int /*<<< orphan*/  lock_service (struct vchiq_service*) ; 

__attribute__((used)) static struct vchiq_service *
get_connected_service(struct vchiq_state *state, unsigned int port)
{
	int i;

	for (i = 0; i < state->unused_service; i++) {
		struct vchiq_service *service = state->services[i];

		if (service && (service->srvstate == VCHIQ_SRVSTATE_OPEN)
			&& (service->remoteport == port)) {
			lock_service(service);
			return service;
		}
	}
	return NULL;
}