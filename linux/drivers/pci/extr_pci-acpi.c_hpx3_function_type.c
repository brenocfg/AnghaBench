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
typedef  int /*<<< orphan*/  u8 ;
struct pci_dev {scalar_t__ is_virtfn; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPX_FN_NORMAL ; 
 int /*<<< orphan*/  HPX_FN_SRIOV_PHYS ; 
 int /*<<< orphan*/  HPX_FN_SRIOV_VIRT ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_SRIOV ; 
 scalar_t__ pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 hpx3_function_type(struct pci_dev *dev)
{
	if (dev->is_virtfn)
		return HPX_FN_SRIOV_VIRT;
	else if (pci_find_ext_capability(dev, PCI_EXT_CAP_ID_SRIOV) > 0)
		return HPX_FN_SRIOV_PHYS;
	else
		return HPX_FN_NORMAL;
}