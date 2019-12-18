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
struct mv88e6xxx_chip {int dummy; } ;
struct dsa_switch {int /*<<< orphan*/  dev; struct mv88e6xxx_chip* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mv88e6xxx_bridge_map (struct mv88e6xxx_chip*,struct net_device*) ; 
 scalar_t__ mv88e6xxx_port_vlan_map (struct mv88e6xxx_chip*,int) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_lock (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_unlock (struct mv88e6xxx_chip*) ; 

__attribute__((used)) static void mv88e6xxx_port_bridge_leave(struct dsa_switch *ds, int port,
					struct net_device *br)
{
	struct mv88e6xxx_chip *chip = ds->priv;

	mv88e6xxx_reg_lock(chip);
	if (mv88e6xxx_bridge_map(chip, br) ||
	    mv88e6xxx_port_vlan_map(chip, port))
		dev_err(ds->dev, "failed to remap in-chip Port VLAN\n");
	mv88e6xxx_reg_unlock(chip);
}