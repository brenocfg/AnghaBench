#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct opa_congestion_setting_entry {int dummy; } ;
struct ib_cc_table_entry {int dummy; } ;
struct hfi1_pportdata {int total_cct_entry; int /*<<< orphan*/  cc_state_lock; int /*<<< orphan*/  cc_state; int /*<<< orphan*/  congestion_entries; int /*<<< orphan*/  cc_sl_control_map; int /*<<< orphan*/  ccti_entries; } ;
struct TYPE_4__ {int /*<<< orphan*/  entries; int /*<<< orphan*/  control_map; int /*<<< orphan*/  port_control; } ;
struct TYPE_3__ {int ccti_limit; int /*<<< orphan*/  entries; } ;
struct cc_state {TYPE_2__ cong_setting; TYPE_1__ cct; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_CC_CCS_PC_SL_BASED ; 
 int OPA_MAX_SLS ; 
 struct cc_state* get_cc_state_protected (struct hfi1_pportdata*) ; 
 int /*<<< orphan*/  kfree (struct cc_state*) ; 
 int /*<<< orphan*/  kfree_rcu (struct cc_state*,int /*<<< orphan*/ ) ; 
 struct cc_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct cc_state*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void apply_cc_state(struct hfi1_pportdata *ppd)
{
	struct cc_state *old_cc_state, *new_cc_state;

	new_cc_state = kzalloc(sizeof(*new_cc_state), GFP_KERNEL);
	if (!new_cc_state)
		return;

	/*
	 * Hold the lock for updating *and* to prevent ppd information
	 * from changing during the update.
	 */
	spin_lock(&ppd->cc_state_lock);

	old_cc_state = get_cc_state_protected(ppd);
	if (!old_cc_state) {
		/* never active, or shutting down */
		spin_unlock(&ppd->cc_state_lock);
		kfree(new_cc_state);
		return;
	}

	*new_cc_state = *old_cc_state;

	if (ppd->total_cct_entry)
		new_cc_state->cct.ccti_limit = ppd->total_cct_entry - 1;
	else
		new_cc_state->cct.ccti_limit = 0;

	memcpy(new_cc_state->cct.entries, ppd->ccti_entries,
	       ppd->total_cct_entry * sizeof(struct ib_cc_table_entry));

	new_cc_state->cong_setting.port_control = IB_CC_CCS_PC_SL_BASED;
	new_cc_state->cong_setting.control_map = ppd->cc_sl_control_map;
	memcpy(new_cc_state->cong_setting.entries, ppd->congestion_entries,
	       OPA_MAX_SLS * sizeof(struct opa_congestion_setting_entry));

	rcu_assign_pointer(ppd->cc_state, new_cc_state);

	spin_unlock(&ppd->cc_state_lock);

	kfree_rcu(old_cc_state, rcu);
}