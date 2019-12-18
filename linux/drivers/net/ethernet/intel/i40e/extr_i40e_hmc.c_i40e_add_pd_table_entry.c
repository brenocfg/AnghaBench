#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  size_t u32 ;
struct i40e_hw {int dummy; } ;
struct TYPE_9__ {scalar_t__ va; } ;
struct i40e_hmc_pd_table {TYPE_4__ pd_page_addr; struct i40e_hmc_pd_entry* pd_entry; } ;
struct i40e_dma_mem {int pa; } ;
struct TYPE_10__ {size_t sd_pd_index; scalar_t__ entry_type; struct i40e_dma_mem addr; } ;
struct i40e_hmc_pd_entry {int valid; int rsrc_pg; size_t sd_index; TYPE_5__ bp; } ;
struct TYPE_8__ {size_t sd_cnt; TYPE_2__* sd_entry; } ;
struct i40e_hmc_info {TYPE_3__ sd_table; } ;
typedef  scalar_t__ i40e_status ;
struct TYPE_6__ {struct i40e_hmc_pd_table pd_table; } ;
struct TYPE_7__ {scalar_t__ entry_type; TYPE_1__ u; } ;

/* Variables and functions */
 scalar_t__ I40E_ERR_INVALID_PAGE_DESC_INDEX ; 
 int /*<<< orphan*/  I40E_HMC_PAGED_BP_SIZE ; 
 int /*<<< orphan*/  I40E_HMC_PD_BP_BUF_ALIGNMENT ; 
 size_t I40E_HMC_PD_CNT_IN_SD ; 
 int /*<<< orphan*/  I40E_INC_BP_REFCNT (TYPE_5__*) ; 
 int /*<<< orphan*/  I40E_INC_PD_REFCNT (struct i40e_hmc_pd_table*) ; 
 scalar_t__ I40E_SD_TYPE_PAGED ; 
 int /*<<< orphan*/  hw_dbg (struct i40e_hw*,char*) ; 
 scalar_t__ i40e_allocate_dma_mem (struct i40e_hw*,struct i40e_dma_mem*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_mem_bp ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

i40e_status i40e_add_pd_table_entry(struct i40e_hw *hw,
					      struct i40e_hmc_info *hmc_info,
					      u32 pd_index,
					      struct i40e_dma_mem *rsrc_pg)
{
	i40e_status ret_code = 0;
	struct i40e_hmc_pd_table *pd_table;
	struct i40e_hmc_pd_entry *pd_entry;
	struct i40e_dma_mem mem;
	struct i40e_dma_mem *page = &mem;
	u32 sd_idx, rel_pd_idx;
	u64 *pd_addr;
	u64 page_desc;

	if (pd_index / I40E_HMC_PD_CNT_IN_SD >= hmc_info->sd_table.sd_cnt) {
		ret_code = I40E_ERR_INVALID_PAGE_DESC_INDEX;
		hw_dbg(hw, "i40e_add_pd_table_entry: bad pd_index\n");
		goto exit;
	}

	/* find corresponding sd */
	sd_idx = (pd_index / I40E_HMC_PD_CNT_IN_SD);
	if (I40E_SD_TYPE_PAGED !=
	    hmc_info->sd_table.sd_entry[sd_idx].entry_type)
		goto exit;

	rel_pd_idx = (pd_index % I40E_HMC_PD_CNT_IN_SD);
	pd_table = &hmc_info->sd_table.sd_entry[sd_idx].u.pd_table;
	pd_entry = &pd_table->pd_entry[rel_pd_idx];
	if (!pd_entry->valid) {
		if (rsrc_pg) {
			pd_entry->rsrc_pg = true;
			page = rsrc_pg;
		} else {
			/* allocate a 4K backing page */
			ret_code = i40e_allocate_dma_mem(hw, page, i40e_mem_bp,
						I40E_HMC_PAGED_BP_SIZE,
						I40E_HMC_PD_BP_BUF_ALIGNMENT);
			if (ret_code)
				goto exit;
			pd_entry->rsrc_pg = false;
		}

		pd_entry->bp.addr = *page;
		pd_entry->bp.sd_pd_index = pd_index;
		pd_entry->bp.entry_type = I40E_SD_TYPE_PAGED;
		/* Set page address and valid bit */
		page_desc = page->pa | 0x1;

		pd_addr = (u64 *)pd_table->pd_page_addr.va;
		pd_addr += rel_pd_idx;

		/* Add the backing page physical address in the pd entry */
		memcpy(pd_addr, &page_desc, sizeof(u64));

		pd_entry->sd_index = sd_idx;
		pd_entry->valid = true;
		I40E_INC_PD_REFCNT(pd_table);
	}
	I40E_INC_BP_REFCNT(&pd_entry->bp);
exit:
	return ret_code;
}