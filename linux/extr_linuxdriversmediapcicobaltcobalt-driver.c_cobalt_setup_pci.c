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
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct cobalt {int device_id; int /*<<< orphan*/  pci_dev; TYPE_1__ v4l2_dev; int /*<<< orphan*/ * bar1; void* bar0; int /*<<< orphan*/  card_rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  COBALT_SYS_CTRL_BASE ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EIO ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  PCI_CLASS_REVISION ; 
 int /*<<< orphan*/  PCI_DEVICE_ID ; 
#define  PCI_DEVICE_ID_COBALT 128 
 int /*<<< orphan*/  PCI_IRQ_MSI ; 
 int /*<<< orphan*/  cobalt_dbg (int,char*) ; 
 int /*<<< orphan*/  cobalt_err (char*,...) ; 
 int /*<<< orphan*/  cobalt_info (char*) ; 
 int /*<<< orphan*/  cobalt_irq_handler ; 
 int /*<<< orphan*/  cobalt_pci_iounmap (struct cobalt*,struct pci_dev*) ; 
 int /*<<< orphan*/  cobalt_pcie_status_show (struct cobalt*) ; 
 int cobalt_read_bar1 (struct cobalt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cobalt_set_interrupt (struct cobalt*,int) ; 
 int /*<<< orphan*/  cobalt_warn (char*,int) ; 
 int /*<<< orphan*/  cobalt_write_bar1 (struct cobalt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msi_config_show (struct cobalt*,struct pci_dev*) ; 
 int /*<<< orphan*/  omni_sg_dma_init (struct cobalt*) ; 
 int pci_alloc_irq_vectors (struct pci_dev*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 void* pci_iomap (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,char*) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int pcie_bus_link_get_lanes (struct cobalt*) ; 
 int pcie_link_get_lanes (struct cobalt*) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int cobalt_setup_pci(struct cobalt *cobalt, struct pci_dev *pci_dev,
			    const struct pci_device_id *pci_id)
{
	u32 ctrl;
	int ret;

	cobalt_dbg(1, "enabling pci device\n");

	ret = pci_enable_device(pci_dev);
	if (ret) {
		cobalt_err("can't enable device\n");
		return ret;
	}
	pci_set_master(pci_dev);
	pci_read_config_byte(pci_dev, PCI_CLASS_REVISION, &cobalt->card_rev);
	pci_read_config_word(pci_dev, PCI_DEVICE_ID, &cobalt->device_id);

	switch (cobalt->device_id) {
	case PCI_DEVICE_ID_COBALT:
		cobalt_info("PCI Express interface from Omnitek\n");
		break;
	default:
		cobalt_info("PCI Express interface provider is unknown!\n");
		break;
	}

	if (pcie_link_get_lanes(cobalt) != 8) {
		cobalt_warn("PCI Express link width is %d lanes.\n",
				pcie_link_get_lanes(cobalt));
		if (pcie_bus_link_get_lanes(cobalt) < 8)
			cobalt_warn("The current slot only supports %d lanes, for best performance 8 are needed\n",
					pcie_bus_link_get_lanes(cobalt));
		if (pcie_link_get_lanes(cobalt) != pcie_bus_link_get_lanes(cobalt)) {
			cobalt_err("The card is most likely not seated correctly in the PCIe slot\n");
			ret = -EIO;
			goto err_disable;
		}
	}

	if (pci_set_dma_mask(pci_dev, DMA_BIT_MASK(64))) {
		ret = pci_set_dma_mask(pci_dev, DMA_BIT_MASK(32));
		if (ret) {
			cobalt_err("no suitable DMA available\n");
			goto err_disable;
		}
	}

	ret = pci_request_regions(pci_dev, "cobalt");
	if (ret) {
		cobalt_err("error requesting regions\n");
		goto err_disable;
	}

	cobalt_pcie_status_show(cobalt);

	cobalt->bar0 = pci_iomap(pci_dev, 0, 0);
	cobalt->bar1 = pci_iomap(pci_dev, 1, 0);
	if (cobalt->bar1 == NULL) {
		cobalt->bar1 = pci_iomap(pci_dev, 2, 0);
		cobalt_info("64-bit BAR\n");
	}
	if (!cobalt->bar0 || !cobalt->bar1) {
		ret = -EIO;
		goto err_release;
	}

	/* Reset the video inputs before enabling any interrupts */
	ctrl = cobalt_read_bar1(cobalt, COBALT_SYS_CTRL_BASE);
	cobalt_write_bar1(cobalt, COBALT_SYS_CTRL_BASE, ctrl & ~0xf00);

	/* Disable interrupts to prevent any spurious interrupts
	   from being generated. */
	cobalt_set_interrupt(cobalt, false);

	if (pci_alloc_irq_vectors(pci_dev, 1, 1, PCI_IRQ_MSI) < 1) {
		cobalt_err("Could not enable MSI\n");
		ret = -EIO;
		goto err_release;
	}
	msi_config_show(cobalt, pci_dev);

	/* Register IRQ */
	if (request_irq(pci_dev->irq, cobalt_irq_handler, IRQF_SHARED,
			cobalt->v4l2_dev.name, (void *)cobalt)) {
		cobalt_err("Failed to register irq %d\n", pci_dev->irq);
		ret = -EIO;
		goto err_msi;
	}

	omni_sg_dma_init(cobalt);
	return 0;

err_msi:
	pci_disable_msi(pci_dev);

err_release:
	cobalt_pci_iounmap(cobalt, pci_dev);
	pci_release_regions(pci_dev);

err_disable:
	pci_disable_device(cobalt->pci_dev);
	return ret;
}