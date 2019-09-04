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
struct i40iw_sc_dev {int dummy; } ;
struct i40iw_pble_alloc {scalar_t__ total_cnt; } ;
struct i40iw_hmc_pble_rsrc {int dummy; } ;
struct gen_pool {int dummy; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 scalar_t__ PBLE_PER_PAGE ; 
 int get_lvl1_pble (struct i40iw_sc_dev*,struct i40iw_hmc_pble_rsrc*,struct i40iw_pble_alloc*) ; 
 int get_lvl2_pble (struct i40iw_hmc_pble_rsrc*,struct i40iw_pble_alloc*,struct gen_pool*) ; 

__attribute__((used)) static inline enum i40iw_status_code get_lvl1_lvl2_pble(struct i40iw_sc_dev *dev,
							struct i40iw_hmc_pble_rsrc *pble_rsrc,
							struct i40iw_pble_alloc *palloc,
							struct gen_pool *pool)
{
	enum i40iw_status_code status = 0;

	status = get_lvl1_pble(dev, pble_rsrc, palloc);
	if (status && (palloc->total_cnt > PBLE_PER_PAGE))
		status = get_lvl2_pble(pble_rsrc, palloc, pool);
	return status;
}