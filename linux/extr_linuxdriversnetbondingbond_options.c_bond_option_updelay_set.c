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
struct TYPE_2__ {int miimon; int updelay; } ;
struct bonding {TYPE_1__ params; int /*<<< orphan*/  dev; } ;
struct bond_opt_value {int value; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,int,int,int) ; 

__attribute__((used)) static int bond_option_updelay_set(struct bonding *bond,
				   const struct bond_opt_value *newval)
{
	int value = newval->value;

	if (!bond->params.miimon) {
		netdev_err(bond->dev, "Unable to set up delay as MII monitoring is disabled\n");
		return -EPERM;
	}
	if ((value % bond->params.miimon) != 0) {
		netdev_warn(bond->dev, "up delay (%d) is not a multiple of miimon (%d), updelay rounded to %d ms\n",
			    value, bond->params.miimon,
			    (value / bond->params.miimon) *
			    bond->params.miimon);
	}
	bond->params.updelay = value / bond->params.miimon;
	netdev_dbg(bond->dev, "Setting up delay to %d\n",
		   bond->params.updelay * bond->params.miimon);

	return 0;
}