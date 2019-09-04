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
struct cx231xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TS1_CFG_REG ; 
 int /*<<< orphan*/  TS_MODE_REG ; 
 int /*<<< orphan*/  VRT_SET_REGISTER ; 
 int /*<<< orphan*/  cx231xx_write_ctrl_reg (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

void cx231xx_stop_TS1(struct cx231xx *dev)
{
	u8 val[4] = { 0, 0, 0, 0 };

	val[0] = 0x00;
	val[1] = 0x03;
	val[2] = 0x00;
	val[3] = 0x00;
	cx231xx_write_ctrl_reg(dev, VRT_SET_REGISTER,
			TS_MODE_REG, val, 4);

	val[0] = 0x00;
	val[1] = 0x70;
	val[2] = 0x04;
	val[3] = 0x00;
	cx231xx_write_ctrl_reg(dev, VRT_SET_REGISTER,
			TS1_CFG_REG, val, 4);
}