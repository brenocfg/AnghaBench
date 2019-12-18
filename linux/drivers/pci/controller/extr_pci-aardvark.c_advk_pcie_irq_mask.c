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
typedef  int /*<<< orphan*/  u32 ;
struct irq_data {TYPE_1__* domain; } ;
struct advk_pcie {int dummy; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;
struct TYPE_2__ {struct advk_pcie* host_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_ISR1_INTX_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCIE_ISR1_MASK_REG ; 
 int /*<<< orphan*/  advk_readl (struct advk_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  advk_writel (struct advk_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irqd_to_hwirq (struct irq_data*) ; 

__attribute__((used)) static void advk_pcie_irq_mask(struct irq_data *d)
{
	struct advk_pcie *pcie = d->domain->host_data;
	irq_hw_number_t hwirq = irqd_to_hwirq(d);
	u32 mask;

	mask = advk_readl(pcie, PCIE_ISR1_MASK_REG);
	mask |= PCIE_ISR1_INTX_ASSERT(hwirq);
	advk_writel(pcie, mask, PCIE_ISR1_MASK_REG);
}