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
struct ice_hw {int /*<<< orphan*/ * port_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_cfg_fw_log (struct ice_hw*,int) ; 
 int /*<<< orphan*/  ice_cleanup_fltr_mgmt_struct (struct ice_hw*) ; 
 int /*<<< orphan*/  ice_clear_all_vsi_ctx (struct ice_hw*) ; 
 int /*<<< orphan*/  ice_destroy_all_ctrlq (struct ice_hw*) ; 
 int /*<<< orphan*/  ice_free_hw_tbls (struct ice_hw*) ; 
 int /*<<< orphan*/  ice_free_seg (struct ice_hw*) ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 
 int /*<<< orphan*/  ice_sched_cleanup_all (struct ice_hw*) ; 
 int /*<<< orphan*/  ice_sched_clear_agg (struct ice_hw*) ; 

void ice_deinit_hw(struct ice_hw *hw)
{
	ice_cleanup_fltr_mgmt_struct(hw);

	ice_sched_cleanup_all(hw);
	ice_sched_clear_agg(hw);
	ice_free_seg(hw);
	ice_free_hw_tbls(hw);

	if (hw->port_info) {
		devm_kfree(ice_hw_to_dev(hw), hw->port_info);
		hw->port_info = NULL;
	}

	/* Attempt to disable FW logging before shutting down control queues */
	ice_cfg_fw_log(hw, false);
	ice_destroy_all_ctrlq(hw);

	/* Clear VSI contexts if not already cleared */
	ice_clear_all_vsi_ctx(hw);
}