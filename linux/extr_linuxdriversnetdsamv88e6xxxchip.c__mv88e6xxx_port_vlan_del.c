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
struct mv88e6xxx_vtu_entry {scalar_t__* member; int valid; int /*<<< orphan*/  fid; } ;
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ MV88E6XXX_G1_VTU_DATA_MEMBER_TAG_NON_MEMBER ; 
 int mv88e6xxx_g1_atu_remove (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int,int) ; 
 int mv88e6xxx_num_ports (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_vtu_get (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,struct mv88e6xxx_vtu_entry*,int) ; 
 int mv88e6xxx_vtu_loadpurge (struct mv88e6xxx_chip*,struct mv88e6xxx_vtu_entry*) ; 

__attribute__((used)) static int _mv88e6xxx_port_vlan_del(struct mv88e6xxx_chip *chip,
				    int port, u16 vid)
{
	struct mv88e6xxx_vtu_entry vlan;
	int i, err;

	err = mv88e6xxx_vtu_get(chip, vid, &vlan, false);
	if (err)
		return err;

	/* Tell switchdev if this VLAN is handled in software */
	if (vlan.member[port] == MV88E6XXX_G1_VTU_DATA_MEMBER_TAG_NON_MEMBER)
		return -EOPNOTSUPP;

	vlan.member[port] = MV88E6XXX_G1_VTU_DATA_MEMBER_TAG_NON_MEMBER;

	/* keep the VLAN unless all ports are excluded */
	vlan.valid = false;
	for (i = 0; i < mv88e6xxx_num_ports(chip); ++i) {
		if (vlan.member[i] !=
		    MV88E6XXX_G1_VTU_DATA_MEMBER_TAG_NON_MEMBER) {
			vlan.valid = true;
			break;
		}
	}

	err = mv88e6xxx_vtu_loadpurge(chip, &vlan);
	if (err)
		return err;

	return mv88e6xxx_g1_atu_remove(chip, vlan.fid, port, false);
}