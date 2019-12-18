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
struct tegra_fuse {int dummy; } ;
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct device {int dummy; } ;
struct bin_attribute {scalar_t__ size; } ;
typedef  int ssize_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 struct tegra_fuse* dev_get_drvdata (struct device*) ; 
 char fuse_readb (struct tegra_fuse*,scalar_t__) ; 
 struct device* kobj_to_dev (struct kobject*) ; 

__attribute__((used)) static ssize_t fuse_read(struct file *fd, struct kobject *kobj,
			 struct bin_attribute *attr, char *buf,
			 loff_t pos, size_t size)
{
	struct device *dev = kobj_to_dev(kobj);
	struct tegra_fuse *fuse = dev_get_drvdata(dev);
	int i;

	if (pos < 0 || pos >= attr->size)
		return 0;

	if (size > attr->size - pos)
		size = attr->size - pos;

	for (i = 0; i < size; i++)
		buf[i] = fuse_readb(fuse, pos + i);

	return i;
}