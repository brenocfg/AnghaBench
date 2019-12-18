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

__attribute__((used)) static int uniphier_pro4_get_gpio_muxval(unsigned int pin,
					 unsigned int gpio_offset)
{
	if (gpio_offset >= 134 && gpio_offset <= 140)	/* XIRQ14-20 */
		return 2;

	return 7;
}