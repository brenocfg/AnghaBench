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
typedef  int uint32_t ;
struct gpio_chip {int can_sleep; unsigned int base; int ngpio; int /*<<< orphan*/  owner; int /*<<< orphan*/ * parent; int /*<<< orphan*/  label; int /*<<< orphan*/  get; int /*<<< orphan*/  set_multiple; int /*<<< orphan*/  set; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; } ;
struct max732x_chip {unsigned int dir_output; unsigned int dir_input; unsigned int mask_group_a; TYPE_1__* client; struct gpio_chip gpio_chip; } ;
struct i2c_device_id {size_t driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  PORT_INPUT 130 
#define  PORT_OPENDRAIN 129 
#define  PORT_OUTPUT 128 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/ * max732x_features ; 
 int /*<<< orphan*/  max732x_gpio_direction_input ; 
 int /*<<< orphan*/  max732x_gpio_direction_output ; 
 int /*<<< orphan*/  max732x_gpio_get_value ; 
 int /*<<< orphan*/  max732x_gpio_set_multiple ; 
 int /*<<< orphan*/  max732x_gpio_set_value ; 

__attribute__((used)) static int max732x_setup_gpio(struct max732x_chip *chip,
					const struct i2c_device_id *id,
					unsigned gpio_start)
{
	struct gpio_chip *gc = &chip->gpio_chip;
	uint32_t id_data = (uint32_t)max732x_features[id->driver_data];
	int i, port = 0;

	for (i = 0; i < 16; i++, id_data >>= 2) {
		unsigned int mask = 1 << port;

		switch (id_data & 0x3) {
		case PORT_OUTPUT:
			chip->dir_output |= mask;
			break;
		case PORT_INPUT:
			chip->dir_input |= mask;
			break;
		case PORT_OPENDRAIN:
			chip->dir_output |= mask;
			chip->dir_input |= mask;
			break;
		default:
			continue;
		}

		if (i < 8)
			chip->mask_group_a |= mask;
		port++;
	}

	if (chip->dir_input)
		gc->direction_input = max732x_gpio_direction_input;
	if (chip->dir_output) {
		gc->direction_output = max732x_gpio_direction_output;
		gc->set = max732x_gpio_set_value;
		gc->set_multiple = max732x_gpio_set_multiple;
	}
	gc->get = max732x_gpio_get_value;
	gc->can_sleep = true;

	gc->base = gpio_start;
	gc->ngpio = port;
	gc->label = chip->client->name;
	gc->parent = &chip->client->dev;
	gc->owner = THIS_MODULE;

	return port;
}