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
typedef  unsigned int u8 ;
typedef  unsigned int u16 ;
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ MV88E6XXX_G1_VTU_DATA1 ; 
 int mv88e6xxx_g1_read (struct mv88e6xxx_chip*,scalar_t__,unsigned int*) ; 
 int mv88e6xxx_num_ports (struct mv88e6xxx_chip*) ; 

__attribute__((used)) static int mv88e6390_g1_vtu_data_read(struct mv88e6xxx_chip *chip, u8 *data)
{
	u16 regs[2];
	int i;

	/* Read the 2 VTU/STU Data registers */
	for (i = 0; i < 2; ++i) {
		u16 *reg = &regs[i];
		int err;

		err = mv88e6xxx_g1_read(chip, MV88E6XXX_G1_VTU_DATA1 + i, reg);
		if (err)
			return err;
	}

	/* Extract data */
	for (i = 0; i < mv88e6xxx_num_ports(chip); ++i) {
		unsigned int offset = (i % 8) * 2;

		data[i] = (regs[i / 8] >> offset) & 0x3;
	}

	return 0;
}