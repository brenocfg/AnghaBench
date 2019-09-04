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
struct pci_driver {TYPE_1__* err_handler; } ;
struct pci_dev {scalar_t__ hdr_type; int /*<<< orphan*/  bus; } ;
struct eeh_rmv_data {int removed; int /*<<< orphan*/  edev_list; } ;
struct eeh_dev {int /*<<< orphan*/  rmv_list; scalar_t__ physfn; int /*<<< orphan*/  mode; int /*<<< orphan*/  bus; int /*<<< orphan*/  pe; } ;
struct TYPE_2__ {scalar_t__ slot_reset; scalar_t__ error_detected; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEH_DEV_DISCONNECTED ; 
 scalar_t__ PCI_HEADER_TYPE_BRIDGE ; 
 scalar_t__ eeh_dev_removed (struct eeh_dev*) ; 
 struct pci_dev* eeh_dev_to_pci_dev (struct eeh_dev*) ; 
 struct pci_driver* eeh_pcid_get (struct pci_dev*) ; 
 int /*<<< orphan*/  eeh_pcid_put (struct pci_dev*) ; 
 scalar_t__ eeh_pe_passed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_lock_rescan_remove () ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_stop_and_remove_bus_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_unlock_rescan_remove () ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *eeh_rmv_device(struct eeh_dev *edev, void *userdata)
{
	struct pci_driver *driver;
	struct pci_dev *dev = eeh_dev_to_pci_dev(edev);
	struct eeh_rmv_data *rmv_data = (struct eeh_rmv_data *)userdata;
	int *removed = rmv_data ? &rmv_data->removed : NULL;

	/*
	 * Actually, we should remove the PCI bridges as well.
	 * However, that's lots of complexity to do that,
	 * particularly some of devices under the bridge might
	 * support EEH. So we just care about PCI devices for
	 * simplicity here.
	 */
	if (!dev || (dev->hdr_type == PCI_HEADER_TYPE_BRIDGE))
		return NULL;

	/*
	 * We rely on count-based pcibios_release_device() to
	 * detach permanently offlined PEs. Unfortunately, that's
	 * not reliable enough. We might have the permanently
	 * offlined PEs attached, but we needn't take care of
	 * them and their child devices.
	 */
	if (eeh_dev_removed(edev))
		return NULL;

	if (removed) {
		if (eeh_pe_passed(edev->pe))
			return NULL;
		driver = eeh_pcid_get(dev);
		if (driver) {
			if (driver->err_handler &&
			    driver->err_handler->error_detected &&
			    driver->err_handler->slot_reset) {
				eeh_pcid_put(dev);
				return NULL;
			}
			eeh_pcid_put(dev);
		}
	}

	/* Remove it from PCI subsystem */
	pr_debug("EEH: Removing %s without EEH sensitive driver\n",
		 pci_name(dev));
	edev->bus = dev->bus;
	edev->mode |= EEH_DEV_DISCONNECTED;
	if (removed)
		(*removed)++;

	if (edev->physfn) {
#ifdef CONFIG_PCI_IOV
		struct pci_dn *pdn = eeh_dev_to_pdn(edev);

		pci_iov_remove_virtfn(edev->physfn, pdn->vf_index);
		edev->pdev = NULL;

		/*
		 * We have to set the VF PE number to invalid one, which is
		 * required to plug the VF successfully.
		 */
		pdn->pe_number = IODA_INVALID_PE;
#endif
		if (rmv_data)
			list_add(&edev->rmv_list, &rmv_data->edev_list);
	} else {
		pci_lock_rescan_remove();
		pci_stop_and_remove_bus_device(dev);
		pci_unlock_rescan_remove();
	}

	return NULL;
}