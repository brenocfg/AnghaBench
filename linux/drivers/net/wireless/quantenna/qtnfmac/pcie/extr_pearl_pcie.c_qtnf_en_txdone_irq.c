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
struct qtnf_pcie_pearl_state {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  pcie_reg_base; int /*<<< orphan*/  pcie_irq_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_HDP_INT_EN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCIE_HDP_INT_TX_BITS ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void qtnf_en_txdone_irq(struct qtnf_pcie_pearl_state *ps)
{
	unsigned long flags;

	spin_lock_irqsave(&ps->irq_lock, flags);
	ps->pcie_irq_mask |= PCIE_HDP_INT_TX_BITS;
	writel(ps->pcie_irq_mask, PCIE_HDP_INT_EN(ps->pcie_reg_base));
	spin_unlock_irqrestore(&ps->irq_lock, flags);
}