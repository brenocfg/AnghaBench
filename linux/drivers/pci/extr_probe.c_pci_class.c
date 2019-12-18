#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {TYPE_2__* physfn; scalar_t__ is_virtfn; } ;
struct TYPE_4__ {TYPE_1__* sriov; } ;
struct TYPE_3__ {int /*<<< orphan*/  class; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_CLASS_REVISION ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 pci_class(struct pci_dev *dev)
{
	u32 class;

#ifdef CONFIG_PCI_IOV
	if (dev->is_virtfn)
		return dev->physfn->sriov->class;
#endif
	pci_read_config_dword(dev, PCI_CLASS_REVISION, &class);
	return class;
}