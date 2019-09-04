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
struct slave {scalar_t__ link; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct TYPE_2__ {int primary_reselect; } ;
struct bonding {int force_primary; TYPE_1__ params; int /*<<< orphan*/  dev; int /*<<< orphan*/  curr_active_slave; int /*<<< orphan*/  primary_slave; } ;

/* Variables and functions */
 scalar_t__ BOND_LINK_UP ; 
#define  BOND_PRI_RESELECT_ALWAYS 130 
#define  BOND_PRI_RESELECT_BETTER 129 
#define  BOND_PRI_RESELECT_FAILURE 128 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct slave* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct slave *bond_choose_primary_or_current(struct bonding *bond)
{
	struct slave *prim = rtnl_dereference(bond->primary_slave);
	struct slave *curr = rtnl_dereference(bond->curr_active_slave);

	if (!prim || prim->link != BOND_LINK_UP) {
		if (!curr || curr->link != BOND_LINK_UP)
			return NULL;
		return curr;
	}

	if (bond->force_primary) {
		bond->force_primary = false;
		return prim;
	}

	if (!curr || curr->link != BOND_LINK_UP)
		return prim;

	/* At this point, prim and curr are both up */
	switch (bond->params.primary_reselect) {
	case BOND_PRI_RESELECT_ALWAYS:
		return prim;
	case BOND_PRI_RESELECT_BETTER:
		if (prim->speed < curr->speed)
			return curr;
		if (prim->speed == curr->speed && prim->duplex <= curr->duplex)
			return curr;
		return prim;
	case BOND_PRI_RESELECT_FAILURE:
		return curr;
	default:
		netdev_err(bond->dev, "impossible primary_reselect %d\n",
			   bond->params.primary_reselect);
		return curr;
	}
}