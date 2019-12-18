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
struct phylink {scalar_t__ link_irq; int /*<<< orphan*/  link_poll; scalar_t__ phydev; scalar_t__ sfp_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  PHYLINK_DISABLE_STOPPED ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct phylink*) ; 
 int /*<<< orphan*/  phy_stop (scalar_t__) ; 
 int /*<<< orphan*/  phylink_run_resolve_and_disable (struct phylink*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfp_upstream_stop (scalar_t__) ; 

void phylink_stop(struct phylink *pl)
{
	ASSERT_RTNL();

	if (pl->sfp_bus)
		sfp_upstream_stop(pl->sfp_bus);
	if (pl->phydev)
		phy_stop(pl->phydev);
	del_timer_sync(&pl->link_poll);
	if (pl->link_irq) {
		free_irq(pl->link_irq, pl);
		pl->link_irq = 0;
	}

	phylink_run_resolve_and_disable(pl, PHYLINK_DISABLE_STOPPED);
}