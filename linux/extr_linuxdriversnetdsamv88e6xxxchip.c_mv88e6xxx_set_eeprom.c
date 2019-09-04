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
typedef  int /*<<< orphan*/  u8 ;
struct mv88e6xxx_chip {int /*<<< orphan*/  reg_lock; TYPE_1__* info; } ;
struct ethtool_eeprom {int magic; } ;
struct dsa_switch {struct mv88e6xxx_chip* priv; } ;
struct TYPE_4__ {int (* set_eeprom ) (struct mv88e6xxx_chip*,struct ethtool_eeprom*,int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {TYPE_2__* ops; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct mv88e6xxx_chip*,struct ethtool_eeprom*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mv88e6xxx_set_eeprom(struct dsa_switch *ds,
				struct ethtool_eeprom *eeprom, u8 *data)
{
	struct mv88e6xxx_chip *chip = ds->priv;
	int err;

	if (!chip->info->ops->set_eeprom)
		return -EOPNOTSUPP;

	if (eeprom->magic != 0xc3ec4951)
		return -EINVAL;

	mutex_lock(&chip->reg_lock);
	err = chip->info->ops->set_eeprom(chip, eeprom, data);
	mutex_unlock(&chip->reg_lock);

	return err;
}