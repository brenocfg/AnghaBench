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

/* Variables and functions */
 int /*<<< orphan*/  __ppc64_runlatch_off () ; 
 int /*<<< orphan*/  __ppc64_runlatch_on () ; 
 int /*<<< orphan*/  fini_irq_for_idle_irqsoff () ; 
 unsigned long power7_idle_insn (unsigned long) ; 
 int /*<<< orphan*/  prep_irq_for_idle_irqsoff () ; 

__attribute__((used)) static unsigned long __power7_idle_type(unsigned long type)
{
	unsigned long srr1;

	if (!prep_irq_for_idle_irqsoff())
		return 0;

	__ppc64_runlatch_off();
	srr1 = power7_idle_insn(type);
	__ppc64_runlatch_on();

	fini_irq_for_idle_irqsoff();

	return srr1;
}