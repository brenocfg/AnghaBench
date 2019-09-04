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
struct s3c_hwmon {int /*<<< orphan*/  lock; int /*<<< orphan*/  client; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int s3c_adc_read (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int s3c_hwmon_read_ch(struct device *dev,
			     struct s3c_hwmon *hwmon, int channel)
{
	int ret;

	ret = mutex_lock_interruptible(&hwmon->lock);
	if (ret < 0)
		return ret;

	dev_dbg(dev, "reading channel %d\n", channel);

	ret = s3c_adc_read(hwmon->client, channel);
	mutex_unlock(&hwmon->lock);

	return ret;
}