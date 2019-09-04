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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct i40iw_pble_info {int cnt; void* idx; void* addr; } ;
struct i40iw_pble_level2 {int leaf_cnt; struct i40iw_pble_info* leaf; struct i40iw_pble_info root; } ;
struct i40iw_pble_alloc {int total_cnt; int /*<<< orphan*/  level; struct i40iw_pble_level2 level2; } ;
struct i40iw_hmc_pble_rsrc {int /*<<< orphan*/  stats_lvl2; } ;
struct gen_pool {int dummy; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int I40IW_ERR_NO_MEMORY ; 
 int /*<<< orphan*/  I40IW_LEVEL_2 ; 
 int PBLE_PER_PAGE ; 
 void* fpm_to_idx (struct i40iw_hmc_pble_rsrc*,scalar_t__) ; 
 int /*<<< orphan*/  free_lvl2 (struct i40iw_hmc_pble_rsrc*,struct i40iw_pble_alloc*) ; 
 void* gen_pool_alloc (struct gen_pool*,int) ; 
 scalar_t__ gen_pool_virt_to_phys (struct gen_pool*,void*) ; 
 int /*<<< orphan*/  kfree (struct i40iw_pble_info*) ; 
 struct i40iw_pble_info* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum i40iw_status_code get_lvl2_pble(struct i40iw_hmc_pble_rsrc *pble_rsrc,
					    struct i40iw_pble_alloc *palloc,
					    struct gen_pool *pool)
{
	u32 lf4k, lflast, total, i;
	u32 pblcnt = PBLE_PER_PAGE;
	u64 *addr;
	struct i40iw_pble_level2 *lvl2 = &palloc->level2;
	struct i40iw_pble_info *root = &lvl2->root;
	struct i40iw_pble_info *leaf;

	/* number of full 512 (4K) leafs) */
	lf4k = palloc->total_cnt >> 9;
	lflast = palloc->total_cnt % PBLE_PER_PAGE;
	total = (lflast == 0) ? lf4k : lf4k + 1;
	lvl2->leaf_cnt = total;

	leaf = kzalloc((sizeof(*leaf) * total), GFP_ATOMIC);
	if (!leaf)
		return I40IW_ERR_NO_MEMORY;
	lvl2->leaf = leaf;
	/* allocate pbles for the root */
	root->addr = gen_pool_alloc(pool, (total << 3));
	if (!root->addr) {
		kfree(lvl2->leaf);
		lvl2->leaf = NULL;
		return I40IW_ERR_NO_MEMORY;
	}
	root->idx = fpm_to_idx(pble_rsrc,
			       (u64)gen_pool_virt_to_phys(pool, root->addr));
	root->cnt = total;
	addr = (u64 *)root->addr;
	for (i = 0; i < total; i++, leaf++) {
		pblcnt = (lflast && ((i + 1) == total)) ? lflast : PBLE_PER_PAGE;
		leaf->addr = gen_pool_alloc(pool, (pblcnt << 3));
		if (!leaf->addr)
			goto error;
		leaf->idx = fpm_to_idx(pble_rsrc, (u64)gen_pool_virt_to_phys(pool, leaf->addr));

		leaf->cnt = pblcnt;
		*addr = (u64)leaf->idx;
		addr++;
	}
	palloc->level = I40IW_LEVEL_2;
	pble_rsrc->stats_lvl2++;
	return 0;
 error:
	free_lvl2(pble_rsrc, palloc);
	return I40IW_ERR_NO_MEMORY;
}