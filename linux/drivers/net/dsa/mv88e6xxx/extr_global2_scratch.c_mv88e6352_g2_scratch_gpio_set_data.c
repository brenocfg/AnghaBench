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
typedef  int u8 ;
struct mv88e6xxx_chip {int* gpio_data; } ;

/* Variables and functions */
 int MV88E6352_G2_SCRATCH_GPIO_DATA0 ; 
 int mv88e6xxx_g2_scratch_write (struct mv88e6xxx_chip*,int,int) ; 

__attribute__((used)) static int mv88e6352_g2_scratch_gpio_set_data(struct mv88e6xxx_chip *chip,
					      unsigned int pin, int value)
{
	u8 mask = (1 << (pin & 0x7));
	int offset = (pin / 8);
	int reg;

	reg = MV88E6352_G2_SCRATCH_GPIO_DATA0 + offset;

	if (value)
		chip->gpio_data[offset] |= mask;
	else
		chip->gpio_data[offset] &= ~mask;

	return mv88e6xxx_g2_scratch_write(chip, reg, chip->gpio_data[offset]);
}