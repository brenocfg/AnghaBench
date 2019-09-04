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
struct TYPE_2__ {int base; int ngpio; int can_sleep; int /*<<< orphan*/  owner; int /*<<< orphan*/  request; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  parent; int /*<<< orphan*/  label; } ;
struct ad5592r_state {TYPE_1__ gpiochip; int /*<<< orphan*/  gpio_lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  gpio_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  ad5592r_gpio_direction_input ; 
 int /*<<< orphan*/  ad5592r_gpio_direction_output ; 
 int /*<<< orphan*/  ad5592r_gpio_get ; 
 int /*<<< orphan*/  ad5592r_gpio_request ; 
 int /*<<< orphan*/  ad5592r_gpio_set ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int gpiochip_add_data (TYPE_1__*,struct ad5592r_state*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad5592r_gpio_init(struct ad5592r_state *st)
{
	if (!st->gpio_map)
		return 0;

	st->gpiochip.label = dev_name(st->dev);
	st->gpiochip.base = -1;
	st->gpiochip.ngpio = 8;
	st->gpiochip.parent = st->dev;
	st->gpiochip.can_sleep = true;
	st->gpiochip.direction_input = ad5592r_gpio_direction_input;
	st->gpiochip.direction_output = ad5592r_gpio_direction_output;
	st->gpiochip.get = ad5592r_gpio_get;
	st->gpiochip.set = ad5592r_gpio_set;
	st->gpiochip.request = ad5592r_gpio_request;
	st->gpiochip.owner = THIS_MODULE;

	mutex_init(&st->gpio_lock);

	return gpiochip_add_data(&st->gpiochip, st);
}