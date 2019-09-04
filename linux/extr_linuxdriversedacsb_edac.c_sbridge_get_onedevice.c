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
typedef  int /*<<< orphan*/  u8 ;
struct sbridge_dev {size_t i_devs; struct pci_dev** pdev; } ;
struct pci_id_table {int n_imcs_per_sock; struct pci_id_descr* descr; } ;
struct pci_id_descr {scalar_t__ dom; int /*<<< orphan*/  dev_id; scalar_t__ optional; } ;
struct pci_dev {TYPE_1__* bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ IMC1 ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_INTEL ; 
 scalar_t__ SOCK ; 
 struct sbridge_dev* alloc_sbridge_dev (int,int /*<<< orphan*/ ,scalar_t__,struct pci_id_table const*) ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sbridge_dev* get_sbridge_dev (int,int /*<<< orphan*/ ,scalar_t__,int const,struct sbridge_dev*) ; 
 int /*<<< orphan*/  pci_dev_get (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 int pci_domain_nr (TYPE_1__*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pci_dev*) ; 
 int /*<<< orphan*/  sbridge_printk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int sbridge_get_onedevice(struct pci_dev **prev,
				 u8 *num_mc,
				 const struct pci_id_table *table,
				 const unsigned devno,
				 const int multi_bus)
{
	struct sbridge_dev *sbridge_dev = NULL;
	const struct pci_id_descr *dev_descr = &table->descr[devno];
	struct pci_dev *pdev = NULL;
	int seg = 0;
	u8 bus = 0;
	int i = 0;

	sbridge_printk(KERN_DEBUG,
		"Seeking for: PCI ID %04x:%04x\n",
		PCI_VENDOR_ID_INTEL, dev_descr->dev_id);

	pdev = pci_get_device(PCI_VENDOR_ID_INTEL,
			      dev_descr->dev_id, *prev);

	if (!pdev) {
		if (*prev) {
			*prev = pdev;
			return 0;
		}

		if (dev_descr->optional)
			return 0;

		/* if the HA wasn't found */
		if (devno == 0)
			return -ENODEV;

		sbridge_printk(KERN_INFO,
			"Device not found: %04x:%04x\n",
			PCI_VENDOR_ID_INTEL, dev_descr->dev_id);

		/* End of list, leave */
		return -ENODEV;
	}
	seg = pci_domain_nr(pdev->bus);
	bus = pdev->bus->number;

next_imc:
	sbridge_dev = get_sbridge_dev(seg, bus, dev_descr->dom,
				      multi_bus, sbridge_dev);
	if (!sbridge_dev) {
		/* If the HA1 wasn't found, don't create EDAC second memory controller */
		if (dev_descr->dom == IMC1 && devno != 1) {
			edac_dbg(0, "Skip IMC1: %04x:%04x (since HA1 was absent)\n",
				 PCI_VENDOR_ID_INTEL, dev_descr->dev_id);
			pci_dev_put(pdev);
			return 0;
		}

		if (dev_descr->dom == SOCK)
			goto out_imc;

		sbridge_dev = alloc_sbridge_dev(seg, bus, dev_descr->dom, table);
		if (!sbridge_dev) {
			pci_dev_put(pdev);
			return -ENOMEM;
		}
		(*num_mc)++;
	}

	if (sbridge_dev->pdev[sbridge_dev->i_devs]) {
		sbridge_printk(KERN_ERR,
			"Duplicated device for %04x:%04x\n",
			PCI_VENDOR_ID_INTEL, dev_descr->dev_id);
		pci_dev_put(pdev);
		return -ENODEV;
	}

	sbridge_dev->pdev[sbridge_dev->i_devs++] = pdev;

	/* pdev belongs to more than one IMC, do extra gets */
	if (++i > 1)
		pci_dev_get(pdev);

	if (dev_descr->dom == SOCK && i < table->n_imcs_per_sock)
		goto next_imc;

out_imc:
	/* Be sure that the device is enabled */
	if (unlikely(pci_enable_device(pdev) < 0)) {
		sbridge_printk(KERN_ERR,
			"Couldn't enable %04x:%04x\n",
			PCI_VENDOR_ID_INTEL, dev_descr->dev_id);
		return -ENODEV;
	}

	edac_dbg(0, "Detected %04x:%04x\n",
		 PCI_VENDOR_ID_INTEL, dev_descr->dev_id);

	/*
	 * As stated on drivers/pci/search.c, the reference count for
	 * @from is always decremented if it is not %NULL. So, as we need
	 * to get all devices up to null, we need to do a get for the device
	 */
	pci_dev_get(pdev);

	*prev = pdev;

	return 0;
}