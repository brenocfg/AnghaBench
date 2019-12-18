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
typedef  int u32 ;
struct pcie_port {int /*<<< orphan*/  lock; } ;
struct keystone_pcie {int dummy; } ;
struct irq_data {int hwirq; } ;
struct dw_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  MSI_IRQ_ENABLE_CLR (int) ; 
 struct pcie_port* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  ks_pcie_app_writel (struct keystone_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct dw_pcie* to_dw_pcie_from_pp (struct pcie_port*) ; 
 struct keystone_pcie* to_keystone_pcie (struct dw_pcie*) ; 

__attribute__((used)) static void ks_pcie_msi_mask(struct irq_data *data)
{
	struct pcie_port *pp = irq_data_get_irq_chip_data(data);
	struct keystone_pcie *ks_pcie;
	u32 irq = data->hwirq;
	struct dw_pcie *pci;
	unsigned long flags;
	u32 reg_offset;
	u32 bit_pos;

	raw_spin_lock_irqsave(&pp->lock, flags);

	pci = to_dw_pcie_from_pp(pp);
	ks_pcie = to_keystone_pcie(pci);

	reg_offset = irq % 8;
	bit_pos = irq >> 3;

	ks_pcie_app_writel(ks_pcie, MSI_IRQ_ENABLE_CLR(reg_offset),
			   BIT(bit_pos));

	raw_spin_unlock_irqrestore(&pp->lock, flags);
}