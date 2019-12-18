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
struct plic_handler {scalar_t__ hart_base; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 scalar_t__ CONTEXT_CLAIM ; 
 int /*<<< orphan*/  plic_handlers ; 
 struct plic_handler* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void plic_irq_eoi(struct irq_data *d)
{
	struct plic_handler *handler = this_cpu_ptr(&plic_handlers);

	writel(d->hwirq, handler->hart_base + CONTEXT_CLAIM);
}