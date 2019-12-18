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
struct qlcnic_adapter {struct pci_dev* pdev; } ;
struct pci_dev {unsigned short subsystem_vendor; scalar_t__ device; scalar_t__ subsystem_device; } ;
struct TYPE_2__ {unsigned short sub_vendor; scalar_t__ sub_device; } ;

/* Variables and functions */
 scalar_t__ PCI_DEVICE_ID_QLOGIC_QLE824X ; 
 scalar_t__ PCI_DEVICE_ID_QLOGIC_QLE834X ; 
 TYPE_1__* qlcnic_boards ; 

__attribute__((used)) static bool qlcnic_validate_subsystem_id(struct qlcnic_adapter *adapter,
					 int index)
{
	struct pci_dev *pdev = adapter->pdev;
	unsigned short subsystem_vendor;
	bool ret = true;

	subsystem_vendor = pdev->subsystem_vendor;

	if (pdev->device == PCI_DEVICE_ID_QLOGIC_QLE824X ||
	    pdev->device == PCI_DEVICE_ID_QLOGIC_QLE834X) {
		if (qlcnic_boards[index].sub_vendor == subsystem_vendor &&
		    qlcnic_boards[index].sub_device == pdev->subsystem_device)
			ret = true;
		else
			ret = false;
	}

	return ret;
}