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
struct efa_com_dev {int /*<<< orphan*/  reg_bar; } ;
struct efa_dev {int /*<<< orphan*/  ibdev; struct efa_com_dev edev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFA_BASE_BAR_MASK ; 
 int /*<<< orphan*/  devm_iounmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efa_com_admin_destroy (struct efa_com_dev*) ; 
 int /*<<< orphan*/  efa_com_mmio_reg_read_destroy (struct efa_com_dev*) ; 
 int /*<<< orphan*/  efa_disable_msix (struct efa_dev*) ; 
 int /*<<< orphan*/  efa_free_mgmnt_irq (struct efa_dev*) ; 
 int /*<<< orphan*/  efa_release_bars (struct efa_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dealloc_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct efa_dev* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void efa_remove_device(struct pci_dev *pdev)
{
	struct efa_dev *dev = pci_get_drvdata(pdev);
	struct efa_com_dev *edev;

	edev = &dev->edev;
	efa_com_admin_destroy(edev);
	efa_free_mgmnt_irq(dev);
	efa_disable_msix(dev);
	efa_com_mmio_reg_read_destroy(edev);
	devm_iounmap(&pdev->dev, edev->reg_bar);
	efa_release_bars(dev, EFA_BASE_BAR_MASK);
	ib_dealloc_device(&dev->ibdev);
	pci_disable_device(pdev);
}