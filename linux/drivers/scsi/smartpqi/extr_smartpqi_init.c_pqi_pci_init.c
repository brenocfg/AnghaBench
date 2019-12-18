#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_9__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct pqi_ctrl_registers {int dummy; } ;
struct pqi_ctrl_info {TYPE_1__* pci_dev; TYPE_9__* registers; int /*<<< orphan*/ * pqi_registers; TYPE_9__* iomem_base; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_11__ {int /*<<< orphan*/  pqi_registers; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRIVER_NAME_SHORT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PCI_EXP_COMP_TIMEOUT_65_TO_210_MS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_9__* ioremap_nocache (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_disable_device (TYPE_1__*) ; 
 int pci_enable_device (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_release_regions (TYPE_1__*) ; 
 int pci_request_regions (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (TYPE_1__*,struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pci_set_master (TYPE_1__*) ; 
 int pqi_set_pcie_completion_timeout (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pqi_pci_init(struct pqi_ctrl_info *ctrl_info)
{
	int rc;
	u64 mask;

	rc = pci_enable_device(ctrl_info->pci_dev);
	if (rc) {
		dev_err(&ctrl_info->pci_dev->dev,
			"failed to enable PCI device\n");
		return rc;
	}

	if (sizeof(dma_addr_t) > 4)
		mask = DMA_BIT_MASK(64);
	else
		mask = DMA_BIT_MASK(32);

	rc = dma_set_mask_and_coherent(&ctrl_info->pci_dev->dev, mask);
	if (rc) {
		dev_err(&ctrl_info->pci_dev->dev, "failed to set DMA mask\n");
		goto disable_device;
	}

	rc = pci_request_regions(ctrl_info->pci_dev, DRIVER_NAME_SHORT);
	if (rc) {
		dev_err(&ctrl_info->pci_dev->dev,
			"failed to obtain PCI resources\n");
		goto disable_device;
	}

	ctrl_info->iomem_base = ioremap_nocache(pci_resource_start(
		ctrl_info->pci_dev, 0),
		sizeof(struct pqi_ctrl_registers));
	if (!ctrl_info->iomem_base) {
		dev_err(&ctrl_info->pci_dev->dev,
			"failed to map memory for controller registers\n");
		rc = -ENOMEM;
		goto release_regions;
	}

#define PCI_EXP_COMP_TIMEOUT_65_TO_210_MS		0x6

	/* Increase the PCIe completion timeout. */
	rc = pqi_set_pcie_completion_timeout(ctrl_info->pci_dev,
		PCI_EXP_COMP_TIMEOUT_65_TO_210_MS);
	if (rc) {
		dev_err(&ctrl_info->pci_dev->dev,
			"failed to set PCIe completion timeout\n");
		goto release_regions;
	}

	/* Enable bus mastering. */
	pci_set_master(ctrl_info->pci_dev);

	ctrl_info->registers = ctrl_info->iomem_base;
	ctrl_info->pqi_registers = &ctrl_info->registers->pqi_registers;

	pci_set_drvdata(ctrl_info->pci_dev, ctrl_info);

	return 0;

release_regions:
	pci_release_regions(ctrl_info->pci_dev);
disable_device:
	pci_disable_device(ctrl_info->pci_dev);

	return rc;
}