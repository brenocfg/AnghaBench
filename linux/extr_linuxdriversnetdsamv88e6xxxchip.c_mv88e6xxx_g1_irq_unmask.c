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
struct TYPE_2__ {int masked; } ;
struct mv88e6xxx_chip {TYPE_1__ g1_irq; } ;
struct irq_data {unsigned int hwirq; } ;

/* Variables and functions */
 struct mv88e6xxx_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static void mv88e6xxx_g1_irq_unmask(struct irq_data *d)
{
	struct mv88e6xxx_chip *chip = irq_data_get_irq_chip_data(d);
	unsigned int n = d->hwirq;

	chip->g1_irq.masked &= ~(1 << n);
}