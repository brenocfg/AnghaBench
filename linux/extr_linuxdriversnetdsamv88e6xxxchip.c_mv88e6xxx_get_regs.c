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
typedef  int /*<<< orphan*/  u16 ;
struct mv88e6xxx_chip {int /*<<< orphan*/  reg_lock; } ;
struct ethtool_regs {scalar_t__ version; } ;
struct dsa_switch {struct mv88e6xxx_chip* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int mv88e6xxx_port_read (struct mv88e6xxx_chip*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mv88e6xxx_get_regs(struct dsa_switch *ds, int port,
			       struct ethtool_regs *regs, void *_p)
{
	struct mv88e6xxx_chip *chip = ds->priv;
	int err;
	u16 reg;
	u16 *p = _p;
	int i;

	regs->version = 0;

	memset(p, 0xff, 32 * sizeof(u16));

	mutex_lock(&chip->reg_lock);

	for (i = 0; i < 32; i++) {

		err = mv88e6xxx_port_read(chip, port, i, &reg);
		if (!err)
			p[i] = reg;
	}

	mutex_unlock(&chip->reg_lock);
}