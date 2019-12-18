#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usnic_vnic {TYPE_1__* bar; int /*<<< orphan*/  vdev; int /*<<< orphan*/ * chunks; } ;
struct pci_dev {int dummy; } ;
typedef  enum usnic_vnic_res_type { ____Placeholder_usnic_vnic_res_type } usnic_vnic_res_type ;
struct TYPE_3__ {int /*<<< orphan*/  vaddr; int /*<<< orphan*/  bus_addr; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int ENODEV ; 
 int IORESOURCE_MEM ; 
 int USNIC_VNIC_RES_TYPE_EOL ; 
 int USNIC_VNIC_RES_TYPE_MAX ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iomap (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int pci_name (struct pci_dev*) ; 
 int pci_resource_flags (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  usnic_err (char*,int) ; 
 int usnic_vnic_alloc_res_chunk (struct usnic_vnic*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usnic_vnic_free_res_chunk (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_dev_register (int /*<<< orphan*/ *,struct pci_dev*,struct pci_dev*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  vnic_dev_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usnic_vnic_discover_resources(struct pci_dev *pdev,
						struct usnic_vnic *vnic)
{
	enum usnic_vnic_res_type res_type;
	int i;
	int err = 0;

	for (i = 0; i < ARRAY_SIZE(vnic->bar); i++) {
		if (!(pci_resource_flags(pdev, i) & IORESOURCE_MEM))
			continue;
		vnic->bar[i].len = pci_resource_len(pdev, i);
		vnic->bar[i].vaddr = pci_iomap(pdev, i, vnic->bar[i].len);
		if (!vnic->bar[i].vaddr) {
			usnic_err("Cannot memory-map BAR %d, aborting\n",
					i);
			err = -ENODEV;
			goto out_clean_bar;
		}
		vnic->bar[i].bus_addr = pci_resource_start(pdev, i);
	}

	vnic->vdev = vnic_dev_register(NULL, pdev, pdev, vnic->bar,
			ARRAY_SIZE(vnic->bar));
	if (!vnic->vdev) {
		usnic_err("Failed to register device %s\n",
				pci_name(pdev));
		err = -EINVAL;
		goto out_clean_bar;
	}

	for (res_type = USNIC_VNIC_RES_TYPE_EOL + 1;
			res_type < USNIC_VNIC_RES_TYPE_MAX; res_type++) {
		err = usnic_vnic_alloc_res_chunk(vnic, res_type,
						&vnic->chunks[res_type]);
		if (err)
			goto out_clean_chunks;
	}

	return 0;

out_clean_chunks:
	for (res_type--; res_type > USNIC_VNIC_RES_TYPE_EOL; res_type--)
		usnic_vnic_free_res_chunk(&vnic->chunks[res_type]);
	vnic_dev_unregister(vnic->vdev);
out_clean_bar:
	for (i = 0; i < ARRAY_SIZE(vnic->bar); i++) {
		if (!(pci_resource_flags(pdev, i) & IORESOURCE_MEM))
			continue;
		if (!vnic->bar[i].vaddr)
			break;

		iounmap(vnic->bar[i].vaddr);
	}

	return err;
}