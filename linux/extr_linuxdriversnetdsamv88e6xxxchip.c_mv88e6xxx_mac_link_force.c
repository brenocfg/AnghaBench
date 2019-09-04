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
struct mv88e6xxx_chip {int /*<<< orphan*/  dev; int /*<<< orphan*/  reg_lock; TYPE_2__* info; } ;
struct dsa_switch {struct mv88e6xxx_chip* priv; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* port_set_link ) (struct mv88e6xxx_chip*,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct mv88e6xxx_chip*,int,int) ; 

__attribute__((used)) static void mv88e6xxx_mac_link_force(struct dsa_switch *ds, int port, int link)
{
	struct mv88e6xxx_chip *chip = ds->priv;
	int err;

	mutex_lock(&chip->reg_lock);
	err = chip->info->ops->port_set_link(chip, port, link);
	mutex_unlock(&chip->reg_lock);

	if (err)
		dev_err(chip->dev, "p%d: failed to force MAC link\n", port);
}