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

/* Variables and functions */
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  create_workqueue (char*) ; 
 int /*<<< orphan*/  iommu_present (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_bus_type ; 
 int /*<<< orphan*/  usnic_err (char*,...) ; 
 int /*<<< orphan*/  usnic_uiom_wq ; 

int usnic_uiom_init(char *drv_name)
{
	if (!iommu_present(&pci_bus_type)) {
		usnic_err("IOMMU required but not present or enabled.  USNIC QPs will not function w/o enabling IOMMU\n");
		return -EPERM;
	}

	usnic_uiom_wq = create_workqueue(drv_name);
	if (!usnic_uiom_wq) {
		usnic_err("Unable to alloc wq for drv %s\n", drv_name);
		return -ENOMEM;
	}

	return 0;
}