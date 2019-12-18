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
struct TYPE_3__ {int /*<<< orphan*/ * sd_entry; scalar_t__ sd_cnt; int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {int /*<<< orphan*/ * hmc_obj; int /*<<< orphan*/  hmc_obj_virt_mem; TYPE_1__ sd_table; } ;
struct i40e_hw {TYPE_2__ hmc; } ;
struct i40e_hmc_lan_delete_obj_info {int count; scalar_t__ start_idx; int /*<<< orphan*/  rsrc_type; TYPE_2__* hmc_info; } ;
typedef  int /*<<< orphan*/  i40e_status ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_HMC_LAN_FULL ; 
 int /*<<< orphan*/  i40e_delete_lan_hmc_object (struct i40e_hw*,struct i40e_hmc_lan_delete_obj_info*) ; 
 int /*<<< orphan*/  i40e_free_virt_mem (struct i40e_hw*,int /*<<< orphan*/ *) ; 

i40e_status i40e_shutdown_lan_hmc(struct i40e_hw *hw)
{
	struct i40e_hmc_lan_delete_obj_info info;
	i40e_status ret_code;

	info.hmc_info = &hw->hmc;
	info.rsrc_type = I40E_HMC_LAN_FULL;
	info.start_idx = 0;
	info.count = 1;

	/* delete the object */
	ret_code = i40e_delete_lan_hmc_object(hw, &info);

	/* free the SD table entry for LAN */
	i40e_free_virt_mem(hw, &hw->hmc.sd_table.addr);
	hw->hmc.sd_table.sd_cnt = 0;
	hw->hmc.sd_table.sd_entry = NULL;

	/* free memory used for hmc_obj */
	i40e_free_virt_mem(hw, &hw->hmc.hmc_obj_virt_mem);
	hw->hmc.hmc_obj = NULL;

	return ret_code;
}