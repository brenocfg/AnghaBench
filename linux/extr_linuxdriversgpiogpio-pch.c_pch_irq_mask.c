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
struct pch_gpio {int irq_base; TYPE_1__* reg; } ;
struct irq_data {int irq; } ;
struct irq_chip_generic {struct pch_gpio* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  imask; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 
 struct irq_chip_generic* irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static void pch_irq_mask(struct irq_data *d)
{
	struct irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	struct pch_gpio *chip = gc->private;

	iowrite32(1 << (d->irq - chip->irq_base), &chip->reg->imask);
}