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
struct switchdev_obj_port_mdb {int /*<<< orphan*/  vid; int /*<<< orphan*/  addr; } ;
struct mv88e6xxx_chip {int dummy; } ;
struct dsa_switch {int /*<<< orphan*/  dev; struct mv88e6xxx_chip* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E6XXX_G1_ATU_DATA_STATE_MC_STATIC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ mv88e6xxx_port_db_load_purge (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_lock (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_unlock (struct mv88e6xxx_chip*) ; 

__attribute__((used)) static void mv88e6xxx_port_mdb_add(struct dsa_switch *ds, int port,
				   const struct switchdev_obj_port_mdb *mdb)
{
	struct mv88e6xxx_chip *chip = ds->priv;

	mv88e6xxx_reg_lock(chip);
	if (mv88e6xxx_port_db_load_purge(chip, port, mdb->addr, mdb->vid,
					 MV88E6XXX_G1_ATU_DATA_STATE_MC_STATIC))
		dev_err(ds->dev, "p%d: failed to load multicast MAC address\n",
			port);
	mv88e6xxx_reg_unlock(chip);
}