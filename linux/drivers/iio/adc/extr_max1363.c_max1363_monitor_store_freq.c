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
struct max1363_state {int monitor_speed; } ;
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned long*) ; 
 int /*<<< orphan*/  EINVAL ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct max1363_state* iio_priv (struct iio_dev*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 unsigned long* max1363_monitor_speeds ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t max1363_monitor_store_freq(struct device *dev,
					struct device_attribute *attr,
					const char *buf,
					size_t len)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct max1363_state *st = iio_priv(indio_dev);
	int i, ret;
	unsigned long val;
	bool found = false;

	ret = kstrtoul(buf, 10, &val);
	if (ret)
		return -EINVAL;
	for (i = 0; i < ARRAY_SIZE(max1363_monitor_speeds); i++)
		if (val == max1363_monitor_speeds[i]) {
			found = true;
			break;
		}
	if (!found)
		return -EINVAL;

	mutex_lock(&indio_dev->mlock);
	st->monitor_speed = i;
	mutex_unlock(&indio_dev->mlock);

	return 0;
}