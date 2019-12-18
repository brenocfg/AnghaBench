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
typedef  int u64 ;
struct thunderx_gpio {scalar_t__ register_base; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int GPIO_BIT_CFG_TX_OE ; 
 scalar_t__ bit_cfg_reg (unsigned int) ; 
 struct thunderx_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int readq (scalar_t__) ; 
 int /*<<< orphan*/  thunderx_gpio_is_gpio_nowarn (struct thunderx_gpio*,unsigned int) ; 

__attribute__((used)) static int thunderx_gpio_get_direction(struct gpio_chip *chip, unsigned int line)
{
	struct thunderx_gpio *txgpio = gpiochip_get_data(chip);
	u64 bit_cfg;

	if (!thunderx_gpio_is_gpio_nowarn(txgpio, line))
		/*
		 * Say it is input for now to avoid WARNing on
		 * gpiochip_add_data().  We will WARN if someone
		 * requests it or tries to use it.
		 */
		return 1;

	bit_cfg = readq(txgpio->register_base + bit_cfg_reg(line));

	return !(bit_cfg & GPIO_BIT_CFG_TX_OE);
}