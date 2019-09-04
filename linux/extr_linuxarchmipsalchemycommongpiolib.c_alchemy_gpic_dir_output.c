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
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ AU1300_GPIO_BASE ; 
 int au1300_gpio_direction_output (scalar_t__,int) ; 

__attribute__((used)) static int alchemy_gpic_dir_output(struct gpio_chip *chip, unsigned int off,
				   int v)
{
	return au1300_gpio_direction_output(off + AU1300_GPIO_BASE, v);
}