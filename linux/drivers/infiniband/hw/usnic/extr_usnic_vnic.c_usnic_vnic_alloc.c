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
struct usnic_vnic {int /*<<< orphan*/  res_lock; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct usnic_vnic* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct usnic_vnic*) ; 
 struct usnic_vnic* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_is_enabled (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usnic_dbg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usnic_err (char*,int /*<<< orphan*/ ,...) ; 
 int usnic_vnic_discover_resources (struct pci_dev*,struct usnic_vnic*) ; 
 int /*<<< orphan*/  usnic_vnic_pci_name (struct usnic_vnic*) ; 

struct usnic_vnic *usnic_vnic_alloc(struct pci_dev *pdev)
{
	struct usnic_vnic *vnic;
	int err = 0;

	if (!pci_is_enabled(pdev)) {
		usnic_err("PCI dev %s is disabled\n", pci_name(pdev));
		return ERR_PTR(-EINVAL);
	}

	vnic = kzalloc(sizeof(*vnic), GFP_KERNEL);
	if (!vnic)
		return ERR_PTR(-ENOMEM);

	spin_lock_init(&vnic->res_lock);

	err = usnic_vnic_discover_resources(pdev, vnic);
	if (err) {
		usnic_err("Failed to discover %s resources with err %d\n",
				pci_name(pdev), err);
		goto out_free_vnic;
	}

	usnic_dbg("Allocated vnic for %s\n", usnic_vnic_pci_name(vnic));

	return vnic;

out_free_vnic:
	kfree(vnic);

	return ERR_PTR(err);
}