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
typedef  enum au1300_multifunc_pins { ____Placeholder_au1300_multifunc_pins } au1300_multifunc_pins ;

/* Variables and functions */
 int AU1300_GPIO_BASE ; 
 int /*<<< orphan*/  au1300_gpio_direction_input (int) ; 

void au1300_pinfunc_to_gpio(enum au1300_multifunc_pins gpio)
{
	au1300_gpio_direction_input(gpio + AU1300_GPIO_BASE);
}