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
struct atmel_pioctrl {struct atmel_pin** pins; } ;
struct atmel_pin {int /*<<< orphan*/  line; int /*<<< orphan*/  bank; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_PIO_CODR ; 
 int /*<<< orphan*/  ATMEL_PIO_SODR ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_gpio_write (struct atmel_pioctrl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct atmel_pioctrl* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static void atmel_gpio_set(struct gpio_chip *chip, unsigned offset, int val)
{
	struct atmel_pioctrl *atmel_pioctrl = gpiochip_get_data(chip);
	struct atmel_pin *pin = atmel_pioctrl->pins[offset];

	atmel_gpio_write(atmel_pioctrl, pin->bank,
			 val ? ATMEL_PIO_SODR : ATMEL_PIO_CODR,
			 BIT(pin->line));
}