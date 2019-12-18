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
struct ov5640_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV5640_REG_HZ5060_CTRL00 ; 
 int /*<<< orphan*/  OV5640_REG_HZ5060_CTRL01 ; 
 int /*<<< orphan*/  OV5640_REG_SIGMADELTA_CTRL0C ; 
 int ov5640_read_reg (struct ov5640_dev*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ov5640_get_light_freq(struct ov5640_dev *sensor)
{
	/* get banding filter value */
	int ret, light_freq = 0;
	u8 temp, temp1;

	ret = ov5640_read_reg(sensor, OV5640_REG_HZ5060_CTRL01, &temp);
	if (ret)
		return ret;

	if (temp & 0x80) {
		/* manual */
		ret = ov5640_read_reg(sensor, OV5640_REG_HZ5060_CTRL00,
				      &temp1);
		if (ret)
			return ret;
		if (temp1 & 0x04) {
			/* 50Hz */
			light_freq = 50;
		} else {
			/* 60Hz */
			light_freq = 60;
		}
	} else {
		/* auto */
		ret = ov5640_read_reg(sensor, OV5640_REG_SIGMADELTA_CTRL0C,
				      &temp1);
		if (ret)
			return ret;

		if (temp1 & 0x01) {
			/* 50Hz */
			light_freq = 50;
		} else {
			/* 60Hz */
		}
	}

	return light_freq;
}