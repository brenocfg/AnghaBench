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
struct pm860x_battery_info {int /*<<< orphan*/  i2c; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PM8607_CHG_CTRL2 ; 
 int pm860x_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pm860x_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int set_charger_current(struct pm860x_battery_info *info, int data,
			       int *old)
{
	int ret;

	if (data < 50 || data > 1600 || !old)
		return -EINVAL;

	data = ((data - 50) / 50) & 0x1f;
	*old = pm860x_reg_read(info->i2c, PM8607_CHG_CTRL2);
	*old = (*old & 0x1f) * 50 + 50;
	ret = pm860x_set_bits(info->i2c, PM8607_CHG_CTRL2, 0x1f, data);
	if (ret < 0)
		return ret;
	return 0;
}