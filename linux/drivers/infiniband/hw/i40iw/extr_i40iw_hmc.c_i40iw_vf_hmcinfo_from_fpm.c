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
typedef  scalar_t__ u8 ;
typedef  size_t u16 ;
struct i40iw_sc_dev {TYPE_1__** vf_dev; } ;
struct i40iw_hmc_info {int dummy; } ;
struct TYPE_2__ {struct i40iw_hmc_info hmc_info; scalar_t__ pmf_index; } ;

/* Variables and functions */
 size_t I40IW_MAX_PE_ENABLED_VF_COUNT ; 

struct i40iw_hmc_info *i40iw_vf_hmcinfo_from_fpm(struct i40iw_sc_dev *dev,
						 u8 hmc_fn_id)
{
	struct i40iw_hmc_info *hmc_info = NULL;
	u16 idx;

	for (idx = 0; idx < I40IW_MAX_PE_ENABLED_VF_COUNT; idx++) {
		if (dev->vf_dev[idx] &&
		    ((u8)dev->vf_dev[idx]->pmf_index == hmc_fn_id)) {
			hmc_info = &dev->vf_dev[idx]->hmc_info;
			break;
		}
	}
	return hmc_info;
}