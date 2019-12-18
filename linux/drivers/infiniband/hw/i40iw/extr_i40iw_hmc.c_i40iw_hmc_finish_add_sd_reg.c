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
struct i40iw_sc_dev {int dummy; } ;
struct i40iw_hmc_create_obj_info {scalar_t__ start_idx; size_t rsrc_type; scalar_t__ count; int /*<<< orphan*/  add_sd_cnt; TYPE_2__* hmc_info; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_4__ {int /*<<< orphan*/ * sd_indexes; TYPE_1__* hmc_obj; } ;
struct TYPE_3__ {scalar_t__ cnt; } ;

/* Variables and functions */
 int I40IW_ERR_INVALID_HMC_OBJ_COUNT ; 
 int I40IW_ERR_INVALID_HMC_OBJ_INDEX ; 
 int i40iw_hmc_sd_grp (struct i40iw_sc_dev*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_hmc_finish_add_sd_reg(struct i40iw_sc_dev *dev,
							  struct i40iw_hmc_create_obj_info *info)
{
	if (info->start_idx >= info->hmc_info->hmc_obj[info->rsrc_type].cnt)
		return I40IW_ERR_INVALID_HMC_OBJ_INDEX;

	if ((info->start_idx + info->count) >
			info->hmc_info->hmc_obj[info->rsrc_type].cnt)
		return I40IW_ERR_INVALID_HMC_OBJ_COUNT;

	if (!info->add_sd_cnt)
		return 0;

	return i40iw_hmc_sd_grp(dev, info->hmc_info,
				info->hmc_info->sd_indexes[0],
				info->add_sd_cnt, true);
}