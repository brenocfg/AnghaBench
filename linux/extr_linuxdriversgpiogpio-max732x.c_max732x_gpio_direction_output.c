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
struct max732x_chip {unsigned int dir_output; TYPE_1__* client; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,unsigned int) ; 
 struct max732x_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  max732x_gpio_set_value (struct gpio_chip*,unsigned int,int) ; 

__attribute__((used)) static int max732x_gpio_direction_output(struct gpio_chip *gc,
		unsigned off, int val)
{
	struct max732x_chip *chip = gpiochip_get_data(gc);
	unsigned int mask = 1u << off;

	if ((mask & chip->dir_output) == 0) {
		dev_dbg(&chip->client->dev, "%s port %d is input only\n",
			chip->client->name, off);
		return -EACCES;
	}

	max732x_gpio_set_value(gc, off, val);
	return 0;
}