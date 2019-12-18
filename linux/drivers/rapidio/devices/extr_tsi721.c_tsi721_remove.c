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
struct tsi721_device {int flags; int /*<<< orphan*/  pdev; scalar_t__ odb_base; scalar_t__ regs; int /*<<< orphan*/  mport; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT ; 
 int TSI721_USING_MSI ; 
 int TSI721_USING_MSIX ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct tsi721_device*) ; 
 int /*<<< orphan*/  pci_clear_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_msix (int /*<<< orphan*/ ) ; 
 struct tsi721_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rio_unregister_mport (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsi721_bdma_maint_free (struct tsi721_device*) ; 
 int /*<<< orphan*/  tsi721_close_sr2pc_mapping (struct tsi721_device*) ; 
 int /*<<< orphan*/  tsi721_disable_ints (struct tsi721_device*) ; 
 int /*<<< orphan*/  tsi721_doorbell_free (struct tsi721_device*) ; 
 int /*<<< orphan*/  tsi721_free_irq (struct tsi721_device*) ; 
 int /*<<< orphan*/  tsi721_port_write_free (struct tsi721_device*) ; 
 int /*<<< orphan*/  tsi721_unregister_dma (struct tsi721_device*) ; 
 int /*<<< orphan*/  tsi_debug (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void tsi721_remove(struct pci_dev *pdev)
{
	struct tsi721_device *priv = pci_get_drvdata(pdev);

	tsi_debug(EXIT, &pdev->dev, "enter");

	tsi721_disable_ints(priv);
	tsi721_free_irq(priv);
	flush_scheduled_work();
	rio_unregister_mport(&priv->mport);

	tsi721_unregister_dma(priv);
	tsi721_bdma_maint_free(priv);
	tsi721_doorbell_free(priv);
	tsi721_port_write_free(priv);
	tsi721_close_sr2pc_mapping(priv);

	if (priv->regs)
		iounmap(priv->regs);
	if (priv->odb_base)
		iounmap(priv->odb_base);
#ifdef CONFIG_PCI_MSI
	if (priv->flags & TSI721_USING_MSIX)
		pci_disable_msix(priv->pdev);
	else if (priv->flags & TSI721_USING_MSI)
		pci_disable_msi(priv->pdev);
#endif
	pci_release_regions(pdev);
	pci_clear_master(pdev);
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, NULL);
	kfree(priv);
	tsi_debug(EXIT, &pdev->dev, "exit");
}