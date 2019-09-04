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
struct irq_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_irq (scalar_t__) ; 
 scalar_t__ fiq_start ; 
 int /*<<< orphan*/  irq_activate (struct irq_desc*) ; 
 struct irq_desc* irq_to_desc (scalar_t__) ; 

void enable_fiq(int fiq)
{
	struct irq_desc *desc = irq_to_desc(fiq + fiq_start);
	irq_activate(desc);
	enable_irq(fiq + fiq_start);
}