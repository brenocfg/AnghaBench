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
struct i2c_timings {int bus_freq_hz; } ;
struct dw_i2c_dev {int functionality; int master_cfg; int /*<<< orphan*/  mode; struct i2c_timings timings; } ;

/* Variables and functions */
 int DW_IC_CON_MASTER ; 
 int DW_IC_CON_RESTART_EN ; 
 int DW_IC_CON_SLAVE_DISABLE ; 
 int DW_IC_CON_SPEED_FAST ; 
 int DW_IC_CON_SPEED_HIGH ; 
 int DW_IC_CON_SPEED_STD ; 
 int DW_IC_DEFAULT_FUNCTIONALITY ; 
 int /*<<< orphan*/  DW_IC_MASTER ; 
 int I2C_FUNC_10BIT_ADDR ; 

__attribute__((used)) static void i2c_dw_configure_master(struct dw_i2c_dev *dev)
{
	struct i2c_timings *t = &dev->timings;

	dev->functionality = I2C_FUNC_10BIT_ADDR | DW_IC_DEFAULT_FUNCTIONALITY;

	dev->master_cfg = DW_IC_CON_MASTER | DW_IC_CON_SLAVE_DISABLE |
			  DW_IC_CON_RESTART_EN;

	dev->mode = DW_IC_MASTER;

	switch (t->bus_freq_hz) {
	case 100000:
		dev->master_cfg |= DW_IC_CON_SPEED_STD;
		break;
	case 3400000:
		dev->master_cfg |= DW_IC_CON_SPEED_HIGH;
		break;
	default:
		dev->master_cfg |= DW_IC_CON_SPEED_FAST;
	}
}