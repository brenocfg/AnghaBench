#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct i40iw_sc_dev {int dummy; } ;
struct i40iw_pble_alloc {int total_cnt; int /*<<< orphan*/  level; } ;
struct TYPE_2__ {struct gen_pool* pool; } ;
struct i40iw_hmc_pble_rsrc {int /*<<< orphan*/  stats_alloc_fail; int /*<<< orphan*/  stats_alloc_ok; TYPE_1__ pinfo; } ;
struct gen_pool {int dummy; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_LEVEL_0 ; 
 int add_pble_pool (struct i40iw_sc_dev*,struct i40iw_hmc_pble_rsrc*) ; 
 int get_lvl1_lvl2_pble (struct i40iw_sc_dev*,struct i40iw_hmc_pble_rsrc*,struct i40iw_pble_alloc*,struct gen_pool*) ; 

enum i40iw_status_code i40iw_get_pble(struct i40iw_sc_dev *dev,
				      struct i40iw_hmc_pble_rsrc *pble_rsrc,
				      struct i40iw_pble_alloc *palloc,
				      u32 pble_cnt)
{
	struct gen_pool *pool;
	enum i40iw_status_code status = 0;
	u32 max_sds = 0;
	int i;

	pool = pble_rsrc->pinfo.pool;
	palloc->total_cnt = pble_cnt;
	palloc->level = I40IW_LEVEL_0;
	/*check first to see if we can get pble's without acquiring additional sd's */
	status = get_lvl1_lvl2_pble(dev, pble_rsrc, palloc, pool);
	if (!status)
		goto exit;
	max_sds = (palloc->total_cnt >> 18) + 1;
	for (i = 0; i < max_sds; i++) {
		status = add_pble_pool(dev, pble_rsrc);
		if (status)
			break;
		status = get_lvl1_lvl2_pble(dev, pble_rsrc, palloc, pool);
		if (!status)
			break;
	}
exit:
	if (!status)
		pble_rsrc->stats_alloc_ok++;
	else
		pble_rsrc->stats_alloc_fail++;

	return status;
}