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
struct pcie_service_card {void* pci_mmap; void* pci_mmap1; struct pci_dev* dev; } ;
struct pci_dev {int dummy; } ;
struct mwifiex_adapter {struct pcie_service_card* card; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int EIO ; 
 int mwifiex_pcie_alloc_buffers (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 void* pci_iomap (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,void*) ; 
 int /*<<< orphan*/  pci_release_region (struct pci_dev*,int) ; 
 int pci_request_region (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int pci_set_consistent_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct pcie_service_card*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_notice (char*,void*,void*) ; 

__attribute__((used)) static int mwifiex_init_pcie(struct mwifiex_adapter *adapter)
{
	struct pcie_service_card *card = adapter->card;
	int ret;
	struct pci_dev *pdev = card->dev;

	pci_set_drvdata(pdev, card);

	ret = pci_enable_device(pdev);
	if (ret)
		goto err_enable_dev;

	pci_set_master(pdev);

	ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
	if (ret) {
		pr_err("set_dma_mask(32) failed: %d\n", ret);
		goto err_set_dma_mask;
	}

	ret = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
	if (ret) {
		pr_err("set_consistent_dma_mask(64) failed\n");
		goto err_set_dma_mask;
	}

	ret = pci_request_region(pdev, 0, DRV_NAME);
	if (ret) {
		pr_err("req_reg(0) error\n");
		goto err_req_region0;
	}
	card->pci_mmap = pci_iomap(pdev, 0, 0);
	if (!card->pci_mmap) {
		pr_err("iomap(0) error\n");
		ret = -EIO;
		goto err_iomap0;
	}
	ret = pci_request_region(pdev, 2, DRV_NAME);
	if (ret) {
		pr_err("req_reg(2) error\n");
		goto err_req_region2;
	}
	card->pci_mmap1 = pci_iomap(pdev, 2, 0);
	if (!card->pci_mmap1) {
		pr_err("iomap(2) error\n");
		ret = -EIO;
		goto err_iomap2;
	}

	pr_notice("PCI memory map Virt0: %pK PCI memory map Virt2: %pK\n",
		  card->pci_mmap, card->pci_mmap1);

	ret = mwifiex_pcie_alloc_buffers(adapter);
	if (ret)
		goto err_alloc_buffers;

	return 0;

err_alloc_buffers:
	pci_iounmap(pdev, card->pci_mmap1);
err_iomap2:
	pci_release_region(pdev, 2);
err_req_region2:
	pci_iounmap(pdev, card->pci_mmap);
err_iomap0:
	pci_release_region(pdev, 0);
err_req_region0:
err_set_dma_mask:
	pci_disable_device(pdev);
err_enable_dev:
	return ret;
}