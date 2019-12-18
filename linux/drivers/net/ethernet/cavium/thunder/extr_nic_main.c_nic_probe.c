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
typedef  union nic_mbx {int dummy; } nic_mbx ;
typedef  int u8 ;
struct pci_device_id {int dummy; } ;
struct device {int dummy; } ;
struct pci_dev {struct device dev; } ;
struct nicpf {int /*<<< orphan*/  vf_lmac_map; TYPE_1__* hw; int /*<<< orphan*/  node; int /*<<< orphan*/  reg_base; struct pci_dev* pdev; } ;
struct hw_info {int dummy; } ;
struct TYPE_2__ {int bgx_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_LMAC_PER_BGX ; 
 int /*<<< orphan*/  PCI_CFG_REG_BAR_NUM ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  devm_kmalloc_array (struct device*,int,int,int /*<<< orphan*/ ) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nic_get_hw_info (struct nicpf*) ; 
 int /*<<< orphan*/  nic_get_node_id (struct pci_dev*) ; 
 int /*<<< orphan*/  nic_init_hw (struct nicpf*) ; 
 int nic_register_interrupts (struct nicpf*) ; 
 int /*<<< orphan*/  nic_set_lmac_vf_mapping (struct nicpf*) ; 
 int nic_sriov_init (struct pci_dev*,struct nicpf*) ; 
 int /*<<< orphan*/  nic_unregister_interrupts (struct nicpf*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_consistent_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct nicpf*) ; 
 int /*<<< orphan*/  pcim_iomap (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nic_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	struct device *dev = &pdev->dev;
	struct nicpf *nic;
	u8     max_lmac;
	int    err;

	BUILD_BUG_ON(sizeof(union nic_mbx) > 16);

	nic = devm_kzalloc(dev, sizeof(*nic), GFP_KERNEL);
	if (!nic)
		return -ENOMEM;

	nic->hw = devm_kzalloc(dev, sizeof(struct hw_info), GFP_KERNEL);
	if (!nic->hw)
		return -ENOMEM;

	pci_set_drvdata(pdev, nic);

	nic->pdev = pdev;

	err = pci_enable_device(pdev);
	if (err) {
		dev_err(dev, "Failed to enable PCI device\n");
		pci_set_drvdata(pdev, NULL);
		return err;
	}

	err = pci_request_regions(pdev, DRV_NAME);
	if (err) {
		dev_err(dev, "PCI request regions failed 0x%x\n", err);
		goto err_disable_device;
	}

	err = pci_set_dma_mask(pdev, DMA_BIT_MASK(48));
	if (err) {
		dev_err(dev, "Unable to get usable DMA configuration\n");
		goto err_release_regions;
	}

	err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(48));
	if (err) {
		dev_err(dev, "Unable to get 48-bit DMA for consistent allocations\n");
		goto err_release_regions;
	}

	/* MAP PF's configuration registers */
	nic->reg_base = pcim_iomap(pdev, PCI_CFG_REG_BAR_NUM, 0);
	if (!nic->reg_base) {
		dev_err(dev, "Cannot map config register space, aborting\n");
		err = -ENOMEM;
		goto err_release_regions;
	}

	nic->node = nic_get_node_id(pdev);

	/* Get HW capability info */
	nic_get_hw_info(nic);

	/* Allocate memory for LMAC tracking elements */
	err = -ENOMEM;
	max_lmac = nic->hw->bgx_cnt * MAX_LMAC_PER_BGX;

	nic->vf_lmac_map = devm_kmalloc_array(dev, max_lmac, sizeof(u8),
					      GFP_KERNEL);
	if (!nic->vf_lmac_map)
		goto err_release_regions;

	/* Initialize hardware */
	nic_init_hw(nic);

	nic_set_lmac_vf_mapping(nic);

	/* Register interrupts */
	err = nic_register_interrupts(nic);
	if (err)
		goto err_release_regions;

	/* Configure SRIOV */
	err = nic_sriov_init(pdev, nic);
	if (err)
		goto err_unregister_interrupts;

	return 0;

err_unregister_interrupts:
	nic_unregister_interrupts(nic);
err_release_regions:
	pci_release_regions(pdev);
err_disable_device:
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, NULL);
	return err;
}