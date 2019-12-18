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
struct enetc_hw {scalar_t__ reg; scalar_t__ global; scalar_t__ port; } ;
struct enetc_si {int pad; struct enetc_hw hw; struct pci_dev* pdev; } ;

/* Variables and functions */
 size_t ALIGN (size_t,int) ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  ENETC_BAR_REGS ; 
 int ENETC_GLOBAL_BASE ; 
 int ENETC_PORT_BASE ; 
 int ENETC_SI_ALIGN ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct enetc_si* PTR_ALIGN (struct enetc_si*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enetc_detect_errata (struct enetc_si*) ; 
 int /*<<< orphan*/  enetc_kfree_si (struct enetc_si*) ; 
 scalar_t__ ioremap (int /*<<< orphan*/ ,int) ; 
 struct enetc_si* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device_mem (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_mem_regions (struct pci_dev*) ; 
 int pci_request_mem_regions (struct pci_dev*,char const*) ; 
 int pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct enetc_si*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_flr (struct pci_dev*) ; 

int enetc_pci_probe(struct pci_dev *pdev, const char *name, int sizeof_priv)
{
	struct enetc_si *si, *p;
	struct enetc_hw *hw;
	size_t alloc_size;
	int err, len;

	pcie_flr(pdev);
	err = pci_enable_device_mem(pdev);
	if (err) {
		dev_err(&pdev->dev, "device enable failed\n");
		return err;
	}

	/* set up for high or low dma */
	err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	if (err) {
		err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		if (err) {
			dev_err(&pdev->dev,
				"DMA configuration failed: 0x%x\n", err);
			goto err_dma;
		}
	}

	err = pci_request_mem_regions(pdev, name);
	if (err) {
		dev_err(&pdev->dev, "pci_request_regions failed err=%d\n", err);
		goto err_pci_mem_reg;
	}

	pci_set_master(pdev);

	alloc_size = sizeof(struct enetc_si);
	if (sizeof_priv) {
		/* align priv to 32B */
		alloc_size = ALIGN(alloc_size, ENETC_SI_ALIGN);
		alloc_size += sizeof_priv;
	}
	/* force 32B alignment for enetc_si */
	alloc_size += ENETC_SI_ALIGN - 1;

	p = kzalloc(alloc_size, GFP_KERNEL);
	if (!p) {
		err = -ENOMEM;
		goto err_alloc_si;
	}

	si = PTR_ALIGN(p, ENETC_SI_ALIGN);
	si->pad = (char *)si - (char *)p;

	pci_set_drvdata(pdev, si);
	si->pdev = pdev;
	hw = &si->hw;

	len = pci_resource_len(pdev, ENETC_BAR_REGS);
	hw->reg = ioremap(pci_resource_start(pdev, ENETC_BAR_REGS), len);
	if (!hw->reg) {
		err = -ENXIO;
		dev_err(&pdev->dev, "ioremap() failed\n");
		goto err_ioremap;
	}
	if (len > ENETC_PORT_BASE)
		hw->port = hw->reg + ENETC_PORT_BASE;
	if (len > ENETC_GLOBAL_BASE)
		hw->global = hw->reg + ENETC_GLOBAL_BASE;

	enetc_detect_errata(si);

	return 0;

err_ioremap:
	enetc_kfree_si(si);
err_alloc_si:
	pci_release_mem_regions(pdev);
err_pci_mem_reg:
err_dma:
	pci_disable_device(pdev);

	return err;
}