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
struct irq_desc {int dummy; } ;
struct irq_chip {int dummy; } ;
struct goldfish_pic_data {int /*<<< orphan*/  irq_domain; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ GFPIC_REG_IRQ_PENDING ; 
 int __fls (int) ; 
 int /*<<< orphan*/  chained_irq_enter (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  chained_irq_exit (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  generic_handle_irq (int) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct goldfish_pic_data* irq_desc_get_handler_data (struct irq_desc*) ; 
 int irq_linear_revmap (int /*<<< orphan*/ ,int) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static void goldfish_pic_cascade(struct irq_desc *desc)
{
	struct goldfish_pic_data *gfpic = irq_desc_get_handler_data(desc);
	struct irq_chip *host_chip = irq_desc_get_chip(desc);
	u32 pending, hwirq, virq;

	chained_irq_enter(host_chip, desc);

	pending = readl(gfpic->base + GFPIC_REG_IRQ_PENDING);
	while (pending) {
		hwirq = __fls(pending);
		virq = irq_linear_revmap(gfpic->irq_domain, hwirq);
		generic_handle_irq(virq);
		pending &= ~(1 << hwirq);
	}

	chained_irq_exit(host_chip, desc);
}