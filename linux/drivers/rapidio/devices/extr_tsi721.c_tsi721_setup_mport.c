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
struct TYPE_2__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * parent; } ;
struct rio_mport {int phys_efptr; int phys_rmap; scalar_t__ host_deviceid; int /*<<< orphan*/  name; int /*<<< orphan*/ * riores; int /*<<< orphan*/  dbells; TYPE_1__ dev; void* priv; scalar_t__ sys_size; scalar_t__ index; int /*<<< orphan*/ * ops; } ;
struct tsi721_device {scalar_t__ regs; int /*<<< orphan*/  flags; struct rio_mport mport; struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MPORT ; 
 size_t RIO_DOORBELL_RESOURCE ; 
 size_t RIO_INB_MBOX_RESOURCE ; 
 int /*<<< orphan*/  RIO_MAX_MPORT_NAME ; 
 size_t RIO_OUTB_MBOX_RESOURCE ; 
 scalar_t__ RIO_PORT_GEN_CTL_CSR ; 
 int RIO_PORT_GEN_DISCOVERED ; 
 int RIO_PORT_GEN_HOST ; 
 int RIO_PORT_GEN_MASTER ; 
 scalar_t__ TSI721_DEVCTL ; 
 int TSI721_DEVCTL_SRBOOT_CMPL ; 
 int /*<<< orphan*/  TSI721_USING_MSI ; 
 int /*<<< orphan*/  TSI721_USING_MSIX ; 
 char* dev_driver_string (int /*<<< orphan*/ *) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  pci_enable_msi (struct pci_dev*) ; 
 int /*<<< orphan*/  rio_init_dbell_res (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rio_init_mbox_res (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int rio_mport_initialize (struct rio_mport*) ; 
 int rio_register_mport (struct rio_mport*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  tsi721_enable_msix (struct tsi721_device*) ; 
 int /*<<< orphan*/  tsi721_free_irq (struct tsi721_device*) ; 
 int /*<<< orphan*/  tsi721_mport_release ; 
 int tsi721_register_dma (struct tsi721_device*) ; 
 int tsi721_request_irq (struct tsi721_device*) ; 
 int /*<<< orphan*/  tsi721_rio_ops ; 
 int /*<<< orphan*/  tsi721_unregister_dma (struct tsi721_device*) ; 
 int /*<<< orphan*/  tsi_debug (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  tsi_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tsi721_setup_mport(struct tsi721_device *priv)
{
	struct pci_dev *pdev = priv->pdev;
	int err = 0;
	struct rio_mport *mport = &priv->mport;

	err = rio_mport_initialize(mport);
	if (err)
		return err;

	mport->ops = &tsi721_rio_ops;
	mport->index = 0;
	mport->sys_size = 0; /* small system */
	mport->priv = (void *)priv;
	mport->phys_efptr = 0x100;
	mport->phys_rmap = 1;
	mport->dev.parent = &pdev->dev;
	mport->dev.release = tsi721_mport_release;

	INIT_LIST_HEAD(&mport->dbells);

	rio_init_dbell_res(&mport->riores[RIO_DOORBELL_RESOURCE], 0, 0xffff);
	rio_init_mbox_res(&mport->riores[RIO_INB_MBOX_RESOURCE], 0, 3);
	rio_init_mbox_res(&mport->riores[RIO_OUTB_MBOX_RESOURCE], 0, 3);
	snprintf(mport->name, RIO_MAX_MPORT_NAME, "%s(%s)",
		 dev_driver_string(&pdev->dev), dev_name(&pdev->dev));

	/* Hook up interrupt handler */

#ifdef CONFIG_PCI_MSI
	if (!tsi721_enable_msix(priv))
		priv->flags |= TSI721_USING_MSIX;
	else if (!pci_enable_msi(pdev))
		priv->flags |= TSI721_USING_MSI;
	else
		tsi_debug(MPORT, &pdev->dev,
			 "MSI/MSI-X is not available. Using legacy INTx.");
#endif /* CONFIG_PCI_MSI */

	err = tsi721_request_irq(priv);

	if (err) {
		tsi_err(&pdev->dev, "Unable to get PCI IRQ %02X (err=0x%x)",
			pdev->irq, err);
		return err;
	}

#ifdef CONFIG_RAPIDIO_DMA_ENGINE
	err = tsi721_register_dma(priv);
	if (err)
		goto err_exit;
#endif
	/* Enable SRIO link */
	iowrite32(ioread32(priv->regs + TSI721_DEVCTL) |
		  TSI721_DEVCTL_SRBOOT_CMPL,
		  priv->regs + TSI721_DEVCTL);

	if (mport->host_deviceid >= 0)
		iowrite32(RIO_PORT_GEN_HOST | RIO_PORT_GEN_MASTER |
			  RIO_PORT_GEN_DISCOVERED,
			  priv->regs + (0x100 + RIO_PORT_GEN_CTL_CSR));
	else
		iowrite32(0, priv->regs + (0x100 + RIO_PORT_GEN_CTL_CSR));

	err = rio_register_mport(mport);
	if (err) {
		tsi721_unregister_dma(priv);
		goto err_exit;
	}

	return 0;

err_exit:
	tsi721_free_irq(priv);
	return err;
}