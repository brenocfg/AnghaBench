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
 int i2c_smbus_read_byte_data (struct i2c_client*,int) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int,int) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t als_sensing_range_store(struct device *dev,
		struct device_attribute *attr, const  char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	int ret_val;
	unsigned long val;

	ret_val = kstrtoul(buf, 10, &val);
	if (ret_val)
		return ret_val;

	if (val < 1 || val > 64000)
		return -EINVAL;

	/* Pick the smallest sensor range that will meet our requirements */
	if (val <= 1000)
		val = 1;
	else if (val <= 4000)
		val = 2;
	else if (val <= 16000)
		val = 3;
	else
		val = 4;

	ret_val = i2c_smbus_read_byte_data(client, 0x00);
	if (ret_val < 0)
		return ret_val;

	ret_val &= 0xFC; /*reset the bit before setting them */
	ret_val |= val - 1;
	ret_val = i2c_smbus_write_byte_data(client, 0x00, ret_val);

	if (ret_val < 0)
		return ret_val;
	return count;
}