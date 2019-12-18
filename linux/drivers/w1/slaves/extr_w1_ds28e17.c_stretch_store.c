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
struct w1_slave {struct w1_f19_data* family_data; } ;
struct w1_f19_data {char stretch; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 struct w1_slave* dev_to_w1_slave (struct device*) ; 

__attribute__((used)) static ssize_t stretch_store(struct device *dev, struct device_attribute *attr,
			      const char *buf, size_t count)
{
	struct w1_slave *sl = dev_to_w1_slave(dev);
	struct w1_f19_data *data = sl->family_data;

	/* Valid values are '1' to '9' */
	if (count < 1 || count > 2 || !buf)
		return -EINVAL;
	if (count == 2 && buf[1] != '\n')
		return -EINVAL;
	if (buf[0] < '1' || buf[0] > '9')
		return -EINVAL;

	/* Set busy stretch value. */
	data->stretch = buf[0] & 0x0F;

	/* Return bytes written. */
	return count;
}