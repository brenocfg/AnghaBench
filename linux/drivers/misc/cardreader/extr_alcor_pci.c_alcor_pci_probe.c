#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {scalar_t__ driver_data; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; TYPE_1__* bus; } ;
struct alcor_pci_priv {int id; int /*<<< orphan*/ * dev; int /*<<< orphan*/  iobase; int /*<<< orphan*/  irq; struct alcor_dev_cfg* cfg; int /*<<< orphan*/  parent_pdev; struct pci_dev* pdev; } ;
struct alcor_dev_cfg {int dummy; } ;
struct TYPE_6__ {int pdata_size; struct alcor_pci_priv* platform_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  self; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  AU6601_MS_INT_ENABLE ; 
 int /*<<< orphan*/  AU6601_REG_INT_ENABLE ; 
 int /*<<< orphan*/  AU6601_SDMA_MASK ; 
 int /*<<< orphan*/  DRV_NAME_ALCOR_PCI ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IORESOURCE_MEM ; 
 int /*<<< orphan*/  alcor_pci_aspm_ctrl (struct alcor_pci_priv*,int /*<<< orphan*/ ) ; 
 TYPE_2__* alcor_pci_cells ; 
 int /*<<< orphan*/  alcor_pci_idr ; 
 int /*<<< orphan*/  alcor_pci_init_check_aspm (struct alcor_pci_priv*) ; 
 int /*<<< orphan*/  alcor_write32 (struct alcor_pci_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct alcor_pci_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mfd_add_devices (int /*<<< orphan*/ *,int,TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_resource_flags (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct alcor_pci_priv*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int pcim_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pcim_iomap (struct pci_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alcor_pci_probe(struct pci_dev *pdev,
			   const struct pci_device_id *ent)
{
	struct alcor_dev_cfg *cfg;
	struct alcor_pci_priv *priv;
	int ret, i, bar = 0;

	cfg = (void *)ent->driver_data;

	ret = pcim_enable_device(pdev);
	if (ret)
		return ret;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	ret = ida_simple_get(&alcor_pci_idr, 0, 0, GFP_KERNEL);
	if (ret < 0)
		return ret;
	priv->id = ret;

	priv->pdev = pdev;
	priv->parent_pdev = pdev->bus->self;
	priv->dev = &pdev->dev;
	priv->cfg = cfg;
	priv->irq = pdev->irq;

	ret = pci_request_regions(pdev, DRV_NAME_ALCOR_PCI);
	if (ret) {
		dev_err(&pdev->dev, "Cannot request region\n");
		return -ENOMEM;
	}

	if (!(pci_resource_flags(pdev, bar) & IORESOURCE_MEM)) {
		dev_err(&pdev->dev, "BAR %d is not iomem. Aborting.\n", bar);
		ret = -ENODEV;
		goto error_release_regions;
	}

	priv->iobase = pcim_iomap(pdev, bar, 0);
	if (!priv->iobase) {
		ret = -ENOMEM;
		goto error_release_regions;
	}

	/* make sure irqs are disabled */
	alcor_write32(priv, 0, AU6601_REG_INT_ENABLE);
	alcor_write32(priv, 0, AU6601_MS_INT_ENABLE);

	ret = dma_set_mask_and_coherent(priv->dev, AU6601_SDMA_MASK);
	if (ret) {
		dev_err(priv->dev, "Failed to set DMA mask\n");
		goto error_release_regions;
	}

	pci_set_master(pdev);
	pci_set_drvdata(pdev, priv);
	alcor_pci_init_check_aspm(priv);

	for (i = 0; i < ARRAY_SIZE(alcor_pci_cells); i++) {
		alcor_pci_cells[i].platform_data = priv;
		alcor_pci_cells[i].pdata_size = sizeof(*priv);
	}
	ret = mfd_add_devices(&pdev->dev, priv->id, alcor_pci_cells,
			ARRAY_SIZE(alcor_pci_cells), NULL, 0, NULL);
	if (ret < 0)
		goto error_release_regions;

	alcor_pci_aspm_ctrl(priv, 0);

	return 0;

error_release_regions:
	pci_release_regions(pdev);
	return ret;
}