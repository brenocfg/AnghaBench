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
typedef  int /*<<< orphan*/  u8 ;
struct fschmd_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/  global_control; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  FSCHMD_CONTROL_ALERT_LED ; 
 int /*<<< orphan*/  FSCHMD_REG_CONTROL ; 
 struct fschmd_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t alert_led_store(struct device *dev,
	struct device_attribute *devattr, const char *buf, size_t count)
{
	u8 reg;
	struct fschmd_data *data = dev_get_drvdata(dev);
	unsigned long v;
	int err;

	err = kstrtoul(buf, 10, &v);
	if (err)
		return err;

	mutex_lock(&data->update_lock);

	reg = i2c_smbus_read_byte_data(to_i2c_client(dev), FSCHMD_REG_CONTROL);

	if (v)
		reg |= FSCHMD_CONTROL_ALERT_LED;
	else
		reg &= ~FSCHMD_CONTROL_ALERT_LED;

	i2c_smbus_write_byte_data(to_i2c_client(dev), FSCHMD_REG_CONTROL, reg);

	data->global_control = reg;

	mutex_unlock(&data->update_lock);

	return count;
}