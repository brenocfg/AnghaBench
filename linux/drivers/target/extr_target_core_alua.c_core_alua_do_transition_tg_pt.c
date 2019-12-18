#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  cg_item; } ;
struct t10_alua_tg_pt_gp {int tg_pt_gp_alua_access_state; scalar_t__ tg_pt_gp_trans_delay_msecs; int /*<<< orphan*/  tg_pt_gp_transition_mutex; int /*<<< orphan*/  tg_pt_gp_id; TYPE_1__ tg_pt_gp_group; scalar_t__ tg_pt_gp_write_metadata; int /*<<< orphan*/  tg_pt_gp_alua_access_status; } ;

/* Variables and functions */
 int ALUA_ACCESS_STATE_TRANSITION ; 
 int /*<<< orphan*/  ALUA_STATUS_ALTERED_BY_EXPLICIT_STPG ; 
 int /*<<< orphan*/  ALUA_STATUS_ALTERED_BY_IMPLICIT_ALUA ; 
 int EAGAIN ; 
 int /*<<< orphan*/  config_item_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  core_alua_dump_state (int) ; 
 int /*<<< orphan*/  core_alua_queue_state_change_ua (struct t10_alua_tg_pt_gp*) ; 
 int /*<<< orphan*/  core_alua_update_tpg_primary_metadata (struct t10_alua_tg_pt_gp*) ; 
 int /*<<< orphan*/  msleep_interruptible (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int core_alua_do_transition_tg_pt(
	struct t10_alua_tg_pt_gp *tg_pt_gp,
	int new_state,
	int explicit)
{
	int prev_state;

	mutex_lock(&tg_pt_gp->tg_pt_gp_transition_mutex);
	/* Nothing to be done here */
	if (tg_pt_gp->tg_pt_gp_alua_access_state == new_state) {
		mutex_unlock(&tg_pt_gp->tg_pt_gp_transition_mutex);
		return 0;
	}

	if (explicit && new_state == ALUA_ACCESS_STATE_TRANSITION) {
		mutex_unlock(&tg_pt_gp->tg_pt_gp_transition_mutex);
		return -EAGAIN;
	}

	/*
	 * Save the old primary ALUA access state, and set the current state
	 * to ALUA_ACCESS_STATE_TRANSITION.
	 */
	prev_state = tg_pt_gp->tg_pt_gp_alua_access_state;
	tg_pt_gp->tg_pt_gp_alua_access_state = ALUA_ACCESS_STATE_TRANSITION;
	tg_pt_gp->tg_pt_gp_alua_access_status = (explicit) ?
				ALUA_STATUS_ALTERED_BY_EXPLICIT_STPG :
				ALUA_STATUS_ALTERED_BY_IMPLICIT_ALUA;

	core_alua_queue_state_change_ua(tg_pt_gp);

	if (new_state == ALUA_ACCESS_STATE_TRANSITION) {
		mutex_unlock(&tg_pt_gp->tg_pt_gp_transition_mutex);
		return 0;
	}

	/*
	 * Check for the optional ALUA primary state transition delay
	 */
	if (tg_pt_gp->tg_pt_gp_trans_delay_msecs != 0)
		msleep_interruptible(tg_pt_gp->tg_pt_gp_trans_delay_msecs);

	/*
	 * Set the current primary ALUA access state to the requested new state
	 */
	tg_pt_gp->tg_pt_gp_alua_access_state = new_state;

	/*
	 * Update the ALUA metadata buf that has been allocated in
	 * core_alua_do_port_transition(), this metadata will be written
	 * to struct file.
	 *
	 * Note that there is the case where we do not want to update the
	 * metadata when the saved metadata is being parsed in userspace
	 * when setting the existing port access state and access status.
	 *
	 * Also note that the failure to write out the ALUA metadata to
	 * struct file does NOT affect the actual ALUA transition.
	 */
	if (tg_pt_gp->tg_pt_gp_write_metadata) {
		core_alua_update_tpg_primary_metadata(tg_pt_gp);
	}

	pr_debug("Successful %s ALUA transition TG PT Group: %s ID: %hu"
		" from primary access state %s to %s\n", (explicit) ? "explicit" :
		"implicit", config_item_name(&tg_pt_gp->tg_pt_gp_group.cg_item),
		tg_pt_gp->tg_pt_gp_id,
		core_alua_dump_state(prev_state),
		core_alua_dump_state(new_state));

	core_alua_queue_state_change_ua(tg_pt_gp);

	mutex_unlock(&tg_pt_gp->tg_pt_gp_transition_mutex);
	return 0;
}