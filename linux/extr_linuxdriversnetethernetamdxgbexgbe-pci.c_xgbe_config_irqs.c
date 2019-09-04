#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xgbe_prv_data {int isr_as_tasklet; int irq_count; int channel_irq_count; int /*<<< orphan*/ * channel_irq; int /*<<< orphan*/  dev; void* an_irq; void* i2c_irq; void* ecc_irq; void* dev_irq; TYPE_1__* pcidev; } ;
struct TYPE_3__ {scalar_t__ msi_enabled; } ;

/* Variables and functions */
 int PCI_IRQ_LEGACY ; 
 int PCI_IRQ_MSI ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ netif_msg_probe (struct xgbe_prv_data*) ; 
 int pci_alloc_irq_vectors (TYPE_1__*,int,int,int) ; 
 void* pci_irq_vector (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int xgbe_config_multi_msi (struct xgbe_prv_data*) ; 

__attribute__((used)) static int xgbe_config_irqs(struct xgbe_prv_data *pdata)
{
	int ret;

	ret = xgbe_config_multi_msi(pdata);
	if (!ret)
		goto out;

	ret = pci_alloc_irq_vectors(pdata->pcidev, 1, 1,
				    PCI_IRQ_LEGACY | PCI_IRQ_MSI);
	if (ret < 0) {
		dev_info(pdata->dev, "single IRQ enablement failed\n");
		return ret;
	}

	pdata->isr_as_tasklet = pdata->pcidev->msi_enabled ? 1 : 0;
	pdata->irq_count = 1;
	pdata->channel_irq_count = 1;

	pdata->dev_irq = pci_irq_vector(pdata->pcidev, 0);
	pdata->ecc_irq = pci_irq_vector(pdata->pcidev, 0);
	pdata->i2c_irq = pci_irq_vector(pdata->pcidev, 0);
	pdata->an_irq = pci_irq_vector(pdata->pcidev, 0);

	if (netif_msg_probe(pdata))
		dev_dbg(pdata->dev, "single %s interrupt enabled\n",
			pdata->pcidev->msi_enabled ?  "MSI" : "legacy");

out:
	if (netif_msg_probe(pdata)) {
		unsigned int i;

		dev_dbg(pdata->dev, " dev irq=%d\n", pdata->dev_irq);
		dev_dbg(pdata->dev, " ecc irq=%d\n", pdata->ecc_irq);
		dev_dbg(pdata->dev, " i2c irq=%d\n", pdata->i2c_irq);
		dev_dbg(pdata->dev, "  an irq=%d\n", pdata->an_irq);
		for (i = 0; i < pdata->channel_irq_count; i++)
			dev_dbg(pdata->dev, " dma%u irq=%d\n",
				i, pdata->channel_irq[i]);
	}

	return 0;
}