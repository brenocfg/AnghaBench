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
 int MV88E6XXX_G1_VTU_OP_VTU_LOAD_PURGE ; 
 int mv88e6185_g1_vtu_data_write (struct mv88e6xxx_chip*,struct mv88e6xxx_vtu_entry*) ; 
 int mv88e6xxx_g1_vtu_op (struct mv88e6xxx_chip*,int) ; 
 int mv88e6xxx_g1_vtu_op_wait (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_g1_vtu_vid_write (struct mv88e6xxx_chip*,struct mv88e6xxx_vtu_entry*) ; 

int mv88e6250_g1_vtu_loadpurge(struct mv88e6xxx_chip *chip,
			       struct mv88e6xxx_vtu_entry *entry)
{
	u16 op = MV88E6XXX_G1_VTU_OP_VTU_LOAD_PURGE;
	int err;

	err = mv88e6xxx_g1_vtu_op_wait(chip);
	if (err)
		return err;

	err = mv88e6xxx_g1_vtu_vid_write(chip, entry);
	if (err)
		return err;

	if (entry->valid) {
		err = mv88e6185_g1_vtu_data_write(chip, entry);
		if (err)
			return err;

		/* VTU DBNum[3:0] are located in VTU Operation 3:0
		 * VTU DBNum[5:4] are located in VTU Operation 9:8
		 */
		op |= entry->fid & 0x000f;
		op |= (entry->fid & 0x0030) << 4;
	}

	return mv88e6xxx_g1_vtu_op(chip, op);
}