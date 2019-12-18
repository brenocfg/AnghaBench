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
typedef  int u16 ;
struct ov5640_dev {int dummy; } ;

/* Variables and functions */
 int ov5640_read_reg (struct ov5640_dev*,int,scalar_t__*) ; 

__attribute__((used)) static int ov5640_read_reg16(struct ov5640_dev *sensor, u16 reg, u16 *val)
{
	u8 hi, lo;
	int ret;

	ret = ov5640_read_reg(sensor, reg, &hi);
	if (ret)
		return ret;
	ret = ov5640_read_reg(sensor, reg + 1, &lo);
	if (ret)
		return ret;

	*val = ((u16)hi << 8) | (u16)lo;
	return 0;
}