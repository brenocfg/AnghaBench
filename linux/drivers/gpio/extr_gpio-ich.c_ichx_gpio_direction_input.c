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
 int /*<<< orphan*/  GPIO_IO_SEL ; 
 int ichx_write_bit (int /*<<< orphan*/ ,unsigned int,int,int) ; 

__attribute__((used)) static int ichx_gpio_direction_input(struct gpio_chip *gpio, unsigned nr)
{
	/*
	 * Try setting pin as an input and verify it worked since many pins
	 * are output-only.
	 */
	return ichx_write_bit(GPIO_IO_SEL, nr, 1, 1);
}