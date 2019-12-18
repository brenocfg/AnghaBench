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
struct qlcnic_adapter {int flags; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int QLCNIC_DIAG_ENABLED ; 
 struct qlcnic_adapter* dev_get_drvdata (struct device*) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t qlcnic_store_diag_mode(struct device *dev,
				      struct device_attribute *attr,
				      const char *buf, size_t len)
{
	struct qlcnic_adapter *adapter = dev_get_drvdata(dev);
	unsigned long new;

	if (kstrtoul(buf, 2, &new))
		return -EINVAL;

	if (!!new != !!(adapter->flags & QLCNIC_DIAG_ENABLED))
		adapter->flags ^= QLCNIC_DIAG_ENABLED;

	return len;
}