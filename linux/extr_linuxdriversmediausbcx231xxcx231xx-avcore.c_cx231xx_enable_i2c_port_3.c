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
struct cx231xx {int port_3_switch_enabled; } ;

/* Variables and functions */
 int I2C_DEMOD_EN ; 
 int /*<<< orphan*/  PWR_CTL_EN ; 
 int /*<<< orphan*/  VRT_GET_REGISTER ; 
 int /*<<< orphan*/  VRT_SET_REGISTER ; 
 int cx231xx_read_ctrl_reg (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int cx231xx_write_ctrl_reg (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

int cx231xx_enable_i2c_port_3(struct cx231xx *dev, bool is_port_3)
{
	u8 value[4] = { 0, 0, 0, 0 };
	int status = 0;
	bool current_is_port_3;

	/*
	 * Should this code check dev->port_3_switch_enabled first
	 * to skip unnecessary reading of the register?
	 * If yes, the flag dev->port_3_switch_enabled must be initialized
	 * correctly.
	 */

	status = cx231xx_read_ctrl_reg(dev, VRT_GET_REGISTER,
				       PWR_CTL_EN, value, 4);
	if (status < 0)
		return status;

	current_is_port_3 = value[0] & I2C_DEMOD_EN ? true : false;

	/* Just return, if already using the right port */
	if (current_is_port_3 == is_port_3)
		return 0;

	if (is_port_3)
		value[0] |= I2C_DEMOD_EN;
	else
		value[0] &= ~I2C_DEMOD_EN;

	status = cx231xx_write_ctrl_reg(dev, VRT_SET_REGISTER,
					PWR_CTL_EN, value, 4);

	/* remember status of the switch for usage in is_tuner */
	if (status >= 0)
		dev->port_3_switch_enabled = is_port_3;

	return status;

}