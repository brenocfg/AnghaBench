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
struct bq2415x_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ2415X_MASK_VO ; 
 int /*<<< orphan*/  BQ2415X_REG_VOLTAGE ; 
 int /*<<< orphan*/  BQ2415X_SHIFT_VO ; 
 int EINVAL ; 
 int bq2415x_i2c_write_mask (struct bq2415x_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bq2415x_set_battery_regulation_voltage(struct bq2415x_device *bq,
						  int mV)
{
	int val = (mV/10 - 350) / 2;

	/*
	 * According to datasheet, maximum battery regulation voltage is
	 * 4440mV which is b101111 = 47.
	 */
	if (val < 0)
		val = 0;
	else if (val > 47)
		return -EINVAL;

	return bq2415x_i2c_write_mask(bq, BQ2415X_REG_VOLTAGE, val,
			BQ2415X_MASK_VO, BQ2415X_SHIFT_VO);
}