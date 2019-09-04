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
struct pci_dev {int dummy; } ;
struct msi_msg {int address_hi; int data; int /*<<< orphan*/  address_lo; } ;
struct msi_desc {int dummy; } ;

/* Variables and functions */
 int ENOSPC ; 
 int IOP13XX_MU_MIMR_CORE_SELECT ; 
 int /*<<< orphan*/  IOP13XX_MU_MIMR_PCI ; 
 int /*<<< orphan*/  IRQ_IOP13XX_MSI_0 ; 
 int NR_IOP13XX_IRQS ; 
 int /*<<< orphan*/  handle_simple_irq ; 
 int iop13xx_cpu_id () ; 
 int /*<<< orphan*/  iop13xx_msi_chip ; 
 int irq_alloc_desc_from (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  irq_free_desc (int) ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_msi_desc (int,struct msi_desc*) ; 
 int /*<<< orphan*/  pci_write_msi_msg (int,struct msi_msg*) ; 

int arch_setup_msi_irq(struct pci_dev *pdev, struct msi_desc *desc)
{
	int id, irq = irq_alloc_desc_from(IRQ_IOP13XX_MSI_0, -1);
	struct msi_msg msg;

	if (irq < 0)
		return irq;

	if (irq >= NR_IOP13XX_IRQS) {
		irq_free_desc(irq);
		return -ENOSPC;
	}

	irq_set_msi_desc(irq, desc);

	msg.address_hi = 0x0;
	msg.address_lo = IOP13XX_MU_MIMR_PCI;

	id = iop13xx_cpu_id();
	msg.data = (id << IOP13XX_MU_MIMR_CORE_SELECT) | (irq & 0x7f);

	pci_write_msi_msg(irq, &msg);
	irq_set_chip_and_handler(irq, &iop13xx_msi_chip, handle_simple_irq);

	return 0;
}