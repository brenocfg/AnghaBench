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
struct mv88e6xxx_chip {TYPE_1__* info; } ;
struct dsa_switch {struct mv88e6xxx_chip* priv; } ;
struct TYPE_2__ {int num_internal_phys; } ;

/* Variables and functions */

__attribute__((used)) static int mv88e6xxx_phy_is_internal(struct dsa_switch *ds, int port)
{
	struct mv88e6xxx_chip *chip = ds->priv;

	return port < chip->info->num_internal_phys;
}