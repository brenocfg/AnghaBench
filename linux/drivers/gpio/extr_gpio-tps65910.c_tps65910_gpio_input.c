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
struct tps65910_gpio {struct tps65910* tps65910; } ;
struct tps65910 {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_CFG_MASK ; 
 unsigned int TPS65910_GPIO0 ; 
 struct tps65910_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int tps65910_reg_clear_bits (struct tps65910*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tps65910_gpio_input(struct gpio_chip *gc, unsigned offset)
{
	struct tps65910_gpio *tps65910_gpio = gpiochip_get_data(gc);
	struct tps65910 *tps65910 = tps65910_gpio->tps65910;

	return tps65910_reg_clear_bits(tps65910, TPS65910_GPIO0 + offset,
						GPIO_CFG_MASK);
}