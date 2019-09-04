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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  generic_handle_irq (int) ; 
 int i8259_irq () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t sni_isa_irq_handler(int dummy, void *p)
{
	int irq;

	irq = i8259_irq();
	if (unlikely(irq < 0))
		return IRQ_NONE;

	generic_handle_irq(irq);
	return IRQ_HANDLED;
}