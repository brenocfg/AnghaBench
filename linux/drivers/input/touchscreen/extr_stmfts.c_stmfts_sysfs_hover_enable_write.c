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
struct stmfts_data {unsigned long hover_enabled; int /*<<< orphan*/  mutex; int /*<<< orphan*/  client; scalar_t__ running; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  STMFTS_SS_HOVER_SENSE_OFF ; 
 int /*<<< orphan*/  STMFTS_SS_HOVER_SENSE_ON ; 
 struct stmfts_data* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_write_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t stmfts_sysfs_hover_enable_write(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t len)
{
	struct stmfts_data *sdata = dev_get_drvdata(dev);
	unsigned long value;
	int err = 0;

	if (kstrtoul(buf, 0, &value))
		return -EINVAL;

	mutex_lock(&sdata->mutex);

	if (value & sdata->hover_enabled)
		goto out;

	if (sdata->running)
		err = i2c_smbus_write_byte(sdata->client,
					   value ? STMFTS_SS_HOVER_SENSE_ON :
						   STMFTS_SS_HOVER_SENSE_OFF);

	if (!err)
		sdata->hover_enabled = !!value;

out:
	mutex_unlock(&sdata->mutex);

	return len;
}