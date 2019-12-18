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
typedef  size_t u64 ;
typedef  size_t u32 ;
struct i40iw_hmc_info {TYPE_1__* hmc_obj; } ;
struct TYPE_2__ {size_t base; size_t size; } ;

/* Variables and functions */
 size_t I40IW_HMC_PAGED_BP_SIZE ; 

__attribute__((used)) static inline void i40iw_find_pd_index_limit(struct i40iw_hmc_info *hmc_info,
					     u32 type,
					     u32 idx,
					     u32 cnt,
					     u32 *pd_idx,
					     u32 *pd_limit)
{
	u64 fpm_adr, fpm_limit;

	fpm_adr = hmc_info->hmc_obj[type].base +
			hmc_info->hmc_obj[type].size * idx;
	fpm_limit = fpm_adr + (hmc_info)->hmc_obj[(type)].size * (cnt);
	*(pd_idx) = (u32)(fpm_adr / I40IW_HMC_PAGED_BP_SIZE);
	*(pd_limit) = (u32)((fpm_limit - 1) / I40IW_HMC_PAGED_BP_SIZE);
	*(pd_limit) += 1;
}