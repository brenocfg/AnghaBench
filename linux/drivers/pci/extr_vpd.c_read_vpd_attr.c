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
struct pci_dev {int dummy; } ;
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct bin_attribute {scalar_t__ size; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  size_t loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  kobj_to_dev (struct kobject*) ; 
 int /*<<< orphan*/  pci_read_vpd (struct pci_dev*,size_t,size_t,char*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t read_vpd_attr(struct file *filp, struct kobject *kobj,
			     struct bin_attribute *bin_attr, char *buf,
			     loff_t off, size_t count)
{
	struct pci_dev *dev = to_pci_dev(kobj_to_dev(kobj));

	if (bin_attr->size > 0) {
		if (off > bin_attr->size)
			count = 0;
		else if (count > bin_attr->size - off)
			count = bin_attr->size - off;
	}

	return pci_read_vpd(dev, off, count, buf);
}