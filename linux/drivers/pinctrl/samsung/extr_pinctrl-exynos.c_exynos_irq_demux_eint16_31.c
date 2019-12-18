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
struct samsung_pin_bank {int /*<<< orphan*/  irq_domain; scalar_t__ eint_offset; TYPE_1__* irq_chip; scalar_t__ eint_base; } ;
struct irq_desc {int dummy; } ;
struct irq_chip {int dummy; } ;
struct exynos_muxed_weint_data {int nr_banks; struct samsung_pin_bank** banks; } ;
struct TYPE_2__ {scalar_t__ eint_mask; scalar_t__ eint_pend; } ;

/* Variables and functions */
 int /*<<< orphan*/  chained_irq_enter (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  chained_irq_exit (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  exynos_irq_demux_eint (unsigned long,int /*<<< orphan*/ ) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct exynos_muxed_weint_data* irq_desc_get_handler_data (struct irq_desc*) ; 
 unsigned long readl (scalar_t__) ; 

__attribute__((used)) static void exynos_irq_demux_eint16_31(struct irq_desc *desc)
{
	struct irq_chip *chip = irq_desc_get_chip(desc);
	struct exynos_muxed_weint_data *eintd = irq_desc_get_handler_data(desc);
	unsigned long pend;
	unsigned long mask;
	int i;

	chained_irq_enter(chip, desc);

	for (i = 0; i < eintd->nr_banks; ++i) {
		struct samsung_pin_bank *b = eintd->banks[i];
		pend = readl(b->eint_base + b->irq_chip->eint_pend
				+ b->eint_offset);
		mask = readl(b->eint_base + b->irq_chip->eint_mask
				+ b->eint_offset);
		exynos_irq_demux_eint(pend & ~mask, b->irq_domain);
	}

	chained_irq_exit(chip, desc);
}