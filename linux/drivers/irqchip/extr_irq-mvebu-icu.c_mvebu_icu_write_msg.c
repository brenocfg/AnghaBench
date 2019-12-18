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
struct mvebu_icu_msi_data {int dummy; } ;
struct mvebu_icu_irq_data {int type; unsigned int icu_group; struct mvebu_icu* icu; } ;
struct mvebu_icu {scalar_t__ base; } ;
struct msi_msg {unsigned int data; scalar_t__ address_hi; scalar_t__ address_lo; } ;
struct msi_desc {int /*<<< orphan*/  irq; } ;
struct irq_data {scalar_t__ hwirq; struct mvebu_icu_irq_data* chip_data; int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 unsigned int ICU_GROUP_SHIFT ; 
 scalar_t__ ICU_INT_CFG (scalar_t__) ; 
 unsigned int ICU_INT_ENABLE ; 
 unsigned int ICU_IS_EDGE ; 
 scalar_t__ ICU_SATA0_ICU_ID ; 
 scalar_t__ ICU_SATA1_ICU_ID ; 
 int IRQ_TYPE_EDGE_RISING ; 
 struct irq_data* irq_get_irq_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvebu_icu_init (struct mvebu_icu*,struct mvebu_icu_msi_data*,struct msi_msg*) ; 
 struct mvebu_icu_msi_data* platform_msi_get_host_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned int,scalar_t__) ; 

__attribute__((used)) static void mvebu_icu_write_msg(struct msi_desc *desc, struct msi_msg *msg)
{
	struct irq_data *d = irq_get_irq_data(desc->irq);
	struct mvebu_icu_msi_data *msi_data = platform_msi_get_host_data(d->domain);
	struct mvebu_icu_irq_data *icu_irqd = d->chip_data;
	struct mvebu_icu *icu = icu_irqd->icu;
	unsigned int icu_int;

	if (msg->address_lo || msg->address_hi) {
		/* One off initialization per domain */
		mvebu_icu_init(icu, msi_data, msg);
		/* Configure the ICU with irq number & type */
		icu_int = msg->data | ICU_INT_ENABLE;
		if (icu_irqd->type & IRQ_TYPE_EDGE_RISING)
			icu_int |= ICU_IS_EDGE;
		icu_int |= icu_irqd->icu_group << ICU_GROUP_SHIFT;
	} else {
		/* De-configure the ICU */
		icu_int = 0;
	}

	writel_relaxed(icu_int, icu->base + ICU_INT_CFG(d->hwirq));

	/*
	 * The SATA unit has 2 ports, and a dedicated ICU entry per
	 * port. The ahci sata driver supports only one irq interrupt
	 * per SATA unit. To solve this conflict, we configure the 2
	 * SATA wired interrupts in the south bridge into 1 GIC
	 * interrupt in the north bridge. Even if only a single port
	 * is enabled, if sata node is enabled, both interrupts are
	 * configured (regardless of which port is actually in use).
	 */
	if (d->hwirq == ICU_SATA0_ICU_ID || d->hwirq == ICU_SATA1_ICU_ID) {
		writel_relaxed(icu_int,
			       icu->base + ICU_INT_CFG(ICU_SATA0_ICU_ID));
		writel_relaxed(icu_int,
			       icu->base + ICU_INT_CFG(ICU_SATA1_ICU_ID));
	}
}