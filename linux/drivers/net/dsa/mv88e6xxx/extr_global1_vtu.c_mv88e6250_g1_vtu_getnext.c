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
struct mv88e6xxx_vtu_entry {int fid; scalar_t__ valid; } ;
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E6XXX_G1_VTU_OP ; 
 int mv88e6185_g1_vtu_data_read (struct mv88e6xxx_chip*,struct mv88e6xxx_vtu_entry*) ; 
 int mv88e6xxx_g1_read (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int*) ; 
 int mv88e6xxx_g1_vtu_getnext (struct mv88e6xxx_chip*,struct mv88e6xxx_vtu_entry*) ; 

int mv88e6250_g1_vtu_getnext(struct mv88e6xxx_chip *chip,
			     struct mv88e6xxx_vtu_entry *entry)
{
	u16 val;
	int err;

	err = mv88e6xxx_g1_vtu_getnext(chip, entry);
	if (err)
		return err;

	if (entry->valid) {
		err = mv88e6185_g1_vtu_data_read(chip, entry);
		if (err)
			return err;

		/* VTU DBNum[3:0] are located in VTU Operation 3:0
		 * VTU DBNum[5:4] are located in VTU Operation 9:8
		 */
		err = mv88e6xxx_g1_read(chip, MV88E6XXX_G1_VTU_OP, &val);
		if (err)
			return err;

		entry->fid = val & 0x000f;
		entry->fid |= (val & 0x0300) >> 4;
	}

	return 0;
}