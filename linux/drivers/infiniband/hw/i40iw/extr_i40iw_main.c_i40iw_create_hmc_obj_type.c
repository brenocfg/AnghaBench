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
struct i40iw_sc_dev {TYPE_1__* hmc_ops; } ;
struct i40iw_hmc_create_obj_info {int dummy; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_2__ {int (* create_hmc_object ) (struct i40iw_sc_dev*,struct i40iw_hmc_create_obj_info*) ;} ;

/* Variables and functions */
 int stub1 (struct i40iw_sc_dev*,struct i40iw_hmc_create_obj_info*) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_create_hmc_obj_type(struct i40iw_sc_dev *dev,
							struct i40iw_hmc_create_obj_info *info)
{
	return dev->hmc_ops->create_hmc_object(dev, info);
}