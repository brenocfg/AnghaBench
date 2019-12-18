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
struct fam15h_power_data {unsigned long power_period; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long MAX_INTERVAL ; 
 struct fam15h_power_data* dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t power1_average_interval_store(struct device *dev,
					     struct device_attribute *attr,
					     const char *buf, size_t count)
{
	struct fam15h_power_data *data = dev_get_drvdata(dev);
	unsigned long temp;
	int ret;

	ret = kstrtoul(buf, 10, &temp);
	if (ret)
		return ret;

	if (temp > MAX_INTERVAL)
		return -EINVAL;

	/* the interval value should be greater than 0 */
	if (temp <= 0)
		return -EINVAL;

	data->power_period = temp;

	return count;
}