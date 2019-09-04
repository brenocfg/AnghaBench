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
 int /*<<< orphan*/  mv88e6xxx_has_pvt (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_pvt_map (struct mv88e6xxx_chip*,int,int) ; 

__attribute__((used)) static int mv88e6xxx_crosschip_bridge_join(struct dsa_switch *ds, int dev,
					   int port, struct net_device *br)
{
	struct mv88e6xxx_chip *chip = ds->priv;
	int err;

	if (!mv88e6xxx_has_pvt(chip))
		return 0;

	mutex_lock(&chip->reg_lock);
	err = mv88e6xxx_pvt_map(chip, dev, port);
	mutex_unlock(&chip->reg_lock);

	return err;
}