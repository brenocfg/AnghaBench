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
struct net_device {int dummy; } ;
struct mv88e6xxx_chip {int /*<<< orphan*/  reg_lock; } ;
struct dsa_switch {struct mv88e6xxx_chip* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int mv88e6xxx_bridge_map (struct mv88e6xxx_chip*,struct net_device*) ; 

__attribute__((used)) static int mv88e6xxx_port_bridge_join(struct dsa_switch *ds, int port,
				      struct net_device *br)
{
	struct mv88e6xxx_chip *chip = ds->priv;
	int err;

	mutex_lock(&chip->reg_lock);
	err = mv88e6xxx_bridge_map(chip, br);
	mutex_unlock(&chip->reg_lock);

	return err;
}