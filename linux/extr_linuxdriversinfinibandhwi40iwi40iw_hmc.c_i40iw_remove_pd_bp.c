#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
struct i40iw_hw {int dummy; } ;
struct TYPE_7__ {scalar_t__ va; } ;
struct i40iw_hmc_pd_table {int /*<<< orphan*/  pd_entry_virt_mem; int /*<<< orphan*/  ref_cnt; TYPE_3__ pd_page_addr; struct i40iw_hmc_pd_entry* pd_entry; } ;
struct TYPE_5__ {struct i40iw_hmc_pd_table pd_table; } ;
struct i40iw_hmc_sd_entry {scalar_t__ entry_type; TYPE_1__ u; } ;
struct i40iw_dma_mem {int /*<<< orphan*/  va; } ;
struct TYPE_8__ {struct i40iw_dma_mem addr; scalar_t__ ref_cnt; } ;
struct i40iw_hmc_pd_entry {int valid; TYPE_4__ bp; int /*<<< orphan*/  rsrc_pg; } ;
struct TYPE_6__ {size_t sd_cnt; struct i40iw_hmc_sd_entry* sd_entry; } ;
struct i40iw_hmc_info {int /*<<< orphan*/  hmc_fn_id; TYPE_2__ sd_table; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_DEC_BP_REFCNT (TYPE_4__*) ; 
 int /*<<< orphan*/  I40IW_DEC_PD_REFCNT (struct i40iw_hmc_pd_table*) ; 
 int I40IW_ERR_INVALID_PAGE_DESC_INDEX ; 
 int I40IW_ERR_INVALID_SD_TYPE ; 
 int I40IW_ERR_PARAM ; 
 size_t I40IW_HMC_PD_CNT_IN_SD ; 
 int /*<<< orphan*/  I40IW_INVALIDATE_PF_HMC_PD (struct i40iw_hw*,size_t,size_t) ; 
 int /*<<< orphan*/  I40IW_INVALIDATE_VF_HMC_PD (struct i40iw_hw*,size_t,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ I40IW_SD_TYPE_PAGED ; 
 int /*<<< orphan*/  i40iw_free_dma_mem (struct i40iw_hw*,struct i40iw_dma_mem*) ; 
 int /*<<< orphan*/  i40iw_free_virt_mem (struct i40iw_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

enum i40iw_status_code i40iw_remove_pd_bp(struct i40iw_hw *hw,
					  struct i40iw_hmc_info *hmc_info,
					  u32 idx,
					  bool is_pf)
{
	struct i40iw_hmc_pd_entry *pd_entry;
	struct i40iw_hmc_pd_table *pd_table;
	struct i40iw_hmc_sd_entry *sd_entry;
	u32 sd_idx, rel_pd_idx;
	struct i40iw_dma_mem *mem;
	u64 *pd_addr;

	sd_idx = idx / I40IW_HMC_PD_CNT_IN_SD;
	rel_pd_idx = idx % I40IW_HMC_PD_CNT_IN_SD;
	if (sd_idx >= hmc_info->sd_table.sd_cnt)
		return I40IW_ERR_INVALID_PAGE_DESC_INDEX;

	sd_entry = &hmc_info->sd_table.sd_entry[sd_idx];
	if (sd_entry->entry_type != I40IW_SD_TYPE_PAGED)
		return I40IW_ERR_INVALID_SD_TYPE;

	pd_table = &hmc_info->sd_table.sd_entry[sd_idx].u.pd_table;
	pd_entry = &pd_table->pd_entry[rel_pd_idx];
	I40IW_DEC_BP_REFCNT(&pd_entry->bp);
	if (pd_entry->bp.ref_cnt)
		return 0;

	pd_entry->valid = false;
	I40IW_DEC_PD_REFCNT(pd_table);
	pd_addr = (u64 *)pd_table->pd_page_addr.va;
	pd_addr += rel_pd_idx;
	memset(pd_addr, 0, sizeof(u64));
	if (is_pf)
		I40IW_INVALIDATE_PF_HMC_PD(hw, sd_idx, idx);
	else
		I40IW_INVALIDATE_VF_HMC_PD(hw, sd_idx, idx,
					   hmc_info->hmc_fn_id);

	if (!pd_entry->rsrc_pg) {
		mem = &pd_entry->bp.addr;
		if (!mem || !mem->va)
			return I40IW_ERR_PARAM;
		i40iw_free_dma_mem(hw, mem);
	}
	if (!pd_table->ref_cnt)
		i40iw_free_virt_mem(hw, &pd_table->pd_entry_virt_mem);

	return 0;
}