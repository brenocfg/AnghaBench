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
typedef  int /*<<< orphan*/  uint64_t ;
struct mv88e6xxx_chip {int dummy; } ;
struct dsa_switch {struct mv88e6xxx_chip* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mv88e6xxx_get_stats (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_lock (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_unlock (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_stats_snapshot (struct mv88e6xxx_chip*,int) ; 

__attribute__((used)) static void mv88e6xxx_get_ethtool_stats(struct dsa_switch *ds, int port,
					uint64_t *data)
{
	struct mv88e6xxx_chip *chip = ds->priv;
	int ret;

	mv88e6xxx_reg_lock(chip);

	ret = mv88e6xxx_stats_snapshot(chip, port);
	mv88e6xxx_reg_unlock(chip);

	if (ret < 0)
		return;

	mv88e6xxx_get_stats(chip, port, data);

}