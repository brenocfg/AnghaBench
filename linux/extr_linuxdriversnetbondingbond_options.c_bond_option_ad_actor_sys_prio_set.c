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
struct TYPE_2__ {int /*<<< orphan*/  ad_actor_sys_prio; } ;
struct bonding {TYPE_1__ params; int /*<<< orphan*/  dev; } ;
struct bond_opt_value {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  bond_3ad_update_ad_actor_settings (struct bonding*) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bond_option_ad_actor_sys_prio_set(struct bonding *bond,
					     const struct bond_opt_value *newval)
{
	netdev_dbg(bond->dev, "Setting ad_actor_sys_prio to %llu\n",
		   newval->value);

	bond->params.ad_actor_sys_prio = newval->value;
	bond_3ad_update_ad_actor_settings(bond);

	return 0;
}