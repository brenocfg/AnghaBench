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
struct pcs_soc_data {int dummy; } ;
struct irq_desc {int dummy; } ;
struct irq_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  chained_irq_enter (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  chained_irq_exit (struct irq_chip*,struct irq_desc*) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct pcs_soc_data* irq_desc_get_handler_data (struct irq_desc*) ; 
 int /*<<< orphan*/  pcs_irq_handle (struct pcs_soc_data*) ; 

__attribute__((used)) static void pcs_irq_chain_handler(struct irq_desc *desc)
{
	struct pcs_soc_data *pcs_soc = irq_desc_get_handler_data(desc);
	struct irq_chip *chip;

	chip = irq_desc_get_chip(desc);
	chained_irq_enter(chip, desc);
	pcs_irq_handle(pcs_soc);
	/* REVISIT: export and add handle_bad_irq(irq, desc)? */
	chained_irq_exit(chip, desc);
}