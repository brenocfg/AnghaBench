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
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E6352_G2_SCRATCH_GPIO_DATA0 ; 
 int mv88e6xxx_g2_scratch_get_bit (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,unsigned int,int*) ; 

__attribute__((used)) static int mv88e6352_g2_scratch_gpio_get_data(struct mv88e6xxx_chip *chip,
					      unsigned int pin)
{
	int val = 0;
	int err;

	err = mv88e6xxx_g2_scratch_get_bit(chip,
					   MV88E6352_G2_SCRATCH_GPIO_DATA0,
					   pin, &val);
	if (err)
		return err;

	return val;
}