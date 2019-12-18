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
struct pci_dev {scalar_t__ is_virtfn; } ;
struct notifier_block {int dummy; } ;
struct dmar_pci_notify_info {int dummy; } ;

/* Variables and functions */
 unsigned long BUS_NOTIFY_ADD_DEVICE ; 
 unsigned long BUS_NOTIFY_REMOVED_DEVICE ; 
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
 struct dmar_pci_notify_info* dmar_alloc_pci_notify_info (struct pci_dev*,unsigned long) ; 
 int /*<<< orphan*/  dmar_free_pci_notify_info (struct dmar_pci_notify_info*) ; 
 int /*<<< orphan*/  dmar_global_lock ; 
 int /*<<< orphan*/  dmar_pci_bus_add_dev (struct dmar_pci_notify_info*) ; 
 int /*<<< orphan*/  dmar_pci_bus_del_dev (struct dmar_pci_notify_info*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 struct pci_dev* to_pci_dev (void*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dmar_pci_bus_notifier(struct notifier_block *nb,
				 unsigned long action, void *data)
{
	struct pci_dev *pdev = to_pci_dev(data);
	struct dmar_pci_notify_info *info;

	/* Only care about add/remove events for physical functions.
	 * For VFs we actually do the lookup based on the corresponding
	 * PF in device_to_iommu() anyway. */
	if (pdev->is_virtfn)
		return NOTIFY_DONE;
	if (action != BUS_NOTIFY_ADD_DEVICE &&
	    action != BUS_NOTIFY_REMOVED_DEVICE)
		return NOTIFY_DONE;

	info = dmar_alloc_pci_notify_info(pdev, action);
	if (!info)
		return NOTIFY_DONE;

	down_write(&dmar_global_lock);
	if (action == BUS_NOTIFY_ADD_DEVICE)
		dmar_pci_bus_add_dev(info);
	else if (action == BUS_NOTIFY_REMOVED_DEVICE)
		dmar_pci_bus_del_dev(info);
	up_write(&dmar_global_lock);

	dmar_free_pci_notify_info(info);

	return NOTIFY_OK;
}