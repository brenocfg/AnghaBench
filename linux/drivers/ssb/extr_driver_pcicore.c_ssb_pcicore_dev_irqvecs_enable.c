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
typedef  int u32 ;
struct ssb_pcicore {int setup_done; struct ssb_device* dev; } ;
struct TYPE_2__ {scalar_t__ coreid; int revision; } ;
struct ssb_device {int core_index; TYPE_1__ id; struct ssb_bus* bus; } ;
struct ssb_bus {scalar_t__ bustype; int /*<<< orphan*/  host_pci; } ;

/* Variables and functions */
 scalar_t__ SSB_BUSTYPE_PCI ; 
 scalar_t__ SSB_DEV_PCI ; 
 scalar_t__ SSB_DEV_PCIE ; 
 int /*<<< orphan*/  SSB_INTVEC ; 
 int /*<<< orphan*/  SSB_PCI_IRQMASK ; 
 int /*<<< orphan*/  SSB_TPSFLAG ; 
 int SSB_TPSFLAG_BPFLAG ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  might_sleep_if (int) ; 
 int pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ssb_pcicore_pci_setup_workarounds (struct ssb_pcicore*) ; 
 int /*<<< orphan*/  ssb_pcicore_pcie_setup_workarounds (struct ssb_pcicore*) ; 
 int ssb_read32 (struct ssb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssb_write32 (struct ssb_device*,int /*<<< orphan*/ ,int) ; 

int ssb_pcicore_dev_irqvecs_enable(struct ssb_pcicore *pc,
				   struct ssb_device *dev)
{
	struct ssb_device *pdev = pc->dev;
	struct ssb_bus *bus;
	int err = 0;
	u32 tmp;

	if (dev->bus->bustype != SSB_BUSTYPE_PCI) {
		/* This SSB device is not on a PCI host-bus. So the IRQs are
		 * not routed through the PCI core.
		 * So we must not enable routing through the PCI core. */
		goto out;
	}

	if (!pdev)
		goto out;
	bus = pdev->bus;

	might_sleep_if(pdev->id.coreid != SSB_DEV_PCI);

	/* Enable interrupts for this device. */
	if ((pdev->id.revision >= 6) || (pdev->id.coreid == SSB_DEV_PCIE)) {
		u32 coremask;

		/* Calculate the "coremask" for the device. */
		coremask = (1 << dev->core_index);

		WARN_ON(bus->bustype != SSB_BUSTYPE_PCI);
		err = pci_read_config_dword(bus->host_pci, SSB_PCI_IRQMASK, &tmp);
		if (err)
			goto out;
		tmp |= coremask << 8;
		err = pci_write_config_dword(bus->host_pci, SSB_PCI_IRQMASK, tmp);
		if (err)
			goto out;
	} else {
		u32 intvec;

		intvec = ssb_read32(pdev, SSB_INTVEC);
		tmp = ssb_read32(dev, SSB_TPSFLAG);
		tmp &= SSB_TPSFLAG_BPFLAG;
		intvec |= (1 << tmp);
		ssb_write32(pdev, SSB_INTVEC, intvec);
	}

	/* Setup PCIcore operation. */
	if (pc->setup_done)
		goto out;
	if (pdev->id.coreid == SSB_DEV_PCI) {
		ssb_pcicore_pci_setup_workarounds(pc);
	} else {
		WARN_ON(pdev->id.coreid != SSB_DEV_PCIE);
		ssb_pcicore_pcie_setup_workarounds(pc);
	}
	pc->setup_done = 1;
out:
	return err;
}