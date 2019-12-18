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
struct irq_desc {int dummy; } ;
struct irq_chip {int dummy; } ;
struct TYPE_2__ {int* parents; } ;
struct gpio_chip {TYPE_1__ irq; } ;
struct bcm2835_pinctrl {int dummy; } ;

/* Variables and functions */
 int BCM2835_NUM_IRQS ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  bcm2835_gpio_irq_handle_bank (struct bcm2835_pinctrl*,int,int) ; 
 int /*<<< orphan*/  chained_irq_enter (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  chained_irq_exit (struct irq_chip*,struct irq_desc*) ; 
 struct bcm2835_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct gpio_chip* irq_desc_get_handler_data (struct irq_desc*) ; 
 int irq_desc_get_irq (struct irq_desc*) ; 

__attribute__((used)) static void bcm2835_gpio_irq_handler(struct irq_desc *desc)
{
	struct gpio_chip *chip = irq_desc_get_handler_data(desc);
	struct bcm2835_pinctrl *pc = gpiochip_get_data(chip);
	struct irq_chip *host_chip = irq_desc_get_chip(desc);
	int irq = irq_desc_get_irq(desc);
	int group;
	int i;

	for (i = 0; i < BCM2835_NUM_IRQS; i++) {
		if (chip->irq.parents[i] == irq) {
			group = i;
			break;
		}
	}
	/* This should not happen, every IRQ has a bank */
	if (i == BCM2835_NUM_IRQS)
		BUG();

	chained_irq_enter(host_chip, desc);

	switch (group) {
	case 0: /* IRQ0 covers GPIOs 0-27 */
		bcm2835_gpio_irq_handle_bank(pc, 0, 0x0fffffff);
		break;
	case 1: /* IRQ1 covers GPIOs 28-45 */
		bcm2835_gpio_irq_handle_bank(pc, 0, 0xf0000000);
		bcm2835_gpio_irq_handle_bank(pc, 1, 0x00003fff);
		break;
	case 2: /* IRQ2 covers GPIOs 46-53 */
		bcm2835_gpio_irq_handle_bank(pc, 1, 0x003fc000);
		break;
	}

	chained_irq_exit(host_chip, desc);
}