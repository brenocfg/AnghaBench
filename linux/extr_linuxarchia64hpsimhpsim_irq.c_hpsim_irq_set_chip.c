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
struct irq_chip {int dummy; } ;

/* Variables and functions */
 struct irq_chip* irq_get_chip (int) ; 
 int /*<<< orphan*/  irq_set_chip (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_type_hp_sim ; 
 struct irq_chip no_irq_chip ; 

__attribute__((used)) static void hpsim_irq_set_chip(int irq)
{
	struct irq_chip *chip = irq_get_chip(irq);

	if (chip == &no_irq_chip)
		irq_set_chip(irq, &irq_type_hp_sim);
}