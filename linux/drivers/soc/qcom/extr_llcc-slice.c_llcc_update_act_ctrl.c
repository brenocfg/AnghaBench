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
struct TYPE_4__ {int /*<<< orphan*/  bcast_regmap; } ;

/* Variables and functions */
 int ACT_CTRL_ACT_TRIG ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  LLCC_STATUS_READ_DELAY ; 
 int LLCC_TRP_ACT_CTRLn (int) ; 
 int LLCC_TRP_STATUSn (int) ; 
 int PTR_ERR (TYPE_1__*) ; 
 TYPE_1__* drv_data ; 
 int regmap_read_poll_timeout (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int llcc_update_act_ctrl(u32 sid,
				u32 act_ctrl_reg_val, u32 status)
{
	u32 act_ctrl_reg;
	u32 status_reg;
	u32 slice_status;
	int ret;

	if (IS_ERR(drv_data))
		return PTR_ERR(drv_data);

	act_ctrl_reg = LLCC_TRP_ACT_CTRLn(sid);
	status_reg = LLCC_TRP_STATUSn(sid);

	/* Set the ACTIVE trigger */
	act_ctrl_reg_val |= ACT_CTRL_ACT_TRIG;
	ret = regmap_write(drv_data->bcast_regmap, act_ctrl_reg,
				act_ctrl_reg_val);
	if (ret)
		return ret;

	/* Clear the ACTIVE trigger */
	act_ctrl_reg_val &= ~ACT_CTRL_ACT_TRIG;
	ret = regmap_write(drv_data->bcast_regmap, act_ctrl_reg,
				act_ctrl_reg_val);
	if (ret)
		return ret;

	ret = regmap_read_poll_timeout(drv_data->bcast_regmap, status_reg,
				      slice_status, !(slice_status & status),
				      0, LLCC_STATUS_READ_DELAY);
	return ret;
}