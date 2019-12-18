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
struct dpot_data {unsigned long rdac_mask; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  otp_en_mask; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int DPOT_ADDR_EEPROM ; 
 int DPOT_ADDR_OTP ; 
 int DPOT_ADDR_OTP_EN ; 
 int DPOT_RDAC_MASK ; 
 size_t EPERM ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 struct dpot_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dpot_write (struct dpot_data*,int,unsigned long) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 scalar_t__ sysfs_streq (char const*,char*) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t sysfs_set_reg(struct device *dev,
			     struct device_attribute *attr,
			     const char *buf, size_t count, u32 reg)
{
	struct dpot_data *data = dev_get_drvdata(dev);
	unsigned long value;
	int err;

	if (reg & DPOT_ADDR_OTP_EN) {
		if (sysfs_streq(buf, "enabled"))
			set_bit(DPOT_RDAC_MASK & reg, data->otp_en_mask);
		else
			clear_bit(DPOT_RDAC_MASK & reg, data->otp_en_mask);

		return count;
	}

	if ((reg & DPOT_ADDR_OTP) &&
		!test_bit(DPOT_RDAC_MASK & reg, data->otp_en_mask))
		return -EPERM;

	err = kstrtoul(buf, 10, &value);
	if (err)
		return err;

	if (value > data->rdac_mask)
		value = data->rdac_mask;

	mutex_lock(&data->update_lock);
	dpot_write(data, reg, value);
	if (reg & DPOT_ADDR_EEPROM)
		msleep(26);	/* Sleep while the EEPROM updates */
	else if (reg & DPOT_ADDR_OTP)
		msleep(400);	/* Sleep while the OTP updates */
	mutex_unlock(&data->update_lock);

	return count;
}