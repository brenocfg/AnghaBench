#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct llcc_slice_desc {int /*<<< orphan*/  slice_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTIVATE ; 
 int ACT_CTRL_OPCODE_DEACTIVATE ; 
 int ACT_CTRL_OPCODE_SHIFT ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 scalar_t__ IS_ERR_OR_NULL (struct llcc_slice_desc*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* drv_data ; 
 int llcc_update_act_ctrl (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int llcc_slice_deactivate(struct llcc_slice_desc *desc)
{
	u32 act_ctrl_val;
	int ret;

	if (IS_ERR(drv_data))
		return PTR_ERR(drv_data);

	if (IS_ERR_OR_NULL(desc))
		return -EINVAL;

	mutex_lock(&drv_data->lock);
	if (!test_bit(desc->slice_id, drv_data->bitmap)) {
		mutex_unlock(&drv_data->lock);
		return 0;
	}
	act_ctrl_val = ACT_CTRL_OPCODE_DEACTIVATE << ACT_CTRL_OPCODE_SHIFT;

	ret = llcc_update_act_ctrl(desc->slice_id, act_ctrl_val,
				  ACTIVATE);
	if (ret) {
		mutex_unlock(&drv_data->lock);
		return ret;
	}

	__clear_bit(desc->slice_id, drv_data->bitmap);
	mutex_unlock(&drv_data->lock);

	return ret;
}