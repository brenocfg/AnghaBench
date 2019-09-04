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
 int mv88e6xxx_g2_scratch_read (struct mv88e6xxx_chip*,int,int*) ; 

__attribute__((used)) static int mv88e6xxx_g2_scratch_get_bit(struct mv88e6xxx_chip *chip,
					int base_reg, unsigned int offset,
					int *set)
{
	int reg = base_reg + (offset / 8);
	u8 mask = (1 << (offset & 0x7));
	u8 val;
	int err;

	err = mv88e6xxx_g2_scratch_read(chip, reg, &val);
	if (err)
		return err;

	*set = !!(mask & val);

	return 0;
}