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
typedef  scalar_t__ u8 ;
struct stk_camera {int dummy; } ;

/* Variables and functions */
 int MAX_RETRIES ; 
 int /*<<< orphan*/  STK_IIC_OP ; 
 scalar_t__ STK_IIC_OP_TX ; 
 int /*<<< orphan*/  STK_IIC_STAT ; 
 scalar_t__ STK_IIC_STAT_TX_OK ; 
 int /*<<< orphan*/  STK_IIC_TX_INDEX ; 
 int /*<<< orphan*/  STK_IIC_TX_VALUE ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 scalar_t__ stk_camera_read_reg (struct stk_camera*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ stk_camera_write_reg (struct stk_camera*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int stk_sensor_outb(struct stk_camera *dev, u8 reg, u8 val)
{
	int i = 0;
	u8 tmpval = 0;

	if (stk_camera_write_reg(dev, STK_IIC_TX_INDEX, reg))
		return 1;
	if (stk_camera_write_reg(dev, STK_IIC_TX_VALUE, val))
		return 1;
	if (stk_camera_write_reg(dev, STK_IIC_OP, STK_IIC_OP_TX))
		return 1;
	do {
		if (stk_camera_read_reg(dev, STK_IIC_STAT, &tmpval))
			return 1;
		i++;
	} while (tmpval == 0 && i < MAX_RETRIES);
	if (tmpval != STK_IIC_STAT_TX_OK) {
		if (tmpval)
			pr_err("stk_sensor_outb failed, status=0x%02x\n",
			       tmpval);
		return 1;
	} else
		return 0;
}