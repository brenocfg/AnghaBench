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
struct phy_device {int dummy; } ;
struct mv88e6xxx_chip {int dummy; } ;
struct dsa_switch {struct mv88e6xxx_chip* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mv88e6xxx_reg_lock (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_unlock (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_serdes_power (struct mv88e6xxx_chip*,int,int) ; 

__attribute__((used)) static int mv88e6xxx_port_enable(struct dsa_switch *ds, int port,
				 struct phy_device *phydev)
{
	struct mv88e6xxx_chip *chip = ds->priv;
	int err;

	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_serdes_power(chip, port, true);
	mv88e6xxx_reg_unlock(chip);

	return err;
}