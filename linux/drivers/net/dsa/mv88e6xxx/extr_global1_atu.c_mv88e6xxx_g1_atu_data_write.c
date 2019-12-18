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
struct mv88e6xxx_chip {int dummy; } ;
struct mv88e6xxx_atu_entry {int state; int portvec; scalar_t__ trunk; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E6XXX_G1_ATU_DATA ; 
 int MV88E6XXX_G1_ATU_DATA_TRUNK ; 
 int mv88e6xxx_g1_write (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int) ; 
 int mv88e6xxx_port_mask (struct mv88e6xxx_chip*) ; 

__attribute__((used)) static int mv88e6xxx_g1_atu_data_write(struct mv88e6xxx_chip *chip,
				       struct mv88e6xxx_atu_entry *entry)
{
	u16 data = entry->state & 0xf;

	if (entry->state) {
		if (entry->trunk)
			data |= MV88E6XXX_G1_ATU_DATA_TRUNK;

		data |= (entry->portvec & mv88e6xxx_port_mask(chip)) << 4;
	}

	return mv88e6xxx_g1_write(chip, MV88E6XXX_G1_ATU_DATA, data);
}