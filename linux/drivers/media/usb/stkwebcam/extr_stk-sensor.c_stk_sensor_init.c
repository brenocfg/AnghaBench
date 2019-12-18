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
struct stk_camera {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COM7_RESET ; 
 int ENODEV ; 
 int /*<<< orphan*/  REG_COM7 ; 
 int /*<<< orphan*/  REG_MIDH ; 
 int /*<<< orphan*/  REG_MIDL ; 
 int /*<<< orphan*/  REG_PID ; 
 int /*<<< orphan*/  REG_VER ; 
 int /*<<< orphan*/  SENSOR_ADDRESS ; 
 int /*<<< orphan*/  STK_IIC_ADDR ; 
 int /*<<< orphan*/  STK_IIC_ENABLE ; 
 int /*<<< orphan*/  STK_IIC_ENABLE_YES ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  ov_initvals ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ stk_camera_write_reg (struct stk_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stk_sensor_inb (struct stk_camera*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stk_sensor_outb (struct stk_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stk_sensor_write_regvals (struct stk_camera*,int /*<<< orphan*/ ) ; 

int stk_sensor_init(struct stk_camera *dev)
{
	u8 idl = 0;
	u8 idh = 0;

	if (stk_camera_write_reg(dev, STK_IIC_ENABLE, STK_IIC_ENABLE_YES)
		|| stk_camera_write_reg(dev, STK_IIC_ADDR, SENSOR_ADDRESS)
		|| stk_sensor_outb(dev, REG_COM7, COM7_RESET)) {
		pr_err("Sensor resetting failed\n");
		return -ENODEV;
	}
	msleep(10);
	/* Read the manufacturer ID: ov = 0x7FA2 */
	if (stk_sensor_inb(dev, REG_MIDH, &idh)
	    || stk_sensor_inb(dev, REG_MIDL, &idl)) {
		pr_err("Strange error reading sensor ID\n");
		return -ENODEV;
	}
	if (idh != 0x7f || idl != 0xa2) {
		pr_err("Huh? you don't have a sensor from ovt\n");
		return -ENODEV;
	}
	if (stk_sensor_inb(dev, REG_PID, &idh)
	    || stk_sensor_inb(dev, REG_VER, &idl)) {
		pr_err("Could not read sensor model\n");
		return -ENODEV;
	}
	stk_sensor_write_regvals(dev, ov_initvals);
	msleep(10);
	pr_info("OmniVision sensor detected, id %02X%02X at address %x\n",
		idh, idl, SENSOR_ADDRESS);
	return 0;
}