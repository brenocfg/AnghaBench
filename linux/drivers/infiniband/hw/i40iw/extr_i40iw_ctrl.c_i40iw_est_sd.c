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
typedef  int u64 ;
struct i40iw_sc_dev {scalar_t__ is_pf; } ;
struct i40iw_hmc_info {TYPE_1__* hmc_obj; } ;
struct TYPE_2__ {int cnt; int size; } ;

/* Variables and functions */
 int I40IW_HMC_IW_PBLE ; 
 int I40IW_HMC_IW_QP ; 

__attribute__((used)) static u64 i40iw_est_sd(struct i40iw_sc_dev *dev, struct i40iw_hmc_info *hmc_info)
{
	int i;
	u64 size = 0;
	u64 sd;

	for (i = I40IW_HMC_IW_QP; i < I40IW_HMC_IW_PBLE; i++)
		size += hmc_info->hmc_obj[i].cnt * hmc_info->hmc_obj[i].size;

	if (dev->is_pf)
		size += hmc_info->hmc_obj[I40IW_HMC_IW_PBLE].cnt * hmc_info->hmc_obj[I40IW_HMC_IW_PBLE].size;

	if (size & 0x1FFFFF)
		sd = (size >> 21) + 1; /* add 1 for remainder */
	else
		sd = size >> 21;

	if (!dev->is_pf) {
		/* 2MB alignment for VF PBLE HMC */
		size = hmc_info->hmc_obj[I40IW_HMC_IW_PBLE].cnt * hmc_info->hmc_obj[I40IW_HMC_IW_PBLE].size;
		if (size & 0x1FFFFF)
			sd += (size >> 21) + 1; /* add 1 for remainder */
		else
			sd += size >> 21;
	}

	return sd;
}