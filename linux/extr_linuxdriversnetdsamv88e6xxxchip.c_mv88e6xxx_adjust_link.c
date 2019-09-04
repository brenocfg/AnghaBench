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
struct phy_device {int /*<<< orphan*/  interface; int /*<<< orphan*/  pause; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  link; } ;
struct mv88e6xxx_chip {int /*<<< orphan*/  reg_lock; } ;
struct dsa_switch {int /*<<< orphan*/  dev; struct mv88e6xxx_chip* priv; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int mv88e6xxx_port_setup_mac (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_is_pseudo_fixed_link (struct phy_device*) ; 

__attribute__((used)) static void mv88e6xxx_adjust_link(struct dsa_switch *ds, int port,
				  struct phy_device *phydev)
{
	struct mv88e6xxx_chip *chip = ds->priv;
	int err;

	if (!phy_is_pseudo_fixed_link(phydev))
		return;

	mutex_lock(&chip->reg_lock);
	err = mv88e6xxx_port_setup_mac(chip, port, phydev->link, phydev->speed,
				       phydev->duplex, phydev->pause,
				       phydev->interface);
	mutex_unlock(&chip->reg_lock);

	if (err && err != -EOPNOTSUPP)
		dev_err(ds->dev, "p%d: failed to configure MAC\n", port);
}