#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct mv88e6xxx_chip {TYPE_1__* info; } ;
struct dsa_switch {struct mv88e6xxx_chip* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_vid; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MV88E6XXX_PORT_CTL2_8021Q_MODE_DISABLED ; 
 int /*<<< orphan*/  MV88E6XXX_PORT_CTL2_8021Q_MODE_SECURE ; 
 int mv88e6xxx_port_set_8021q_mode (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_lock (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_unlock (struct mv88e6xxx_chip*) ; 

__attribute__((used)) static int mv88e6xxx_port_vlan_filtering(struct dsa_switch *ds, int port,
					 bool vlan_filtering)
{
	struct mv88e6xxx_chip *chip = ds->priv;
	u16 mode = vlan_filtering ? MV88E6XXX_PORT_CTL2_8021Q_MODE_SECURE :
		MV88E6XXX_PORT_CTL2_8021Q_MODE_DISABLED;
	int err;

	if (!chip->info->max_vid)
		return -EOPNOTSUPP;

	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_port_set_8021q_mode(chip, port, mode);
	mv88e6xxx_reg_unlock(chip);

	return err;
}