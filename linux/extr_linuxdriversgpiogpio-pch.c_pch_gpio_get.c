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
struct pch_gpio {TYPE_1__* reg; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pi; } ;

/* Variables and functions */
 struct pch_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 unsigned int ioread32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pch_gpio_get(struct gpio_chip *gpio, unsigned nr)
{
	struct pch_gpio *chip =	gpiochip_get_data(gpio);

	return (ioread32(&chip->reg->pi) >> nr) & 1;
}