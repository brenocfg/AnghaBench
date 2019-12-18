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
struct tps65010 {int /*<<< orphan*/  client; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPS_DEFGPIO ; 
 struct tps65010* gpiochip_get_data (struct gpio_chip*) ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tps65010_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	int			value;
	struct tps65010		*tps;

	tps = gpiochip_get_data(chip);

	if (offset < 4) {
		value = i2c_smbus_read_byte_data(tps->client, TPS_DEFGPIO);
		if (value < 0)
			return value;
		if (value & (1 << (offset + 4)))	/* output */
			return !(value & (1 << offset));
		else					/* input */
			return !!(value & (1 << offset));
	}

	/* REVISIT we *could* report LED1/nPG and LED2 state ... */
	return 0;
}