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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct sd_pd_idx {int rel_pd_idx; int /*<<< orphan*/  sd_idx; } ;
struct i40iw_sc_dev {int /*<<< orphan*/  hw; scalar_t__ is_pf; } ;
struct TYPE_4__ {scalar_t__ va; } ;
struct TYPE_5__ {TYPE_1__ addr; } ;
struct TYPE_6__ {TYPE_2__ bp; } ;
struct i40iw_hmc_sd_entry {TYPE_3__ u; int /*<<< orphan*/  valid; } ;
struct i40iw_hmc_pble_rsrc {int /*<<< orphan*/  next_fpm_addr; } ;
struct i40iw_hmc_info {int dummy; } ;
struct i40iw_chunk {int size; int /*<<< orphan*/  fpm_addr; int /*<<< orphan*/ * vaddr; int /*<<< orphan*/  type; } ;
struct i40iw_add_page_info {int pages; struct sd_pd_idx idx; struct i40iw_hmc_sd_entry* sd_entry; struct i40iw_hmc_info* hmc_info; struct i40iw_chunk* chunk; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_DEBUG_PBLE ; 
 int /*<<< orphan*/  I40IW_DMA_COHERENT ; 
 int /*<<< orphan*/  I40IW_HMC_DIRECT_BP_SIZE ; 
 int I40IW_HMC_PAGED_BP_SHIFT ; 
 int /*<<< orphan*/  I40IW_SD_TYPE_DIRECT ; 
 int i40iw_add_sd_table_entry (int /*<<< orphan*/ ,struct i40iw_hmc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_debug (struct i40iw_sc_dev*,int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum i40iw_status_code add_sd_direct(struct i40iw_sc_dev *dev,
					    struct i40iw_hmc_pble_rsrc *pble_rsrc,
					    struct i40iw_add_page_info *info)
{
	enum i40iw_status_code ret_code = 0;
	struct sd_pd_idx *idx = &info->idx;
	struct i40iw_chunk *chunk = info->chunk;
	struct i40iw_hmc_info *hmc_info = info->hmc_info;
	struct i40iw_hmc_sd_entry *sd_entry = info->sd_entry;
	u32 offset = 0;

	if (!sd_entry->valid) {
		if (dev->is_pf) {
			ret_code = i40iw_add_sd_table_entry(dev->hw, hmc_info,
							    info->idx.sd_idx,
							    I40IW_SD_TYPE_DIRECT,
							    I40IW_HMC_DIRECT_BP_SIZE);
			if (ret_code)
				return ret_code;
			chunk->type = I40IW_DMA_COHERENT;
		}
	}
	offset = idx->rel_pd_idx << I40IW_HMC_PAGED_BP_SHIFT;
	chunk->size = info->pages << I40IW_HMC_PAGED_BP_SHIFT;
	chunk->vaddr = ((u8 *)sd_entry->u.bp.addr.va + offset);
	chunk->fpm_addr = pble_rsrc->next_fpm_addr;
	i40iw_debug(dev, I40IW_DEBUG_PBLE, "chunk_size[%d] = 0x%x vaddr=%p fpm_addr = %llx\n",
		    chunk->size, chunk->size, chunk->vaddr, chunk->fpm_addr);
	return 0;
}