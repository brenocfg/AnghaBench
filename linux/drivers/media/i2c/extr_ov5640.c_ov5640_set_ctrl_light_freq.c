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
struct ov5640_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  OV5640_REG_HZ5060_CTRL00 ; 
 int /*<<< orphan*/  OV5640_REG_HZ5060_CTRL01 ; 
 int V4L2_CID_POWER_LINE_FREQUENCY_50HZ ; 
 int V4L2_CID_POWER_LINE_FREQUENCY_AUTO ; 
 int ov5640_mod_reg (struct ov5640_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov5640_set_ctrl_light_freq(struct ov5640_dev *sensor, int value)
{
	int ret;

	ret = ov5640_mod_reg(sensor, OV5640_REG_HZ5060_CTRL01, BIT(7),
			     (value == V4L2_CID_POWER_LINE_FREQUENCY_AUTO) ?
			     0 : BIT(7));
	if (ret)
		return ret;

	return ov5640_mod_reg(sensor, OV5640_REG_HZ5060_CTRL00, BIT(2),
			      (value == V4L2_CID_POWER_LINE_FREQUENCY_50HZ) ?
			      BIT(2) : 0);
}