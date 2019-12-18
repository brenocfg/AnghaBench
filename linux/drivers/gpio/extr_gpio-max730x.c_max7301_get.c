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
struct max7301 {unsigned int* port_config; int out_level; int (* read ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PIN_CONFIG_IN_PULLUP 130 
#define  PIN_CONFIG_IN_WO_PULLUP 129 
 unsigned int PIN_CONFIG_MASK ; 
#define  PIN_CONFIG_OUT 128 
 struct max7301* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max7301_get(struct gpio_chip *chip, unsigned offset)
{
	struct max7301 *ts = gpiochip_get_data(chip);
	int config, level = -EINVAL;

	/* First 4 pins are unused in the controller */
	offset += 4;

	mutex_lock(&ts->lock);

	config = (ts->port_config[offset >> 2] >> ((offset & 3) << 1))
			& PIN_CONFIG_MASK;

	switch (config) {
	case PIN_CONFIG_OUT:
		/* Output: return cached level */
		level =  !!(ts->out_level & (1 << offset));
		break;
	case PIN_CONFIG_IN_WO_PULLUP:
	case PIN_CONFIG_IN_PULLUP:
		/* Input: read out */
		level = ts->read(ts->dev, 0x20 + offset) & 0x01;
	}
	mutex_unlock(&ts->lock);

	return level;
}