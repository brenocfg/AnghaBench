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
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 unsigned int MV88E6352_G2_SCRATCH_GPIO_PCTL0 ; 
 int mv88e6xxx_g2_scratch_read (struct mv88e6xxx_chip*,int,int*) ; 
 int mv88e6xxx_g2_scratch_write (struct mv88e6xxx_chip*,int,int) ; 

__attribute__((used)) static int mv88e6352_g2_scratch_gpio_set_pctl(struct mv88e6xxx_chip *chip,
					      unsigned int pin, int func)
{
	int reg = MV88E6352_G2_SCRATCH_GPIO_PCTL0 + (pin / 2);
	int offset = (pin & 0x1) ? 4 : 0;
	u8 mask = (0x7 << offset);
	int err;
	u8 val;

	err = mv88e6xxx_g2_scratch_read(chip, reg, &val);
	if (err)
		return err;

	val = (val & ~mask) | ((func & mask) << offset);

	return mv88e6xxx_g2_scratch_write(chip, reg, val);
}