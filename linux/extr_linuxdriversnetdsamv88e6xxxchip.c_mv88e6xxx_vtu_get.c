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
typedef  scalar_t__ u16 ;
struct mv88e6xxx_vtu_entry {scalar_t__ vid; int valid; int /*<<< orphan*/  fid; int /*<<< orphan*/ * member; } ;
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MV88E6XXX_G1_VTU_DATA_MEMBER_TAG_NON_MEMBER ; 
 int /*<<< orphan*/  memset (struct mv88e6xxx_vtu_entry*,int /*<<< orphan*/ ,int) ; 
 int mv88e6xxx_atu_new (struct mv88e6xxx_chip*,int /*<<< orphan*/ *) ; 
 int mv88e6xxx_num_ports (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_vtu_getnext (struct mv88e6xxx_chip*,struct mv88e6xxx_vtu_entry*) ; 

__attribute__((used)) static int mv88e6xxx_vtu_get(struct mv88e6xxx_chip *chip, u16 vid,
			     struct mv88e6xxx_vtu_entry *entry, bool new)
{
	int err;

	if (!vid)
		return -EINVAL;

	entry->vid = vid - 1;
	entry->valid = false;

	err = mv88e6xxx_vtu_getnext(chip, entry);
	if (err)
		return err;

	if (entry->vid == vid && entry->valid)
		return 0;

	if (new) {
		int i;

		/* Initialize a fresh VLAN entry */
		memset(entry, 0, sizeof(*entry));
		entry->valid = true;
		entry->vid = vid;

		/* Exclude all ports */
		for (i = 0; i < mv88e6xxx_num_ports(chip); ++i)
			entry->member[i] =
				MV88E6XXX_G1_VTU_DATA_MEMBER_TAG_NON_MEMBER;

		return mv88e6xxx_atu_new(chip, &entry->fid);
	}

	/* switchdev expects -EOPNOTSUPP to honor software VLANs */
	return -EOPNOTSUPP;
}