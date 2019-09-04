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
struct zip_device {size_t index; scalar_t__ reg_base; struct pci_dev* pdev; } ;
struct pci_device_id {int dummy; } ;
struct device {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PCI_CFG_ZIP_PF_BAR0 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_to_node (struct device*) ; 
 int /*<<< orphan*/  devm_kfree (struct device*,struct zip_device*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 scalar_t__ pci_ioremap_bar (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_consistent_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct zip_device*) ; 
 struct zip_device* zip_alloc_device (struct pci_dev*) ; 
 int /*<<< orphan*/ ** zip_dev ; 
 int zip_init_hw (struct zip_device*) ; 

__attribute__((used)) static int zip_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	struct device *dev = &pdev->dev;
	struct zip_device *zip = NULL;
	int    err;

	zip = zip_alloc_device(pdev);
	if (!zip)
		return -ENOMEM;

	dev_info(dev, "Found ZIP device %d %x:%x on Node %d\n", zip->index,
		 pdev->vendor, pdev->device, dev_to_node(dev));

	pci_set_drvdata(pdev, zip);
	zip->pdev = pdev;

	err = pci_enable_device(pdev);
	if (err) {
		dev_err(dev, "Failed to enable PCI device");
		goto err_free_device;
	}

	err = pci_request_regions(pdev, DRV_NAME);
	if (err) {
		dev_err(dev, "PCI request regions failed 0x%x", err);
		goto err_disable_device;
	}

	err = pci_set_dma_mask(pdev, DMA_BIT_MASK(48));
	if (err) {
		dev_err(dev, "Unable to get usable DMA configuration\n");
		goto err_release_regions;
	}

	err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(48));
	if (err) {
		dev_err(dev, "Unable to get 48-bit DMA for allocations\n");
		goto err_release_regions;
	}

	/* MAP configuration registers */
	zip->reg_base = pci_ioremap_bar(pdev, PCI_CFG_ZIP_PF_BAR0);
	if (!zip->reg_base) {
		dev_err(dev, "ZIP: Cannot map BAR0 CSR memory space, aborting");
		err = -ENOMEM;
		goto err_release_regions;
	}

	/* Initialize ZIP Hardware */
	err = zip_init_hw(zip);
	if (err)
		goto err_release_regions;

	return 0;

err_release_regions:
	if (zip->reg_base)
		iounmap(zip->reg_base);
	pci_release_regions(pdev);

err_disable_device:
	pci_disable_device(pdev);

err_free_device:
	pci_set_drvdata(pdev, NULL);

	/* Remove zip_dev from zip_device list, free the zip_device memory */
	zip_dev[zip->index] = NULL;
	devm_kfree(dev, zip);

	return err;
}