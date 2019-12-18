#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  umode_t ;
struct pci_dev {int /*<<< orphan*/  aer_stats; } ;
struct kobject {int dummy; } ;
struct device {int dummy; } ;
struct attribute {int /*<<< orphan*/  mode; } ;
struct TYPE_6__ {struct attribute attr; } ;
struct TYPE_5__ {struct attribute attr; } ;
struct TYPE_4__ {struct attribute attr; } ;

/* Variables and functions */
 scalar_t__ PCI_EXP_TYPE_ROOT_PORT ; 
 TYPE_3__ dev_attr_aer_rootport_total_err_cor ; 
 TYPE_2__ dev_attr_aer_rootport_total_err_fatal ; 
 TYPE_1__ dev_attr_aer_rootport_total_err_nonfatal ; 
 struct device* kobj_to_dev (struct kobject*) ; 
 scalar_t__ pci_pcie_type (struct pci_dev*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static umode_t aer_stats_attrs_are_visible(struct kobject *kobj,
					   struct attribute *a, int n)
{
	struct device *dev = kobj_to_dev(kobj);
	struct pci_dev *pdev = to_pci_dev(dev);

	if (!pdev->aer_stats)
		return 0;

	if ((a == &dev_attr_aer_rootport_total_err_cor.attr ||
	     a == &dev_attr_aer_rootport_total_err_fatal.attr ||
	     a == &dev_attr_aer_rootport_total_err_nonfatal.attr) &&
	    pci_pcie_type(pdev) != PCI_EXP_TYPE_ROOT_PORT)
		return 0;

	return a->mode;
}