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
struct gpio_chip {int dummy; } ;
struct abx500_pinctrl {int irq_cluster_size; TYPE_1__* parent; struct abx500_gpio_irq_cluster* irq_cluster; } ;
struct abx500_gpio_irq_cluster {int start; int end; int to_irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int EINVAL ; 
 struct abx500_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 int irq_create_mapping (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int abx500_gpio_to_irq(struct gpio_chip *chip, unsigned offset)
{
	struct abx500_pinctrl *pct = gpiochip_get_data(chip);
	/* The AB8500 GPIO numbers are off by one */
	int gpio = offset + 1;
	int hwirq;
	int i;

	for (i = 0; i < pct->irq_cluster_size; i++) {
		struct abx500_gpio_irq_cluster *cluster =
			&pct->irq_cluster[i];

		if (gpio >= cluster->start && gpio <= cluster->end) {
			/*
			 * The ABx500 GPIO's associated IRQs are clustered together
			 * throughout the interrupt numbers at irregular intervals.
			 * To solve this quandry, we have placed the read-in values
			 * into the cluster information table.
			 */
			hwirq = gpio - cluster->start + cluster->to_irq;
			return irq_create_mapping(pct->parent->domain, hwirq);
		}
	}

	return -EINVAL;
}