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
struct nwl_pcie {int /*<<< orphan*/  leg_mask_lock; } ;
struct irq_desc {int dummy; } ;
struct irq_data {int hwirq; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSGF_LEG_MASK ; 
 struct nwl_pcie* irq_desc_get_chip_data (struct irq_desc*) ; 
 struct irq_desc* irq_to_desc (int /*<<< orphan*/ ) ; 
 int nwl_bridge_readl (struct nwl_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nwl_bridge_writel (struct nwl_pcie*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void nwl_mask_leg_irq(struct irq_data *data)
{
	struct irq_desc *desc = irq_to_desc(data->irq);
	struct nwl_pcie *pcie;
	unsigned long flags;
	u32 mask;
	u32 val;

	pcie = irq_desc_get_chip_data(desc);
	mask = 1 << (data->hwirq - 1);
	raw_spin_lock_irqsave(&pcie->leg_mask_lock, flags);
	val = nwl_bridge_readl(pcie, MSGF_LEG_MASK);
	nwl_bridge_writel(pcie, (val & (~mask)), MSGF_LEG_MASK);
	raw_spin_unlock_irqrestore(&pcie->leg_mask_lock, flags);
}