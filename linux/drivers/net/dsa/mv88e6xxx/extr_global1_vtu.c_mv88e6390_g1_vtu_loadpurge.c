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
struct mv88e6xxx_vtu_entry {int /*<<< orphan*/  member; int /*<<< orphan*/  state; scalar_t__ valid; } ;
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E6XXX_G1_VTU_OP_STU_LOAD_PURGE ; 
 int /*<<< orphan*/  MV88E6XXX_G1_VTU_OP_VTU_LOAD_PURGE ; 
 int mv88e6390_g1_vtu_data_write (struct mv88e6xxx_chip*,int /*<<< orphan*/ ) ; 
 int mv88e6xxx_g1_vtu_fid_write (struct mv88e6xxx_chip*,struct mv88e6xxx_vtu_entry*) ; 
 int mv88e6xxx_g1_vtu_op (struct mv88e6xxx_chip*,int /*<<< orphan*/ ) ; 
 int mv88e6xxx_g1_vtu_op_wait (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_g1_vtu_sid_write (struct mv88e6xxx_chip*,struct mv88e6xxx_vtu_entry*) ; 
 int mv88e6xxx_g1_vtu_vid_write (struct mv88e6xxx_chip*,struct mv88e6xxx_vtu_entry*) ; 

int mv88e6390_g1_vtu_loadpurge(struct mv88e6xxx_chip *chip,
			       struct mv88e6xxx_vtu_entry *entry)
{
	int err;

	err = mv88e6xxx_g1_vtu_op_wait(chip);
	if (err)
		return err;

	err = mv88e6xxx_g1_vtu_vid_write(chip, entry);
	if (err)
		return err;

	if (entry->valid) {
		/* Write PortState data */
		err = mv88e6390_g1_vtu_data_write(chip, entry->state);
		if (err)
			return err;

		err = mv88e6xxx_g1_vtu_sid_write(chip, entry);
		if (err)
			return err;

		/* Load STU entry */
		err = mv88e6xxx_g1_vtu_op(chip,
					  MV88E6XXX_G1_VTU_OP_STU_LOAD_PURGE);
		if (err)
			return err;

		/* Write MemberTag data */
		err = mv88e6390_g1_vtu_data_write(chip, entry->member);
		if (err)
			return err;

		err = mv88e6xxx_g1_vtu_fid_write(chip, entry);
		if (err)
			return err;
	}

	/* Load/Purge VTU entry */
	return mv88e6xxx_g1_vtu_op(chip, MV88E6XXX_G1_VTU_OP_VTU_LOAD_PURGE);
}