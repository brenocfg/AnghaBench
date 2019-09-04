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
struct mv88e6xxx_vtu_entry {int /*<<< orphan*/  valid; } ;
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E6XXX_G1_VTU_OP_VTU_GET_NEXT ; 
 int mv88e6xxx_g1_vtu_op (struct mv88e6xxx_chip*,int /*<<< orphan*/ ) ; 
 int mv88e6xxx_g1_vtu_op_wait (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_g1_vtu_vid_read (struct mv88e6xxx_chip*,struct mv88e6xxx_vtu_entry*) ; 
 int mv88e6xxx_g1_vtu_vid_write (struct mv88e6xxx_chip*,struct mv88e6xxx_vtu_entry*) ; 

__attribute__((used)) static int mv88e6xxx_g1_vtu_getnext(struct mv88e6xxx_chip *chip,
				    struct mv88e6xxx_vtu_entry *entry)
{
	int err;

	err = mv88e6xxx_g1_vtu_op_wait(chip);
	if (err)
		return err;

	/* To get the next higher active VID, the VTU GetNext operation can be
	 * started again without setting the VID registers since it already
	 * contains the last VID.
	 *
	 * To save a few hardware accesses and abstract this to the caller,
	 * write the VID only once, when the entry is given as invalid.
	 */
	if (!entry->valid) {
		err = mv88e6xxx_g1_vtu_vid_write(chip, entry);
		if (err)
			return err;
	}

	err = mv88e6xxx_g1_vtu_op(chip, MV88E6XXX_G1_VTU_OP_VTU_GET_NEXT);
	if (err)
		return err;

	return mv88e6xxx_g1_vtu_vid_read(chip, entry);
}