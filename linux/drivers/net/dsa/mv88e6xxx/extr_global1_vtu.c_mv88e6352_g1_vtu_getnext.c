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
struct mv88e6xxx_vtu_entry {scalar_t__ valid; } ;
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int mv88e6185_g1_vtu_data_read (struct mv88e6xxx_chip*,struct mv88e6xxx_vtu_entry*) ; 
 int mv88e6xxx_g1_vtu_fid_read (struct mv88e6xxx_chip*,struct mv88e6xxx_vtu_entry*) ; 
 int mv88e6xxx_g1_vtu_getnext (struct mv88e6xxx_chip*,struct mv88e6xxx_vtu_entry*) ; 
 int mv88e6xxx_g1_vtu_stu_get (struct mv88e6xxx_chip*,struct mv88e6xxx_vtu_entry*) ; 

int mv88e6352_g1_vtu_getnext(struct mv88e6xxx_chip *chip,
			     struct mv88e6xxx_vtu_entry *entry)
{
	int err;

	/* Fetch VLAN MemberTag data from the VTU */
	err = mv88e6xxx_g1_vtu_getnext(chip, entry);
	if (err)
		return err;

	if (entry->valid) {
		/* Fetch (and mask) VLAN PortState data from the STU */
		err = mv88e6xxx_g1_vtu_stu_get(chip, entry);
		if (err)
			return err;

		err = mv88e6185_g1_vtu_data_read(chip, entry);
		if (err)
			return err;

		err = mv88e6xxx_g1_vtu_fid_read(chip, entry);
		if (err)
			return err;
	}

	return 0;
}