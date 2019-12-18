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
typedef  int u16 ;
struct mv88e6xxx_vtu_entry {int* member; int* state; } ;
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ MV88E6XXX_G1_VTU_DATA1 ; 
 int mv88e6xxx_g1_write (struct mv88e6xxx_chip*,scalar_t__,int) ; 
 int mv88e6xxx_num_ports (struct mv88e6xxx_chip*) ; 

__attribute__((used)) static int mv88e6185_g1_vtu_data_write(struct mv88e6xxx_chip *chip,
				       struct mv88e6xxx_vtu_entry *entry)
{
	u16 regs[3] = { 0 };
	int i;

	/* Insert MemberTag and PortState data */
	for (i = 0; i < mv88e6xxx_num_ports(chip); ++i) {
		unsigned int member_offset = (i % 4) * 4;
		unsigned int state_offset = member_offset + 2;

		regs[i / 4] |= (entry->member[i] & 0x3) << member_offset;
		regs[i / 4] |= (entry->state[i] & 0x3) << state_offset;
	}

	/* Write all 3 VTU/STU Data registers */
	for (i = 0; i < 3; ++i) {
		u16 reg = regs[i];
		int err;

		err = mv88e6xxx_g1_write(chip, MV88E6XXX_G1_VTU_DATA1 + i, reg);
		if (err)
			return err;
	}

	return 0;
}