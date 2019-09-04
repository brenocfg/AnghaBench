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
struct max6650_data {int /*<<< orphan*/  update_lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 unsigned long ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  const MAX6650_CFG_MODE_CLOSED_LOOP ; 
 int /*<<< orphan*/  const MAX6650_CFG_MODE_OFF ; 
 int /*<<< orphan*/  const MAX6650_CFG_MODE_ON ; 
 int /*<<< orphan*/  const MAX6650_CFG_MODE_OPEN_LOOP ; 
 struct max6650_data* dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  max6650_set_operating_mode (struct max6650_data*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t pwm1_enable_store(struct device *dev,
				 struct device_attribute *devattr,
				 const char *buf, size_t count)
{
	struct max6650_data *data = dev_get_drvdata(dev);
	unsigned long mode;
	int err;
	const u8 max6650_modes[] = {
		MAX6650_CFG_MODE_ON,
		MAX6650_CFG_MODE_OPEN_LOOP,
		MAX6650_CFG_MODE_CLOSED_LOOP,
		MAX6650_CFG_MODE_OFF,
		};

	err = kstrtoul(buf, 10, &mode);
	if (err)
		return err;

	if (mode >= ARRAY_SIZE(max6650_modes))
		return -EINVAL;

	mutex_lock(&data->update_lock);

	max6650_set_operating_mode(data, max6650_modes[mode]);

	mutex_unlock(&data->update_lock);

	return count;
}