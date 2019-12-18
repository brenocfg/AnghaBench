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
struct vchiq_state {int /*<<< orphan*/  id; } ;
struct vchiq_service {int srvstate; int /*<<< orphan*/  remove_event; int /*<<< orphan*/  localport; struct vchiq_state* state; } ;

/* Variables and functions */
#define  VCHIQ_SRVSTATE_CLOSED 132 
#define  VCHIQ_SRVSTATE_CLOSEWAIT 131 
 int /*<<< orphan*/  VCHIQ_SRVSTATE_FREE ; 
#define  VCHIQ_SRVSTATE_HIDDEN 130 
#define  VCHIQ_SRVSTATE_LISTENING 129 
#define  VCHIQ_SRVSTATE_OPENING 128 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * srvstate_names ; 
 int /*<<< orphan*/  unlock_service (struct vchiq_service*) ; 
 int /*<<< orphan*/  vchiq_core_log_level ; 
 int /*<<< orphan*/  vchiq_log_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_log_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_set_service_state (struct vchiq_service*,int /*<<< orphan*/ ) ; 

void
vchiq_free_service_internal(struct vchiq_service *service)
{
	struct vchiq_state *state = service->state;

	vchiq_log_info(vchiq_core_log_level, "%d: fsi - (%d)",
		state->id, service->localport);

	switch (service->srvstate) {
	case VCHIQ_SRVSTATE_OPENING:
	case VCHIQ_SRVSTATE_CLOSED:
	case VCHIQ_SRVSTATE_HIDDEN:
	case VCHIQ_SRVSTATE_LISTENING:
	case VCHIQ_SRVSTATE_CLOSEWAIT:
		break;
	default:
		vchiq_log_error(vchiq_core_log_level,
			"%d: fsi - (%d) in state %s",
			state->id, service->localport,
			srvstate_names[service->srvstate]);
		return;
	}

	vchiq_set_service_state(service, VCHIQ_SRVSTATE_FREE);

	complete(&service->remove_event);

	/* Release the initial lock */
	unlock_service(service);
}