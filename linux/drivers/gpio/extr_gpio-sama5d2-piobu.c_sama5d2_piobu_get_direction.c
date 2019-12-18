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
 int /*<<< orphan*/  PIOBU_DIRECTION ; 
 int PIOBU_IN ; 
 int sama5d2_piobu_read_value (struct gpio_chip*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sama5d2_piobu_get_direction(struct gpio_chip *chip,
				       unsigned int pin)
{
	int ret = sama5d2_piobu_read_value(chip, pin, PIOBU_DIRECTION);

	if (ret < 0)
		return ret;

	return (ret == PIOBU_IN) ? 1 : 0;
}