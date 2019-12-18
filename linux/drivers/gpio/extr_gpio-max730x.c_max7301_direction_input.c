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
typedef  int u8 ;
struct max7301 {int* port_config; int input_pullup_active; int (* write ) (int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int PIN_CONFIG_IN_PULLUP ; 
 int PIN_CONFIG_IN_WO_PULLUP ; 
 int PIN_CONFIG_MASK ; 
 struct max7301* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int max7301_direction_input(struct gpio_chip *chip, unsigned offset)
{
	struct max7301 *ts = gpiochip_get_data(chip);
	u8 *config;
	u8 offset_bits, pin_config;
	int ret;

	/* First 4 pins are unused in the controller */
	offset += 4;
	offset_bits = (offset & 3) << 1;

	config = &ts->port_config[offset >> 2];

	if (ts->input_pullup_active & BIT(offset))
		pin_config = PIN_CONFIG_IN_PULLUP;
	else
		pin_config = PIN_CONFIG_IN_WO_PULLUP;

	mutex_lock(&ts->lock);

	*config = (*config & ~(PIN_CONFIG_MASK << offset_bits))
			   | (pin_config << offset_bits);

	ret = ts->write(ts->dev, 0x08 + (offset >> 2), *config);

	mutex_unlock(&ts->lock);

	return ret;
}