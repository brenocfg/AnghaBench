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
typedef  size_t u32 ;
struct irq_desc {int dummy; } ;
struct irq_chip {int dummy; } ;
struct combiner {size_t nregs; int /*<<< orphan*/  domain; TYPE_1__* regs; } ;
struct TYPE_2__ {size_t enabled; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 size_t __ffs (size_t) ; 
 int /*<<< orphan*/  chained_irq_enter (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  chained_irq_exit (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  generic_handle_irq (int) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct combiner* irq_desc_get_handler_data (struct irq_desc*) ; 
 int irq_find_mapping (int /*<<< orphan*/ ,int) ; 
 int irq_nr (size_t,size_t) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,int /*<<< orphan*/ ,size_t,size_t,int /*<<< orphan*/ ) ; 
 size_t readl_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static void combiner_handle_irq(struct irq_desc *desc)
{
	struct combiner *combiner = irq_desc_get_handler_data(desc);
	struct irq_chip *chip = irq_desc_get_chip(desc);
	u32 reg;

	chained_irq_enter(chip, desc);

	for (reg = 0; reg < combiner->nregs; reg++) {
		int virq;
		int hwirq;
		u32 bit;
		u32 status;

		bit = readl_relaxed(combiner->regs[reg].addr);
		status = bit & combiner->regs[reg].enabled;
		if (bit && !status)
			pr_warn_ratelimited("Unexpected IRQ on CPU%d: (%08x %08lx %p)\n",
					    smp_processor_id(), bit,
					    combiner->regs[reg].enabled,
					    combiner->regs[reg].addr);

		while (status) {
			bit = __ffs(status);
			status &= ~(1 << bit);
			hwirq = irq_nr(reg, bit);
			virq = irq_find_mapping(combiner->domain, hwirq);
			if (virq > 0)
				generic_handle_irq(virq);

		}
	}

	chained_irq_exit(chip, desc);
}