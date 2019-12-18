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
typedef  int u8 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_CONTROL_REG ; 
 int /*<<< orphan*/  GENERAL_2D_CONTROL_REG ; 
 int /*<<< orphan*/  INTERRUPT_EN_REG ; 
 int INT_ENA_ABS_MSK ; 
 int INT_ENA_REL_MSK ; 
 int NO_DECELERATION ; 
 int NO_FILTER ; 
 int REDUCE_REPORTING ; 
 scalar_t__ no_decel ; 
 scalar_t__ no_filter ; 
 scalar_t__ polling_req ; 
 scalar_t__ reduce_report ; 
 int synaptics_i2c_reg_get (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int synaptics_i2c_reg_set (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int synaptics_i2c_config(struct i2c_client *client)
{
	int ret, control;
	u8 int_en;

	/* set Report Rate to Device Highest (>=80) and Sleep to normal */
	ret = synaptics_i2c_reg_set(client, DEV_CONTROL_REG, 0xc1);
	if (ret)
		return ret;

	/* set Interrupt Disable to Func20 / Enable to Func10) */
	int_en = (polling_req) ? 0 : INT_ENA_ABS_MSK | INT_ENA_REL_MSK;
	ret = synaptics_i2c_reg_set(client, INTERRUPT_EN_REG, int_en);
	if (ret)
		return ret;

	control = synaptics_i2c_reg_get(client, GENERAL_2D_CONTROL_REG);
	/* No Deceleration */
	control |= no_decel ? 1 << NO_DECELERATION : 0;
	/* Reduced Reporting */
	control |= reduce_report ? 1 << REDUCE_REPORTING : 0;
	/* No Filter */
	control |= no_filter ? 1 << NO_FILTER : 0;
	ret = synaptics_i2c_reg_set(client, GENERAL_2D_CONTROL_REG, control);
	if (ret)
		return ret;

	return 0;
}