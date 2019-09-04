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
struct mx25_tsadc {int /*<<< orphan*/  domain; int /*<<< orphan*/  regs; } ;
struct irq_desc {int dummy; } ;
struct irq_chip {int dummy; } ;

/* Variables and functions */
 int MX25_TGSR_GCQ_INT ; 
 int MX25_TGSR_TCQ_INT ; 
 int /*<<< orphan*/  MX25_TSC_TGSR ; 
 int /*<<< orphan*/  chained_irq_enter (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  chained_irq_exit (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct mx25_tsadc* irq_desc_get_handler_data (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_find_mapping (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void mx25_tsadc_irq_handler(struct irq_desc *desc)
{
	struct mx25_tsadc *tsadc = irq_desc_get_handler_data(desc);
	struct irq_chip *chip = irq_desc_get_chip(desc);
	u32 status;

	chained_irq_enter(chip, desc);

	regmap_read(tsadc->regs, MX25_TSC_TGSR, &status);

	if (status & MX25_TGSR_GCQ_INT)
		generic_handle_irq(irq_find_mapping(tsadc->domain, 1));

	if (status & MX25_TGSR_TCQ_INT)
		generic_handle_irq(irq_find_mapping(tsadc->domain, 0));

	chained_irq_exit(chip, desc);
}