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
struct vchiq_state {scalar_t__ conn_state; int /*<<< orphan*/  connect; } ;
struct vchiq_service {scalar_t__ srvstate; } ;
typedef  scalar_t__ VCHIQ_STATUS_T ;
typedef  int /*<<< orphan*/  VCHIQ_INSTANCE_T ;

/* Variables and functions */
 int /*<<< orphan*/  QMFLAGS_IS_BLOCKING ; 
 scalar_t__ VCHIQ_CONNSTATE_CONNECTED ; 
 scalar_t__ VCHIQ_CONNSTATE_CONNECTING ; 
 scalar_t__ VCHIQ_CONNSTATE_DISCONNECTED ; 
 int /*<<< orphan*/  VCHIQ_MAKE_MSG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCHIQ_MSG_CONNECT ; 
 scalar_t__ VCHIQ_RETRY ; 
 scalar_t__ VCHIQ_SRVSTATE_HIDDEN ; 
 int /*<<< orphan*/  VCHIQ_SRVSTATE_LISTENING ; 
 scalar_t__ VCHIQ_SUCCESS ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct vchiq_service* next_service_by_instance (struct vchiq_state*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ queue_message (struct vchiq_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_service (struct vchiq_service*) ; 
 int /*<<< orphan*/  vchiq_set_conn_state (struct vchiq_state*,scalar_t__) ; 
 int /*<<< orphan*/  vchiq_set_service_state (struct vchiq_service*,int /*<<< orphan*/ ) ; 
 scalar_t__ wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

VCHIQ_STATUS_T
vchiq_connect_internal(struct vchiq_state *state, VCHIQ_INSTANCE_T instance)
{
	struct vchiq_service *service;
	int i;

	/* Find all services registered to this client and enable them. */
	i = 0;
	while ((service = next_service_by_instance(state, instance,
		&i)) !=	NULL) {
		if (service->srvstate == VCHIQ_SRVSTATE_HIDDEN)
			vchiq_set_service_state(service,
				VCHIQ_SRVSTATE_LISTENING);
		unlock_service(service);
	}

	if (state->conn_state == VCHIQ_CONNSTATE_DISCONNECTED) {
		if (queue_message(state, NULL,
			VCHIQ_MAKE_MSG(VCHIQ_MSG_CONNECT, 0, 0), NULL, NULL,
			0, QMFLAGS_IS_BLOCKING) == VCHIQ_RETRY)
			return VCHIQ_RETRY;

		vchiq_set_conn_state(state, VCHIQ_CONNSTATE_CONNECTING);
	}

	if (state->conn_state == VCHIQ_CONNSTATE_CONNECTING) {
		if (wait_for_completion_interruptible(&state->connect))
			return VCHIQ_RETRY;

		vchiq_set_conn_state(state, VCHIQ_CONNSTATE_CONNECTED);
		complete(&state->connect);
	}

	return VCHIQ_SUCCESS;
}