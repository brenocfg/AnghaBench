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
struct mv88e6xxx_chip {int /*<<< orphan*/  reg_lock; } ;
struct dsa_switch {struct mv88e6xxx_chip* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E6XXX_G1_ATU_DATA_STATE_UNUSED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int mv88e6xxx_port_db_load_purge (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv88e6xxx_port_mdb_del(struct dsa_switch *ds, int port,
				  const struct switchdev_obj_port_mdb *mdb)
{
	struct mv88e6xxx_chip *chip = ds->priv;
	int err;

	mutex_lock(&chip->reg_lock);
	err = mv88e6xxx_port_db_load_purge(chip, port, mdb->addr, mdb->vid,
					   MV88E6XXX_G1_ATU_DATA_STATE_UNUSED);
	mutex_unlock(&chip->reg_lock);

	return err;
}