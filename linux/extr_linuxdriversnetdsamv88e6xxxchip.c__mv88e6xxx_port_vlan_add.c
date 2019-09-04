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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct mv88e6xxx_vtu_entry {int /*<<< orphan*/ * member; } ;
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int mv88e6xxx_broadcast_setup (struct mv88e6xxx_chip*,int /*<<< orphan*/ ) ; 
 int mv88e6xxx_vtu_get (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,struct mv88e6xxx_vtu_entry*,int) ; 
 int mv88e6xxx_vtu_loadpurge (struct mv88e6xxx_chip*,struct mv88e6xxx_vtu_entry*) ; 

__attribute__((used)) static int _mv88e6xxx_port_vlan_add(struct mv88e6xxx_chip *chip, int port,
				    u16 vid, u8 member)
{
	struct mv88e6xxx_vtu_entry vlan;
	int err;

	err = mv88e6xxx_vtu_get(chip, vid, &vlan, true);
	if (err)
		return err;

	vlan.member[port] = member;

	err = mv88e6xxx_vtu_loadpurge(chip, &vlan);
	if (err)
		return err;

	return mv88e6xxx_broadcast_setup(chip, vid);
}