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
 int exar_set_direction (struct gpio_chip*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  exar_set_value (struct gpio_chip*,unsigned int,int) ; 

__attribute__((used)) static int exar_direction_output(struct gpio_chip *chip, unsigned int offset,
				 int value)
{
	exar_set_value(chip, offset, value);
	return exar_set_direction(chip, 0, offset);
}