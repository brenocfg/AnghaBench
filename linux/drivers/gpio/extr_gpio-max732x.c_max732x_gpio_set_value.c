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
typedef  unsigned int uint8_t ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  max732x_gpio_set_mask (struct gpio_chip*,unsigned int,unsigned int,int) ; 

__attribute__((used)) static void max732x_gpio_set_value(struct gpio_chip *gc, unsigned off, int val)
{
	unsigned base = off & ~0x7;
	uint8_t mask = 1u << (off & 0x7);

	max732x_gpio_set_mask(gc, base, mask, val << (off & 0x7));
}