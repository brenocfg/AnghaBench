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
struct ov5640_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV5640_REG_AEC_PK_EXPOSURE_HI ; 
 int /*<<< orphan*/  OV5640_REG_AEC_PK_EXPOSURE_LO ; 
 int /*<<< orphan*/  OV5640_REG_AEC_PK_EXPOSURE_MED ; 
 int ov5640_read_reg (struct ov5640_dev*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int ov5640_get_exposure(struct ov5640_dev *sensor)
{
	int exp, ret;
	u8 temp;

	ret = ov5640_read_reg(sensor, OV5640_REG_AEC_PK_EXPOSURE_HI, &temp);
	if (ret)
		return ret;
	exp = ((int)temp & 0x0f) << 16;
	ret = ov5640_read_reg(sensor, OV5640_REG_AEC_PK_EXPOSURE_MED, &temp);
	if (ret)
		return ret;
	exp |= ((int)temp << 8);
	ret = ov5640_read_reg(sensor, OV5640_REG_AEC_PK_EXPOSURE_LO, &temp);
	if (ret)
		return ret;
	exp |= (int)temp;

	return exp >> 4;
}