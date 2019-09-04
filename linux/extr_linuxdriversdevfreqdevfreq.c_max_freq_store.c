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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct devfreq {unsigned long min_freq; unsigned long max_freq; int /*<<< orphan*/  lock; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sscanf (char const*,char*,unsigned long*) ; 
 struct devfreq* to_devfreq (struct device*) ; 
 int /*<<< orphan*/  update_devfreq (struct devfreq*) ; 

__attribute__((used)) static ssize_t max_freq_store(struct device *dev, struct device_attribute *attr,
			      const char *buf, size_t count)
{
	struct devfreq *df = to_devfreq(dev);
	unsigned long value;
	int ret;
	unsigned long min;

	ret = sscanf(buf, "%lu", &value);
	if (ret != 1)
		return -EINVAL;

	mutex_lock(&df->lock);
	min = df->min_freq;
	if (value && min && value < min) {
		ret = -EINVAL;
		goto unlock;
	}

	df->max_freq = value;
	update_devfreq(df);
	ret = count;
unlock:
	mutex_unlock(&df->lock);
	return ret;
}