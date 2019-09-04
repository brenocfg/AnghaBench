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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hclge_hw {int /*<<< orphan*/  io_base; } ;
struct hclge_dev {int /*<<< orphan*/  num_req_vfs; struct hclge_hw hw; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HCLGE_DRIVER_NAME ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_clear_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_sriov_get_totalvfs (struct pci_dev*) ; 
 int /*<<< orphan*/  pcim_iomap (struct pci_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_pci_init(struct hclge_dev *hdev)
{
	struct pci_dev *pdev = hdev->pdev;
	struct hclge_hw *hw;
	int ret;

	ret = pci_enable_device(pdev);
	if (ret) {
		dev_err(&pdev->dev, "failed to enable PCI device\n");
		return ret;
	}

	ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	if (ret) {
		ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		if (ret) {
			dev_err(&pdev->dev,
				"can't set consistent PCI DMA");
			goto err_disable_device;
		}
		dev_warn(&pdev->dev, "set DMA mask to 32 bits\n");
	}

	ret = pci_request_regions(pdev, HCLGE_DRIVER_NAME);
	if (ret) {
		dev_err(&pdev->dev, "PCI request regions failed %d\n", ret);
		goto err_disable_device;
	}

	pci_set_master(pdev);
	hw = &hdev->hw;
	hw->io_base = pcim_iomap(pdev, 2, 0);
	if (!hw->io_base) {
		dev_err(&pdev->dev, "Can't map configuration register space\n");
		ret = -ENOMEM;
		goto err_clr_master;
	}

	hdev->num_req_vfs = pci_sriov_get_totalvfs(pdev);

	return 0;
err_clr_master:
	pci_clear_master(pdev);
	pci_release_regions(pdev);
err_disable_device:
	pci_disable_device(pdev);

	return ret;
}