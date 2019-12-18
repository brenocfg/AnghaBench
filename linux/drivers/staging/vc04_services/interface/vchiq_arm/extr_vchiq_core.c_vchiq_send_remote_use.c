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
struct vchiq_state {scalar_t__ conn_state; } ;
typedef  int /*<<< orphan*/  VCHIQ_STATUS_T ;

/* Variables and functions */
 scalar_t__ VCHIQ_CONNSTATE_DISCONNECTED ; 
 int /*<<< orphan*/  VCHIQ_MAKE_MSG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCHIQ_MSG_REMOTE_USE ; 
 int /*<<< orphan*/  VCHIQ_RETRY ; 
 int /*<<< orphan*/  queue_message (struct vchiq_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

VCHIQ_STATUS_T vchiq_send_remote_use(struct vchiq_state *state)
{
	VCHIQ_STATUS_T status = VCHIQ_RETRY;

	if (state->conn_state != VCHIQ_CONNSTATE_DISCONNECTED)
		status = queue_message(state, NULL,
			VCHIQ_MAKE_MSG(VCHIQ_MSG_REMOTE_USE, 0, 0),
			NULL, NULL, 0, 0);
	return status;
}