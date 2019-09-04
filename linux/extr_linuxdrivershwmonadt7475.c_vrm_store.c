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
struct adt7475_data {long vrm; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 struct adt7475_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ kstrtol (char const*,int,long*) ; 

__attribute__((used)) static ssize_t vrm_store(struct device *dev, struct device_attribute *devattr,
			 const char *buf, size_t count)
{
	struct adt7475_data *data = dev_get_drvdata(dev);
	long val;

	if (kstrtol(buf, 10, &val))
		return -EINVAL;
	if (val < 0 || val > 255)
		return -EINVAL;
	data->vrm = val;

	return count;
}