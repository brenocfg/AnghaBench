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
struct rc5t583_gpio {TYPE_1__* rc5t583; } ;
struct gpio_chip {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int /*<<< orphan*/  RC5T583_GPIO_IOOUT ; 
 struct rc5t583_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  rc5t583_clear_bits (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc5t583_set_bits (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rc5t583_gpio_set(struct gpio_chip *gc, unsigned int offset, int val)
{
	struct rc5t583_gpio *rc5t583_gpio = gpiochip_get_data(gc);
	struct device *parent = rc5t583_gpio->rc5t583->dev;
	if (val)
		rc5t583_set_bits(parent, RC5T583_GPIO_IOOUT, BIT(offset));
	else
		rc5t583_clear_bits(parent, RC5T583_GPIO_IOOUT, BIT(offset));
}