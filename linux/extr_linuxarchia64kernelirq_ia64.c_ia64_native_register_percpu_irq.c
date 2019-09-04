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
struct irqaction {int dummy; } ;
typedef  unsigned int ia64_vector ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPU_MASK_ALL ; 
 int /*<<< orphan*/  IRQ_PER_CPU ; 
 int /*<<< orphan*/  bind_irq_vector (unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_percpu_irq ; 
 int /*<<< orphan*/  irq_set_chip (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_handler (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_status_flags (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_type_ia64_lsapic ; 
 int /*<<< orphan*/  setup_irq (unsigned int,struct irqaction*) ; 

void
ia64_native_register_percpu_irq (ia64_vector vec, struct irqaction *action)
{
	unsigned int irq;

	irq = vec;
	BUG_ON(bind_irq_vector(irq, vec, CPU_MASK_ALL));
	irq_set_status_flags(irq, IRQ_PER_CPU);
	irq_set_chip(irq, &irq_type_ia64_lsapic);
	if (action)
		setup_irq(irq, action);
	irq_set_handler(irq, handle_percpu_irq);
}