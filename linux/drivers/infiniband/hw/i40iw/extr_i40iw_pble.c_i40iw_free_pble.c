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
struct TYPE_4__ {int cnt; int /*<<< orphan*/  addr; } ;
struct i40iw_pble_alloc {scalar_t__ level; TYPE_2__ level1; } ;
struct TYPE_3__ {struct gen_pool* pool; } ;
struct i40iw_hmc_pble_rsrc {int /*<<< orphan*/  stats_alloc_freed; TYPE_1__ pinfo; } ;
struct gen_pool {int dummy; } ;

/* Variables and functions */
 scalar_t__ I40IW_LEVEL_2 ; 
 int /*<<< orphan*/  free_lvl2 (struct i40iw_hmc_pble_rsrc*,struct i40iw_pble_alloc*) ; 
 int /*<<< orphan*/  gen_pool_free (struct gen_pool*,int /*<<< orphan*/ ,int) ; 

void i40iw_free_pble(struct i40iw_hmc_pble_rsrc *pble_rsrc,
		     struct i40iw_pble_alloc *palloc)
{
	struct gen_pool *pool;

	pool = pble_rsrc->pinfo.pool;
	if (palloc->level == I40IW_LEVEL_2)
		free_lvl2(pble_rsrc, palloc);
	else
		gen_pool_free(pool, palloc->level1.addr,
			      (palloc->level1.cnt << 3));
	pble_rsrc->stats_alloc_freed++;
}