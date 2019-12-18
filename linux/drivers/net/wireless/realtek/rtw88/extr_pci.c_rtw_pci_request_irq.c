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
struct rtw_dev {int /*<<< orphan*/  dev; } ;
struct pci_dev {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 unsigned int PCI_IRQ_LEGACY ; 
 unsigned int PCI_IRQ_MSI ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rtw_dev*) ; 
 int pci_alloc_irq_vectors (struct pci_dev*,int,int,unsigned int) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 int /*<<< orphan*/  rtw_disable_msi ; 
 int /*<<< orphan*/  rtw_err (struct rtw_dev*,char*,...) ; 
 int /*<<< orphan*/  rtw_pci_interrupt_handler ; 
 int /*<<< orphan*/  rtw_pci_interrupt_threadfn ; 

__attribute__((used)) static int rtw_pci_request_irq(struct rtw_dev *rtwdev, struct pci_dev *pdev)
{
	unsigned int flags = PCI_IRQ_LEGACY;
	int ret;

	if (!rtw_disable_msi)
		flags |= PCI_IRQ_MSI;

	ret = pci_alloc_irq_vectors(pdev, 1, 1, flags);
	if (ret < 0) {
		rtw_err(rtwdev, "failed to alloc PCI irq vectors\n");
		return ret;
	}

	ret = devm_request_threaded_irq(rtwdev->dev, pdev->irq,
					rtw_pci_interrupt_handler,
					rtw_pci_interrupt_threadfn,
					IRQF_SHARED, KBUILD_MODNAME, rtwdev);
	if (ret) {
		rtw_err(rtwdev, "failed to request irq %d\n", ret);
		pci_free_irq_vectors(pdev);
	}

	return ret;
}