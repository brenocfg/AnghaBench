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
struct mv88e6xxx_chip {int /*<<< orphan*/  dev; } ;
struct dsa_switch {struct mv88e6xxx_chip* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_lock (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_unlock (struct mv88e6xxx_chip*) ; 
 scalar_t__ mv88e6xxx_serdes_power (struct mv88e6xxx_chip*,int,int) ; 

__attribute__((used)) static void mv88e6xxx_port_disable(struct dsa_switch *ds, int port)
{
	struct mv88e6xxx_chip *chip = ds->priv;

	mv88e6xxx_reg_lock(chip);
	if (mv88e6xxx_serdes_power(chip, port, false))
		dev_err(chip->dev, "failed to power off SERDES\n");
	mv88e6xxx_reg_unlock(chip);
}