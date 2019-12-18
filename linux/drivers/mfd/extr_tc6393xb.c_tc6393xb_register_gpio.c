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
struct TYPE_2__ {char* label; int base; int ngpio; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  get; int /*<<< orphan*/  set; } ;
struct tc6393xb {TYPE_1__ gpio; } ;

/* Variables and functions */
 int gpiochip_add_data (TYPE_1__*,struct tc6393xb*) ; 
 int /*<<< orphan*/  tc6393xb_gpio_direction_input ; 
 int /*<<< orphan*/  tc6393xb_gpio_direction_output ; 
 int /*<<< orphan*/  tc6393xb_gpio_get ; 
 int /*<<< orphan*/  tc6393xb_gpio_set ; 

__attribute__((used)) static int tc6393xb_register_gpio(struct tc6393xb *tc6393xb, int gpio_base)
{
	tc6393xb->gpio.label = "tc6393xb";
	tc6393xb->gpio.base = gpio_base;
	tc6393xb->gpio.ngpio = 16;
	tc6393xb->gpio.set = tc6393xb_gpio_set;
	tc6393xb->gpio.get = tc6393xb_gpio_get;
	tc6393xb->gpio.direction_input = tc6393xb_gpio_direction_input;
	tc6393xb->gpio.direction_output = tc6393xb_gpio_direction_output;

	return gpiochip_add_data(&tc6393xb->gpio, tc6393xb);
}