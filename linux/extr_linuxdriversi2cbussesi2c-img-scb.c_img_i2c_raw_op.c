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
struct img_i2c {int at_cur_cmd; int at_cur_data; scalar_t__ raw_timeout; } ;

/* Variables and functions */
 int OVERRIDE_CMD_MASK ; 
 int OVERRIDE_CMD_SHIFT ; 
 int OVERRIDE_DATA_SHIFT ; 
 int OVERRIDE_DIRECT ; 
 int OVERRIDE_LINE_OVR_EN ; 
 int OVERRIDE_MASTER ; 
 int OVERRIDE_SCLKEN_OVR ; 
 int OVERRIDE_SDATEN_OVR ; 
 int /*<<< orphan*/  SCB_OVERRIDE_REG ; 
 int /*<<< orphan*/  img_i2c_writel (struct img_i2c*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void img_i2c_raw_op(struct img_i2c *i2c)
{
	i2c->raw_timeout = 0;
	img_i2c_writel(i2c, SCB_OVERRIDE_REG,
		OVERRIDE_SCLKEN_OVR |
		OVERRIDE_SDATEN_OVR |
		OVERRIDE_MASTER |
		OVERRIDE_LINE_OVR_EN |
		OVERRIDE_DIRECT |
		((i2c->at_cur_cmd & OVERRIDE_CMD_MASK) << OVERRIDE_CMD_SHIFT) |
		(i2c->at_cur_data << OVERRIDE_DATA_SHIFT));
}