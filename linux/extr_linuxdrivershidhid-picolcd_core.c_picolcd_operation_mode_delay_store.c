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
struct picolcd_data {unsigned int opmode_delay; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 struct picolcd_data* dev_get_drvdata (struct device*) ; 
 int sscanf (char const*,char*,unsigned int*) ; 

__attribute__((used)) static ssize_t picolcd_operation_mode_delay_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct picolcd_data *data = dev_get_drvdata(dev);
	unsigned u;
	if (sscanf(buf, "%u", &u) != 1)
		return -EINVAL;
	if (u > 30000)
		return -EINVAL;
	else
		data->opmode_delay = u;
	return count;
}