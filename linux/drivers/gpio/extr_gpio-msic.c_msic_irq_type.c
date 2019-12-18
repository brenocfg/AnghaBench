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
typedef  int u32 ;
struct TYPE_2__ {int ngpio; } ;
struct msic_gpio {int irq_base; int trig_change_mask; unsigned int trig_type; TYPE_1__ chip; } ;
struct irq_data {int irq; } ;

/* Variables and functions */
 int EINVAL ; 
 struct msic_gpio* irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static int msic_irq_type(struct irq_data *data, unsigned type)
{
	struct msic_gpio *mg = irq_data_get_irq_chip_data(data);
	u32 gpio = data->irq - mg->irq_base;

	if (gpio >= mg->chip.ngpio)
		return -EINVAL;

	/* mark for which gpio the trigger changed, protected by buslock */
	mg->trig_change_mask |= (1 << gpio);
	mg->trig_type = type;

	return 0;
}