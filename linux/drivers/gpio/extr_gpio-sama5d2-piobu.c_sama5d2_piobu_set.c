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
 int PIOBU_HIGH ; 
 int PIOBU_LOW ; 
 int /*<<< orphan*/  PIOBU_SOD ; 
 int /*<<< orphan*/  sama5d2_piobu_write_value (struct gpio_chip*,unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sama5d2_piobu_set(struct gpio_chip *chip, unsigned int pin,
			      int value)
{
	if (!value)
		value = PIOBU_LOW;
	else
		value = PIOBU_HIGH;

	sama5d2_piobu_write_value(chip, pin, PIOBU_SOD, value);
}