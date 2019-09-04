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
struct mv88e6xxx_chip {int /*<<< orphan*/  reg_lock; } ;
struct dsa_switch {int /*<<< orphan*/  dev; struct mv88e6xxx_chip* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int mv88e6xxx_g1_atu_remove (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void mv88e6xxx_port_fast_age(struct dsa_switch *ds, int port)
{
	struct mv88e6xxx_chip *chip = ds->priv;
	int err;

	mutex_lock(&chip->reg_lock);
	err = mv88e6xxx_g1_atu_remove(chip, 0, port, false);
	mutex_unlock(&chip->reg_lock);

	if (err)
		dev_err(ds->dev, "p%d: failed to flush ATU\n", port);
}