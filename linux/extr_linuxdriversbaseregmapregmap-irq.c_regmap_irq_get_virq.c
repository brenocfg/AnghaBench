#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct regmap_irq_chip_data {int /*<<< orphan*/  domain; TYPE_2__* chip; } ;
struct TYPE_4__ {TYPE_1__* irqs; } ;
struct TYPE_3__ {int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int EINVAL ; 
 int irq_create_mapping (int /*<<< orphan*/ ,int) ; 

int regmap_irq_get_virq(struct regmap_irq_chip_data *data, int irq)
{
	/* Handle holes in the IRQ list */
	if (!data->chip->irqs[irq].mask)
		return -EINVAL;

	return irq_create_mapping(data->domain, irq);
}