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
struct s3c_irq_intc {int /*<<< orphan*/  domain; int /*<<< orphan*/  reg_mask; int /*<<< orphan*/  reg_pending; } ;
struct s3c_irq_data {unsigned long sub_bits; struct s3c_irq_intc* sub_intc; struct s3c_irq_intc* intc; } ;
struct irq_desc {int dummy; } ;
struct irq_chip {int dummy; } ;

/* Variables and functions */
 unsigned int __ffs (unsigned long) ; 
 int /*<<< orphan*/  chained_irq_enter (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  chained_irq_exit (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct s3c_irq_data* irq_desc_get_chip_data (struct irq_desc*) ; 
 scalar_t__ irq_domain_get_of_node (int /*<<< orphan*/ ) ; 
 unsigned int irq_find_mapping (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned long readl_relaxed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s3c_irq_demux(struct irq_desc *desc)
{
	struct irq_chip *chip = irq_desc_get_chip(desc);
	struct s3c_irq_data *irq_data = irq_desc_get_chip_data(desc);
	struct s3c_irq_intc *intc = irq_data->intc;
	struct s3c_irq_intc *sub_intc = irq_data->sub_intc;
	unsigned int n, offset, irq;
	unsigned long src, msk;

	/* we're using individual domains for the non-dt case
	 * and one big domain for the dt case where the subintc
	 * starts at hwirq number 32.
	 */
	offset = irq_domain_get_of_node(intc->domain) ? 32 : 0;

	chained_irq_enter(chip, desc);

	src = readl_relaxed(sub_intc->reg_pending);
	msk = readl_relaxed(sub_intc->reg_mask);

	src &= ~msk;
	src &= irq_data->sub_bits;

	while (src) {
		n = __ffs(src);
		src &= ~(1 << n);
		irq = irq_find_mapping(sub_intc->domain, offset + n);
		generic_handle_irq(irq);
	}

	chained_irq_exit(chip, desc);
}