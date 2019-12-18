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
struct rvu_hwinfo {int dummy; } ;
struct rvu {struct rvu* hw; int /*<<< orphan*/  afpf_wq_info; int /*<<< orphan*/  total_pfs; void* pfreg_base; void* afreg_base; struct device* dev; struct pci_dev* pdev; } ;
struct pci_device_id {int dummy; } ;
struct device {int dummy; } ;
struct pci_dev {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PCI_AF_REG_BAR_NUM ; 
 int /*<<< orphan*/  PCI_PF_REG_BAR_NUM ; 
 int /*<<< orphan*/  TYPE_AFPF ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  devm_kfree (struct device*,struct rvu*) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_consistent_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct rvu*) ; 
 void* pcim_iomap (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvu_afpf_mbox_handler ; 
 int /*<<< orphan*/  rvu_afpf_mbox_up_handler ; 
 int /*<<< orphan*/  rvu_cgx_exit (struct rvu*) ; 
 int /*<<< orphan*/  rvu_check_block_implemented (struct rvu*) ; 
 int rvu_enable_sriov (struct rvu*) ; 
 int rvu_flr_init (struct rvu*) ; 
 int /*<<< orphan*/  rvu_flr_wq_destroy (struct rvu*) ; 
 int /*<<< orphan*/  rvu_free_hw_resources (struct rvu*) ; 
 int /*<<< orphan*/  rvu_mbox_destroy (int /*<<< orphan*/ *) ; 
 int rvu_mbox_init (struct rvu*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rvu_register_interrupts (struct rvu*) ; 
 int /*<<< orphan*/  rvu_reset_all_blocks (struct rvu*) ; 
 int rvu_setup_hw_resources (struct rvu*) ; 
 int /*<<< orphan*/  rvu_unregister_interrupts (struct rvu*) ; 
 int /*<<< orphan*/  rvu_update_module_params (struct rvu*) ; 

__attribute__((used)) static int rvu_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	struct device *dev = &pdev->dev;
	struct rvu *rvu;
	int    err;

	rvu = devm_kzalloc(dev, sizeof(*rvu), GFP_KERNEL);
	if (!rvu)
		return -ENOMEM;

	rvu->hw = devm_kzalloc(dev, sizeof(struct rvu_hwinfo), GFP_KERNEL);
	if (!rvu->hw) {
		devm_kfree(dev, rvu);
		return -ENOMEM;
	}

	pci_set_drvdata(pdev, rvu);
	rvu->pdev = pdev;
	rvu->dev = &pdev->dev;

	err = pci_enable_device(pdev);
	if (err) {
		dev_err(dev, "Failed to enable PCI device\n");
		goto err_freemem;
	}

	err = pci_request_regions(pdev, DRV_NAME);
	if (err) {
		dev_err(dev, "PCI request regions failed 0x%x\n", err);
		goto err_disable_device;
	}

	err = pci_set_dma_mask(pdev, DMA_BIT_MASK(48));
	if (err) {
		dev_err(dev, "Unable to set DMA mask\n");
		goto err_release_regions;
	}

	err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(48));
	if (err) {
		dev_err(dev, "Unable to set consistent DMA mask\n");
		goto err_release_regions;
	}

	/* Map Admin function CSRs */
	rvu->afreg_base = pcim_iomap(pdev, PCI_AF_REG_BAR_NUM, 0);
	rvu->pfreg_base = pcim_iomap(pdev, PCI_PF_REG_BAR_NUM, 0);
	if (!rvu->afreg_base || !rvu->pfreg_base) {
		dev_err(dev, "Unable to map admin function CSRs, aborting\n");
		err = -ENOMEM;
		goto err_release_regions;
	}

	/* Store module params in rvu structure */
	rvu_update_module_params(rvu);

	/* Check which blocks the HW supports */
	rvu_check_block_implemented(rvu);

	rvu_reset_all_blocks(rvu);

	err = rvu_setup_hw_resources(rvu);
	if (err)
		goto err_release_regions;

	/* Init mailbox btw AF and PFs */
	err = rvu_mbox_init(rvu, &rvu->afpf_wq_info, TYPE_AFPF,
			    rvu->hw->total_pfs, rvu_afpf_mbox_handler,
			    rvu_afpf_mbox_up_handler);
	if (err)
		goto err_hwsetup;

	err = rvu_flr_init(rvu);
	if (err)
		goto err_mbox;

	err = rvu_register_interrupts(rvu);
	if (err)
		goto err_flr;

	/* Enable AF's VFs (if any) */
	err = rvu_enable_sriov(rvu);
	if (err)
		goto err_irq;

	return 0;
err_irq:
	rvu_unregister_interrupts(rvu);
err_flr:
	rvu_flr_wq_destroy(rvu);
err_mbox:
	rvu_mbox_destroy(&rvu->afpf_wq_info);
err_hwsetup:
	rvu_cgx_exit(rvu);
	rvu_reset_all_blocks(rvu);
	rvu_free_hw_resources(rvu);
err_release_regions:
	pci_release_regions(pdev);
err_disable_device:
	pci_disable_device(pdev);
err_freemem:
	pci_set_drvdata(pdev, NULL);
	devm_kfree(&pdev->dev, rvu->hw);
	devm_kfree(dev, rvu);
	return err;
}