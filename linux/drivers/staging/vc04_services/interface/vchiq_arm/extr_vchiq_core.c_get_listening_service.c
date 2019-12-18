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
struct vchiq_service {int public_fourcc; scalar_t__ srvstate; scalar_t__ remoteport; } ;

/* Variables and functions */
 int VCHIQ_FOURCC_INVALID ; 
 scalar_t__ VCHIQ_PORT_FREE ; 
 scalar_t__ VCHIQ_SRVSTATE_LISTENING ; 
 scalar_t__ VCHIQ_SRVSTATE_OPEN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  lock_service (struct vchiq_service*) ; 

__attribute__((used)) static struct vchiq_service *
get_listening_service(struct vchiq_state *state, int fourcc)
{
	int i;

	WARN_ON(fourcc == VCHIQ_FOURCC_INVALID);

	for (i = 0; i < state->unused_service; i++) {
		struct vchiq_service *service = state->services[i];

		if (service &&
			(service->public_fourcc == fourcc) &&
			((service->srvstate == VCHIQ_SRVSTATE_LISTENING) ||
			((service->srvstate == VCHIQ_SRVSTATE_OPEN) &&
			(service->remoteport == VCHIQ_PORT_FREE)))) {
			lock_service(service);
			return service;
		}
	}

	return NULL;
}