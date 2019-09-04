#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct i40e_hw {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {TYPE_2__ bp; } ;
struct i40e_hmc_sd_entry {TYPE_3__ u; } ;
struct TYPE_4__ {struct i40e_hmc_sd_entry* sd_entry; } ;
struct i40e_hmc_info {TYPE_1__ sd_table; } ;
typedef  int /*<<< orphan*/  i40e_status ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_CLEAR_PF_SD_ENTRY (struct i40e_hw*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_NOT_SUPPORTED ; 
 int /*<<< orphan*/  I40E_SD_TYPE_DIRECT ; 
 int /*<<< orphan*/  i40e_free_dma_mem (struct i40e_hw*,int /*<<< orphan*/ *) ; 

i40e_status i40e_remove_sd_bp_new(struct i40e_hw *hw,
					    struct i40e_hmc_info *hmc_info,
					    u32 idx, bool is_pf)
{
	struct i40e_hmc_sd_entry *sd_entry;

	if (!is_pf)
		return I40E_NOT_SUPPORTED;

	/* get the entry and decrease its ref counter */
	sd_entry = &hmc_info->sd_table.sd_entry[idx];
	I40E_CLEAR_PF_SD_ENTRY(hw, idx, I40E_SD_TYPE_DIRECT);

	return i40e_free_dma_mem(hw, &sd_entry->u.bp.addr);
}