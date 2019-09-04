#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct mv88e6xxx_vtu_entry {scalar_t__ vid; int /*<<< orphan*/  fid; int /*<<< orphan*/  valid; } ;
struct mv88e6xxx_chip {int /*<<< orphan*/  reg_lock; TYPE_1__* info; } ;
typedef  int /*<<< orphan*/  dsa_fdb_dump_cb_t ;
struct TYPE_2__ {scalar_t__ max_vid; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int mv88e6xxx_port_db_dump_fid (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *,void*) ; 
 int mv88e6xxx_port_get_fid (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ *) ; 
 int mv88e6xxx_vtu_getnext (struct mv88e6xxx_chip*,struct mv88e6xxx_vtu_entry*) ; 

__attribute__((used)) static int mv88e6xxx_port_db_dump(struct mv88e6xxx_chip *chip, int port,
				  dsa_fdb_dump_cb_t *cb, void *data)
{
	struct mv88e6xxx_vtu_entry vlan = {
		.vid = chip->info->max_vid,
	};
	u16 fid;
	int err;

	/* Dump port's default Filtering Information Database (VLAN ID 0) */
	mutex_lock(&chip->reg_lock);
	err = mv88e6xxx_port_get_fid(chip, port, &fid);
	mutex_unlock(&chip->reg_lock);

	if (err)
		return err;

	err = mv88e6xxx_port_db_dump_fid(chip, fid, 0, port, cb, data);
	if (err)
		return err;

	/* Dump VLANs' Filtering Information Databases */
	do {
		mutex_lock(&chip->reg_lock);
		err = mv88e6xxx_vtu_getnext(chip, &vlan);
		mutex_unlock(&chip->reg_lock);
		if (err)
			return err;

		if (!vlan.valid)
			break;

		err = mv88e6xxx_port_db_dump_fid(chip, vlan.fid, vlan.vid, port,
						 cb, data);
		if (err)
			return err;
	} while (vlan.vid < chip->info->max_vid);

	return err;
}