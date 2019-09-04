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
typedef  int /*<<< orphan*/  u16 ;
struct mv88e6xxx_chip {int dummy; } ;
struct mv88e6xxx_atu_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E6XXX_G1_ATU_OP_LOAD_DB ; 
 int mv88e6xxx_g1_atu_data_write (struct mv88e6xxx_chip*,struct mv88e6xxx_atu_entry*) ; 
 int mv88e6xxx_g1_atu_mac_write (struct mv88e6xxx_chip*,struct mv88e6xxx_atu_entry*) ; 
 int mv88e6xxx_g1_atu_op (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mv88e6xxx_g1_atu_op_wait (struct mv88e6xxx_chip*) ; 

int mv88e6xxx_g1_atu_loadpurge(struct mv88e6xxx_chip *chip, u16 fid,
			       struct mv88e6xxx_atu_entry *entry)
{
	int err;

	err = mv88e6xxx_g1_atu_op_wait(chip);
	if (err)
		return err;

	err = mv88e6xxx_g1_atu_mac_write(chip, entry);
	if (err)
		return err;

	err = mv88e6xxx_g1_atu_data_write(chip, entry);
	if (err)
		return err;

	return mv88e6xxx_g1_atu_op(chip, fid, MV88E6XXX_G1_ATU_OP_LOAD_DB);
}