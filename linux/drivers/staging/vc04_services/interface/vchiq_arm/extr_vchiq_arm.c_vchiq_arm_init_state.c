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
struct vchiq_state {int dummy; } ;
struct vchiq_arm_state {scalar_t__ first_connect; int /*<<< orphan*/  suspend_timer; struct vchiq_state* state; scalar_t__ suspend_timer_running; int /*<<< orphan*/  suspend_timer_timeout; int /*<<< orphan*/  blocked_blocker; int /*<<< orphan*/  resume_blocker; int /*<<< orphan*/  vc_resume_complete; int /*<<< orphan*/  vc_suspend_complete; int /*<<< orphan*/  ka_release_count; int /*<<< orphan*/  ka_use_ack_count; int /*<<< orphan*/  ka_use_count; int /*<<< orphan*/  ka_evt; int /*<<< orphan*/  susp_res_lock; } ;
typedef  int /*<<< orphan*/  VCHIQ_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  SUSPEND_TIMER_TIMEOUT_MS ; 
 int /*<<< orphan*/  VCHIQ_SUCCESS ; 
 int /*<<< orphan*/  VC_RESUME_RESUMED ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_resume_state (struct vchiq_arm_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  suspend_timer_callback ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

VCHIQ_STATUS_T
vchiq_arm_init_state(struct vchiq_state *state,
		     struct vchiq_arm_state *arm_state)
{
	if (arm_state) {
		rwlock_init(&arm_state->susp_res_lock);

		init_completion(&arm_state->ka_evt);
		atomic_set(&arm_state->ka_use_count, 0);
		atomic_set(&arm_state->ka_use_ack_count, 0);
		atomic_set(&arm_state->ka_release_count, 0);

		init_completion(&arm_state->vc_suspend_complete);

		init_completion(&arm_state->vc_resume_complete);
		/* Initialise to 'done' state.  We only want to block on resume
		 * completion while videocore is suspended. */
		set_resume_state(arm_state, VC_RESUME_RESUMED);

		init_completion(&arm_state->resume_blocker);
		/* Initialise to 'done' state.  We only want to block on this
		 * completion while resume is blocked */
		complete_all(&arm_state->resume_blocker);

		init_completion(&arm_state->blocked_blocker);
		/* Initialise to 'done' state.  We only want to block on this
		 * completion while things are waiting on the resume blocker */
		complete_all(&arm_state->blocked_blocker);

		arm_state->suspend_timer_timeout = SUSPEND_TIMER_TIMEOUT_MS;
		arm_state->suspend_timer_running = 0;
		arm_state->state = state;
		timer_setup(&arm_state->suspend_timer, suspend_timer_callback,
			    0);

		arm_state->first_connect = 0;

	}
	return VCHIQ_SUCCESS;
}