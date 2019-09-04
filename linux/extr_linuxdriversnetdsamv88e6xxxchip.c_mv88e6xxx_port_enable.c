#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct phy_device {int dummy; } ;
struct mv88e6xxx_chip {int /*<<< orphan*/  reg_lock; TYPE_2__* info; } ;
struct dsa_switch {struct mv88e6xxx_chip* priv; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* serdes_irq_setup ) (struct mv88e6xxx_chip*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int mv88e6xxx_serdes_power (struct mv88e6xxx_chip*,int,int) ; 
 int stub1 (struct mv88e6xxx_chip*,int) ; 

__attribute__((used)) static int mv88e6xxx_port_enable(struct dsa_switch *ds, int port,
				 struct phy_device *phydev)
{
	struct mv88e6xxx_chip *chip = ds->priv;
	int err;

	mutex_lock(&chip->reg_lock);

	err = mv88e6xxx_serdes_power(chip, port, true);

	if (!err && chip->info->ops->serdes_irq_setup)
		err = chip->info->ops->serdes_irq_setup(chip, port);

	mutex_unlock(&chip->reg_lock);

	return err;
}