#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct sd_pd_idx {size_t sd_idx; scalar_t__ rel_pd_idx; } ;
struct i40iw_sc_dev {scalar_t__ is_pf; struct i40iw_hmc_info* hmc_info; } ;
struct TYPE_12__ {int /*<<< orphan*/  pa; } ;
struct TYPE_13__ {TYPE_5__ addr; } ;
struct TYPE_10__ {int /*<<< orphan*/  pa; } ;
struct TYPE_11__ {TYPE_3__ pd_page_addr; } ;
struct TYPE_14__ {TYPE_6__ bp; TYPE_4__ pd_table; } ;
struct i40iw_hmc_sd_entry {int valid; int entry_type; TYPE_7__ u; } ;
struct TYPE_9__ {int /*<<< orphan*/  clist; int /*<<< orphan*/  pool; } ;
struct i40iw_hmc_pble_rsrc {int unallocated_pble; int next_fpm_addr; TYPE_2__ pinfo; int /*<<< orphan*/  stats_paged_sds; int /*<<< orphan*/  stats_direct_sds; } ;
struct TYPE_8__ {struct i40iw_hmc_sd_entry* sd_entry; } ;
struct i40iw_hmc_info {int /*<<< orphan*/  hmc_fn_id; TYPE_1__ sd_table; } ;
struct i40iw_chunk {int fpm_addr; int size; int /*<<< orphan*/  list; scalar_t__ vaddr; } ;
struct i40iw_add_page_info {struct i40iw_hmc_sd_entry* sd_entry; scalar_t__ pages; struct i40iw_hmc_info* hmc_info; struct i40iw_chunk* chunk; struct sd_pd_idx idx; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
typedef  enum i40iw_sd_entry_type { ____Placeholder_i40iw_sd_entry_type } i40iw_sd_entry_type ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I40IW_DEBUG_PBLE ; 
 int I40IW_ERR_INVALID_PAGE_DESC_INDEX ; 
 int I40IW_ERR_NO_MEMORY ; 
 scalar_t__ I40IW_HMC_PD_CNT_IN_SD ; 
 int I40IW_SD_TYPE_DIRECT ; 
 int I40IW_SD_TYPE_PAGED ; 
 int PBLE_512_SHIFT ; 
 int PBLE_PER_PAGE ; 
 int add_bp_pages (struct i40iw_sc_dev*,struct i40iw_hmc_pble_rsrc*,struct i40iw_add_page_info*) ; 
 int add_sd_direct (struct i40iw_sc_dev*,struct i40iw_hmc_pble_rsrc*,struct i40iw_add_page_info*) ; 
 scalar_t__ gen_pool_add_virt (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  get_sd_pd_idx (struct i40iw_hmc_pble_rsrc*,struct sd_pd_idx*) ; 
 int /*<<< orphan*/  i40iw_debug (struct i40iw_sc_dev*,int /*<<< orphan*/ ,char*,scalar_t__,int,...) ; 
 int i40iw_hmc_sd_one (struct i40iw_sc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int,int) ; 
 int /*<<< orphan*/  i40iw_pr_err (char*,...) ; 
 int /*<<< orphan*/  kfree (struct i40iw_chunk*) ; 
 struct i40iw_chunk* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ min (scalar_t__,int) ; 

__attribute__((used)) static enum i40iw_status_code add_pble_pool(struct i40iw_sc_dev *dev,
					    struct i40iw_hmc_pble_rsrc *pble_rsrc)
{
	struct i40iw_hmc_sd_entry *sd_entry;
	struct i40iw_hmc_info *hmc_info;
	struct i40iw_chunk *chunk;
	struct i40iw_add_page_info info;
	struct sd_pd_idx *idx = &info.idx;
	enum i40iw_status_code ret_code = 0;
	enum i40iw_sd_entry_type sd_entry_type;
	u64 sd_reg_val = 0;
	u32 pages;

	if (pble_rsrc->unallocated_pble < PBLE_PER_PAGE)
		return I40IW_ERR_NO_MEMORY;
	if (pble_rsrc->next_fpm_addr & 0xfff) {
		i40iw_pr_err("next fpm_addr %llx\n", pble_rsrc->next_fpm_addr);
		return I40IW_ERR_INVALID_PAGE_DESC_INDEX;
	}
	chunk = kzalloc(sizeof(*chunk), GFP_KERNEL);
	if (!chunk)
		return I40IW_ERR_NO_MEMORY;
	hmc_info = dev->hmc_info;
	chunk->fpm_addr = pble_rsrc->next_fpm_addr;
	get_sd_pd_idx(pble_rsrc, idx);
	sd_entry = &hmc_info->sd_table.sd_entry[idx->sd_idx];
	pages = (idx->rel_pd_idx) ? (I40IW_HMC_PD_CNT_IN_SD -
			idx->rel_pd_idx) : I40IW_HMC_PD_CNT_IN_SD;
	pages = min(pages, pble_rsrc->unallocated_pble >> PBLE_512_SHIFT);
	info.chunk = chunk;
	info.hmc_info = hmc_info;
	info.pages = pages;
	info.sd_entry = sd_entry;
	if (!sd_entry->valid) {
		sd_entry_type = (!idx->rel_pd_idx &&
				 (pages == I40IW_HMC_PD_CNT_IN_SD) &&
				 dev->is_pf) ? I40IW_SD_TYPE_DIRECT : I40IW_SD_TYPE_PAGED;
	} else {
		sd_entry_type = sd_entry->entry_type;
	}
	i40iw_debug(dev, I40IW_DEBUG_PBLE,
		    "pages = %d, unallocated_pble[%u] current_fpm_addr = %llx\n",
		    pages, pble_rsrc->unallocated_pble, pble_rsrc->next_fpm_addr);
	i40iw_debug(dev, I40IW_DEBUG_PBLE, "sd_entry_type = %d sd_entry valid = %d\n",
		    sd_entry_type, sd_entry->valid);

	if (sd_entry_type == I40IW_SD_TYPE_DIRECT)
		ret_code = add_sd_direct(dev, pble_rsrc, &info);
	if (ret_code)
		sd_entry_type = I40IW_SD_TYPE_PAGED;
	else
		pble_rsrc->stats_direct_sds++;

	if (sd_entry_type == I40IW_SD_TYPE_PAGED) {
		ret_code = add_bp_pages(dev, pble_rsrc, &info);
		if (ret_code)
			goto error;
		else
			pble_rsrc->stats_paged_sds++;
	}

	if (gen_pool_add_virt(pble_rsrc->pinfo.pool, (unsigned long)chunk->vaddr,
			      (phys_addr_t)chunk->fpm_addr, chunk->size, -1)) {
		i40iw_pr_err("could not allocate memory by gen_pool_addr_virt()\n");
		ret_code = I40IW_ERR_NO_MEMORY;
		goto error;
	}
	pble_rsrc->next_fpm_addr += chunk->size;
	i40iw_debug(dev, I40IW_DEBUG_PBLE, "next_fpm_addr = %llx chunk_size[%u] = 0x%x\n",
		    pble_rsrc->next_fpm_addr, chunk->size, chunk->size);
	pble_rsrc->unallocated_pble -= (chunk->size >> 3);
	list_add(&chunk->list, &pble_rsrc->pinfo.clist);
	sd_reg_val = (sd_entry_type == I40IW_SD_TYPE_PAGED) ?
			sd_entry->u.pd_table.pd_page_addr.pa : sd_entry->u.bp.addr.pa;
	if (sd_entry->valid)
		return 0;
	if (dev->is_pf) {
		ret_code = i40iw_hmc_sd_one(dev, hmc_info->hmc_fn_id,
					    sd_reg_val, idx->sd_idx,
					    sd_entry->entry_type, true);
		if (ret_code) {
			i40iw_pr_err("cqp cmd failed for sd (pbles)\n");
			goto error;
		}
	}

	sd_entry->valid = true;
	return 0;
 error:
	kfree(chunk);
	return ret_code;
}