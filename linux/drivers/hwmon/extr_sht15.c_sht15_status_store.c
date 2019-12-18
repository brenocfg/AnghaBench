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
struct sht15_data {int val_status; int /*<<< orphan*/  read_lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int SHT15_STATUS_HEATER ; 
 struct sht15_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sht15_send_status (struct sht15_data*,int) ; 

__attribute__((used)) static ssize_t sht15_status_store(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t count)
{
	int ret;
	struct sht15_data *data = dev_get_drvdata(dev);
	long value;
	u8 status;

	if (kstrtol(buf, 10, &value))
		return -EINVAL;

	mutex_lock(&data->read_lock);
	status = data->val_status & 0x07;
	if (!!value)
		status |= SHT15_STATUS_HEATER;
	else
		status &= ~SHT15_STATUS_HEATER;

	ret = sht15_send_status(data, status);
	mutex_unlock(&data->read_lock);

	return ret ? ret : count;
}