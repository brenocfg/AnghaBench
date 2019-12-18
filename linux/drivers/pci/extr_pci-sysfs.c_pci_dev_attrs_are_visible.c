#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  umode_t ;
struct pci_dev {int class; } ;
struct kobject {int dummy; } ;
struct device {int dummy; } ;
struct attribute {int /*<<< orphan*/  mode; } ;
struct TYPE_2__ {struct attribute attr; } ;

/* Variables and functions */
 int PCI_CLASS_DISPLAY_VGA ; 
 TYPE_1__ dev_attr_boot_vga ; 
 struct device* kobj_to_dev (struct kobject*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static umode_t pci_dev_attrs_are_visible(struct kobject *kobj,
					 struct attribute *a, int n)
{
	struct device *dev = kobj_to_dev(kobj);
	struct pci_dev *pdev = to_pci_dev(dev);

	if (a == &dev_attr_boot_vga.attr)
		if ((pdev->class >> 8) != PCI_CLASS_DISPLAY_VGA)
			return 0;

	return a->mode;
}