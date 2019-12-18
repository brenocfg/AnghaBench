#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct smi_dev {int /*<<< orphan*/  lmmio; int /*<<< orphan*/ * ts_port; TYPE_1__* info; TYPE_2__* pci_dev; } ;
struct pci_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;
struct TYPE_3__ {scalar_t__ ts_0; scalar_t__ ts_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_INT ; 
 int /*<<< orphan*/  MSI_INT_ENA_CLR ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct smi_dev*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct smi_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msi (TYPE_2__*) ; 
 struct smi_dev* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smi_i2c_exit (struct smi_dev*) ; 
 int /*<<< orphan*/  smi_ir_exit (struct smi_dev*) ; 
 int /*<<< orphan*/  smi_port_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smi_remove(struct pci_dev *pdev)
{
	struct smi_dev *dev = pci_get_drvdata(pdev);

	smi_write(MSI_INT_ENA_CLR, ALL_INT);
	free_irq(dev->pci_dev->irq, dev);
#ifdef CONFIG_PCI_MSI
	pci_disable_msi(dev->pci_dev);
#endif
	if (dev->info->ts_1)
		smi_port_detach(&dev->ts_port[1]);
	if (dev->info->ts_0)
		smi_port_detach(&dev->ts_port[0]);

	smi_ir_exit(dev);
	smi_i2c_exit(dev);
	iounmap(dev->lmmio);
	pci_set_drvdata(pdev, NULL);
	pci_disable_device(pdev);
	kfree(dev);
}