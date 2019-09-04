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
typedef  int u32 ;
struct dpot_data {int rdac_mask; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  otp_en_mask; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int s32 ;

/* Variables and functions */
 int DPOT_ADDR_OTP_EN ; 
 int DPOT_RDAC_MASK ; 
 int DPOT_REG_TOL ; 
 int /*<<< orphan*/  EINVAL ; 
 struct dpot_data* dev_get_drvdata (struct device*) ; 
 int dpot_read (struct dpot_data*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t sysfs_show_reg(struct device *dev,
			      struct device_attribute *attr,
			      char *buf, u32 reg)
{
	struct dpot_data *data = dev_get_drvdata(dev);
	s32 value;

	if (reg & DPOT_ADDR_OTP_EN)
		return sprintf(buf, "%s\n",
			test_bit(DPOT_RDAC_MASK & reg, data->otp_en_mask) ?
			"enabled" : "disabled");


	mutex_lock(&data->update_lock);
	value = dpot_read(data, reg);
	mutex_unlock(&data->update_lock);

	if (value < 0)
		return -EINVAL;
	/*
	 * Let someone else deal with converting this ...
	 * the tolerance is a two-byte value where the MSB
	 * is a sign + integer value, and the LSB is a
	 * decimal value.  See page 18 of the AD5258
	 * datasheet (Rev. A) for more details.
	 */

	if (reg & DPOT_REG_TOL)
		return sprintf(buf, "0x%04x\n", value & 0xFFFF);
	else
		return sprintf(buf, "%u\n", value & data->rdac_mask);
}