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
 int /*<<< orphan*/  gen_74x164_set_value (struct gpio_chip*,unsigned int,int) ; 

__attribute__((used)) static int gen_74x164_direction_output(struct gpio_chip *gc,
		unsigned offset, int val)
{
	gen_74x164_set_value(gc, offset, val);
	return 0;
}