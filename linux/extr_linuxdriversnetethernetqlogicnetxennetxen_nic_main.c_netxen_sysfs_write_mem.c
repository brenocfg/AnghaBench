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
typedef  int /*<<< orphan*/  u64 ;
struct netxen_adapter {scalar_t__ (* pci_mem_write ) (struct netxen_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct device {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EIO ; 
 struct netxen_adapter* dev_get_drvdata (struct device*) ; 
 struct device* kobj_to_dev (struct kobject*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,size_t) ; 
 int netxen_sysfs_validate_mem (struct netxen_adapter*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ stub1 (struct netxen_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t netxen_sysfs_write_mem(struct file *filp, struct kobject *kobj,
		struct bin_attribute *attr, char *buf,
		loff_t offset, size_t size)
{
	struct device *dev = kobj_to_dev(kobj);
	struct netxen_adapter *adapter = dev_get_drvdata(dev);
	u64 data;
	int ret;

	ret = netxen_sysfs_validate_mem(adapter, offset, size);
	if (ret != 0)
		return ret;

	memcpy(&data, buf, size);

	if (adapter->pci_mem_write(adapter, offset, data))
		return -EIO;

	return size;
}