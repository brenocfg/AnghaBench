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
struct TYPE_2__ {int link; int /*<<< orphan*/  interface; int /*<<< orphan*/  pause; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct phylink {int /*<<< orphan*/  state_mutex; TYPE_1__ phy_state; } ;
struct phy_device {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  interface; scalar_t__ asym_pause; scalar_t__ pause; struct phylink* phylink; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLO_PAUSE_ASYM ; 
 int /*<<< orphan*/  MLO_PAUSE_NONE ; 
 int /*<<< orphan*/  MLO_PAUSE_SYM ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_duplex_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_modes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_speed_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phylink_dbg (struct phylink*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phylink_run_resolve (struct phylink*) ; 

__attribute__((used)) static void phylink_phy_change(struct phy_device *phydev, bool up,
			       bool do_carrier)
{
	struct phylink *pl = phydev->phylink;

	mutex_lock(&pl->state_mutex);
	pl->phy_state.speed = phydev->speed;
	pl->phy_state.duplex = phydev->duplex;
	pl->phy_state.pause = MLO_PAUSE_NONE;
	if (phydev->pause)
		pl->phy_state.pause |= MLO_PAUSE_SYM;
	if (phydev->asym_pause)
		pl->phy_state.pause |= MLO_PAUSE_ASYM;
	pl->phy_state.interface = phydev->interface;
	pl->phy_state.link = up;
	mutex_unlock(&pl->state_mutex);

	phylink_run_resolve(pl);

	phylink_dbg(pl, "phy link %s %s/%s/%s\n", up ? "up" : "down",
		    phy_modes(phydev->interface),
		    phy_speed_to_str(phydev->speed),
		    phy_duplex_to_str(phydev->duplex));
}