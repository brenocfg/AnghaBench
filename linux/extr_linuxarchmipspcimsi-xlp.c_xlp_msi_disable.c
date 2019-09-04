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
struct xlp_msi_data {unsigned int msi_enabled_mask; int /*<<< orphan*/  msi_lock; int /*<<< orphan*/  lnkbase; } ;
struct irq_data {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_9XX_MSI_EN ; 
 int /*<<< orphan*/  PCIE_MSI_EN ; 
 scalar_t__ cpu_is_xlp9xx () ; 
 struct xlp_msi_data* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int nlm_irq_msivec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void xlp_msi_disable(struct irq_data *d)
{
	struct xlp_msi_data *md = irq_data_get_irq_chip_data(d);
	unsigned long flags;
	int vec;

	vec = nlm_irq_msivec(d->irq);
	spin_lock_irqsave(&md->msi_lock, flags);
	md->msi_enabled_mask &= ~(1u << vec);
	if (cpu_is_xlp9xx())
		nlm_write_reg(md->lnkbase, PCIE_9XX_MSI_EN,
				md->msi_enabled_mask);
	else
		nlm_write_reg(md->lnkbase, PCIE_MSI_EN, md->msi_enabled_mask);
	spin_unlock_irqrestore(&md->msi_lock, flags);
}