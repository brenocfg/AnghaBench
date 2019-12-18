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
struct samsung_pin_bank {int /*<<< orphan*/  irq_domain; } ;
struct irq_desc {int dummy; } ;
struct irq_chip {int dummy; } ;
struct exynos_weint_data {int /*<<< orphan*/  irq; struct samsung_pin_bank* bank; } ;

/* Variables and functions */
 int /*<<< orphan*/  chained_irq_enter (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  chained_irq_exit (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  generic_handle_irq (int) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct exynos_weint_data* irq_desc_get_handler_data (struct irq_desc*) ; 
 int irq_linear_revmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos_irq_eint0_15(struct irq_desc *desc)
{
	struct exynos_weint_data *eintd = irq_desc_get_handler_data(desc);
	struct samsung_pin_bank *bank = eintd->bank;
	struct irq_chip *chip = irq_desc_get_chip(desc);
	int eint_irq;

	chained_irq_enter(chip, desc);

	eint_irq = irq_linear_revmap(bank->irq_domain, eintd->irq);
	generic_handle_irq(eint_irq);

	chained_irq_exit(chip, desc);
}