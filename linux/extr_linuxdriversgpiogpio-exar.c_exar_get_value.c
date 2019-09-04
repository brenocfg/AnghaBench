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
struct gpio_chip {int dummy; } ;
struct exar_gpio_chip {unsigned int first_pin; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 unsigned int EXAR_OFFSET_MPIOLVL_HI ; 
 unsigned int EXAR_OFFSET_MPIOLVL_LO ; 
 int exar_get (struct gpio_chip*,unsigned int) ; 
 struct exar_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static int exar_get_value(struct gpio_chip *chip, unsigned int offset)
{
	struct exar_gpio_chip *exar_gpio = gpiochip_get_data(chip);
	unsigned int addr = (offset + exar_gpio->first_pin) / 8 ?
		EXAR_OFFSET_MPIOLVL_HI : EXAR_OFFSET_MPIOLVL_LO;
	unsigned int bit  = (offset + exar_gpio->first_pin) % 8;

	return !!(exar_get(chip, addr) & BIT(bit));
}