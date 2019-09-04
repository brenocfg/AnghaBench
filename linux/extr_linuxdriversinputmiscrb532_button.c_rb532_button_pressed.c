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

/* Variables and functions */
 int /*<<< orphan*/  GPIO_BTN_S1 ; 
 int /*<<< orphan*/  LO_FOFF ; 
 int /*<<< orphan*/  gpio_direction_input (int /*<<< orphan*/ ) ; 
 int gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb532_gpio_set_func (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_latch_u5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool rb532_button_pressed(void)
{
	int val;

	set_latch_u5(0, LO_FOFF);
	gpio_direction_input(GPIO_BTN_S1);

	val = gpio_get_value(GPIO_BTN_S1);

	rb532_gpio_set_func(GPIO_BTN_S1);
	set_latch_u5(LO_FOFF, 0);

	return !val;
}