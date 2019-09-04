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
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int isl29003_set_resolution (struct i2c_client*,unsigned long) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t isl29003_store_resolution(struct device *dev,
					 struct device_attribute *attr,
					 const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	unsigned long val;
	int ret;

	ret = kstrtoul(buf, 10, &val);
	if (ret)
		return ret;

	if (val > 3)
		return -EINVAL;

	ret = isl29003_set_resolution(client, val);
	if (ret < 0)
		return ret;

	return count;
}