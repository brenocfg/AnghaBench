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
struct vchiq_state {scalar_t__ conn_state; struct vchiq_service_quota* service_quotas; int /*<<< orphan*/  slot_mutex; int /*<<< orphan*/  recycle_mutex; } ;
struct vchiq_service_quota {int /*<<< orphan*/  quota_event; } ;
struct vchiq_service {int closing; size_t localport; struct vchiq_state* state; } ;

/* Variables and functions */
 scalar_t__ VCHIQ_CONNSTATE_PAUSE_SENT ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mark_service_closing_internal(struct vchiq_service *service, int sh_thread)
{
	struct vchiq_state *state = service->state;
	struct vchiq_service_quota *service_quota;

	service->closing = 1;

	/* Synchronise with other threads. */
	mutex_lock(&state->recycle_mutex);
	mutex_unlock(&state->recycle_mutex);
	if (!sh_thread || (state->conn_state != VCHIQ_CONNSTATE_PAUSE_SENT)) {
		/* If we're pausing then the slot_mutex is held until resume
		 * by the slot handler.  Therefore don't try to acquire this
		 * mutex if we're the slot handler and in the pause sent state.
		 * We don't need to in this case anyway. */
		mutex_lock(&state->slot_mutex);
		mutex_unlock(&state->slot_mutex);
	}

	/* Unblock any sending thread. */
	service_quota = &state->service_quotas[service->localport];
	complete(&service_quota->quota_event);
}