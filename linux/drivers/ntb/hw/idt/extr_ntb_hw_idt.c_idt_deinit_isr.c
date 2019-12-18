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
typedef  int u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct pci_dev* pdev; } ;
struct idt_ntb_dev {TYPE_1__ ntb; } ;

/* Variables and functions */
 int IDT_NTINTMSK_ALL ; 
 int /*<<< orphan*/  IDT_NT_NTINTMSK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct idt_ntb_dev*) ; 
 int idt_nt_read (struct idt_ntb_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idt_nt_write (struct idt_ntb_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_irq_vector (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void idt_deinit_isr(struct idt_ntb_dev *ndev)
{
	struct pci_dev *pdev = ndev->ntb.pdev;
	u32 ntint_mask;

	/* Mask interrupts back */
	ntint_mask = idt_nt_read(ndev, IDT_NT_NTINTMSK) | IDT_NTINTMSK_ALL;
	idt_nt_write(ndev, IDT_NT_NTINTMSK, ntint_mask);

	/* Manually free IRQ otherwise PCI free irq vectors will fail */
	devm_free_irq(&pdev->dev, pci_irq_vector(pdev, 0), ndev);

	/* Free allocated IRQ vectors */
	pci_free_irq_vectors(pdev);

	dev_dbg(&pdev->dev, "NTB interrupts deinitialized");
}