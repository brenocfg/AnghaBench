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
struct ioh_gpio {size_t ch; TYPE_2__* reg; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_4__ {TYPE_1__* regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  pi; } ;

/* Variables and functions */
 struct ioh_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int ioread32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ioh_gpio_get(struct gpio_chip *gpio, unsigned nr)
{
	struct ioh_gpio *chip =	gpiochip_get_data(gpio);

	return !!(ioread32(&chip->reg->regs[chip->ch].pi) & (1 << nr));
}