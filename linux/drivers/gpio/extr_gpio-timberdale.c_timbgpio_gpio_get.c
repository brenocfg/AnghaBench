#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct timbgpio {scalar_t__ membase; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ TGPIOVAL ; 
 struct timbgpio* gpiochip_get_data (struct gpio_chip*) ; 
 int ioread32 (scalar_t__) ; 

__attribute__((used)) static int timbgpio_gpio_get(struct gpio_chip *gpio, unsigned nr)
{
	struct timbgpio *tgpio = gpiochip_get_data(gpio);
	u32 value;

	value = ioread32(tgpio->membase + TGPIOVAL);
	return (value & (1 << nr)) ? 1 : 0;
}