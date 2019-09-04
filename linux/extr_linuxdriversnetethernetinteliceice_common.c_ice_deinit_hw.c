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
 int /*<<< orphan*/  ice_cleanup_fltr_mgmt_struct (struct ice_hw*) ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 
 int /*<<< orphan*/  ice_sched_cleanup_all (struct ice_hw*) ; 
 int /*<<< orphan*/  ice_shutdown_all_ctrlq (struct ice_hw*) ; 

void ice_deinit_hw(struct ice_hw *hw)
{
	ice_sched_cleanup_all(hw);
	ice_shutdown_all_ctrlq(hw);

	if (hw->port_info) {
		devm_kfree(ice_hw_to_dev(hw), hw->port_info);
		hw->port_info = NULL;
	}

	ice_cleanup_fltr_mgmt_struct(hw);
}