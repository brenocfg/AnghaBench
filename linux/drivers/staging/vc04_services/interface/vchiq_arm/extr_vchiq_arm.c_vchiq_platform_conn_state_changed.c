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
typedef  int /*<<< orphan*/  threadname ;
struct vchiq_state {int id; scalar_t__ conn_state; } ;
struct vchiq_arm_state {int first_connect; int /*<<< orphan*/  susp_res_lock; int /*<<< orphan*/  ka_thread; } ;
typedef  int /*<<< orphan*/  VCHIQ_CONNSTATE_T ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ VCHIQ_CONNSTATE_CONNECTED ; 
 int /*<<< orphan*/  get_conn_state_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_create (int /*<<< orphan*/ *,void*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  vchiq_keepalive_thread_func ; 
 int /*<<< orphan*/  vchiq_log_error (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  vchiq_log_info (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vchiq_arm_state* vchiq_platform_get_arm_state (struct vchiq_state*) ; 
 int /*<<< orphan*/  vchiq_susp_log_level ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void vchiq_platform_conn_state_changed(struct vchiq_state *state,
				       VCHIQ_CONNSTATE_T oldstate,
				       VCHIQ_CONNSTATE_T newstate)
{
	struct vchiq_arm_state *arm_state = vchiq_platform_get_arm_state(state);

	vchiq_log_info(vchiq_susp_log_level, "%d: %s->%s", state->id,
		get_conn_state_name(oldstate), get_conn_state_name(newstate));
	if (state->conn_state == VCHIQ_CONNSTATE_CONNECTED) {
		write_lock_bh(&arm_state->susp_res_lock);
		if (!arm_state->first_connect) {
			char threadname[16];

			arm_state->first_connect = 1;
			write_unlock_bh(&arm_state->susp_res_lock);
			snprintf(threadname, sizeof(threadname), "vchiq-keep/%d",
				state->id);
			arm_state->ka_thread = kthread_create(
				&vchiq_keepalive_thread_func,
				(void *)state,
				threadname);
			if (IS_ERR(arm_state->ka_thread)) {
				vchiq_log_error(vchiq_susp_log_level,
					"vchiq: FATAL: couldn't create thread %s",
					threadname);
			} else {
				wake_up_process(arm_state->ka_thread);
			}
		} else
			write_unlock_bh(&arm_state->susp_res_lock);
	}
}