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
struct nsim_bus_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int kstrtouint (char const*,int /*<<< orphan*/ ,unsigned int*) ; 
 int nsim_dev_port_add (struct nsim_bus_dev*,unsigned int) ; 
 struct nsim_bus_dev* to_nsim_bus_dev (struct device*) ; 

__attribute__((used)) static ssize_t
new_port_store(struct device *dev, struct device_attribute *attr,
	       const char *buf, size_t count)
{
	struct nsim_bus_dev *nsim_bus_dev = to_nsim_bus_dev(dev);
	unsigned int port_index;
	int ret;

	ret = kstrtouint(buf, 0, &port_index);
	if (ret)
		return ret;
	ret = nsim_dev_port_add(nsim_bus_dev, port_index);
	return ret ? ret : count;
}