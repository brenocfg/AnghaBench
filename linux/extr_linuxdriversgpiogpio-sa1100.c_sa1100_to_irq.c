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
struct TYPE_2__ {int irqbase; } ;

/* Variables and functions */
 TYPE_1__* sa1100_gpio_chip (struct gpio_chip*) ; 

__attribute__((used)) static int sa1100_to_irq(struct gpio_chip *chip, unsigned offset)
{
	return sa1100_gpio_chip(chip)->irqbase + offset;
}