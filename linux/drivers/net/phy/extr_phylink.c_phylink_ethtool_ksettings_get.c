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
struct phylink_link_state {int dummy; } ;
struct phylink {int link_an_mode; scalar_t__ phydev; int /*<<< orphan*/  supported; int /*<<< orphan*/  link_port; } ;
struct TYPE_4__ {int /*<<< orphan*/  supported; } ;
struct TYPE_3__ {int /*<<< orphan*/  port; } ;
struct ethtool_link_ksettings {TYPE_2__ link_modes; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
#define  MLO_AN_FIXED 129 
#define  MLO_AN_INBAND 128 
 int /*<<< orphan*/  linkmode_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_ethtool_ksettings_get (scalar_t__,struct ethtool_link_ksettings*) ; 
 int /*<<< orphan*/  phylink_get_fixed_state (struct phylink*,struct phylink_link_state*) ; 
 int /*<<< orphan*/  phylink_get_ksettings (struct phylink_link_state*,struct ethtool_link_ksettings*) ; 
 int /*<<< orphan*/  phylink_get_mac_state (struct phylink*,struct phylink_link_state*) ; 

int phylink_ethtool_ksettings_get(struct phylink *pl,
				  struct ethtool_link_ksettings *kset)
{
	struct phylink_link_state link_state;

	ASSERT_RTNL();

	if (pl->phydev) {
		phy_ethtool_ksettings_get(pl->phydev, kset);
	} else {
		kset->base.port = pl->link_port;
	}

	linkmode_copy(kset->link_modes.supported, pl->supported);

	switch (pl->link_an_mode) {
	case MLO_AN_FIXED:
		/* We are using fixed settings. Report these as the
		 * current link settings - and note that these also
		 * represent the supported speeds/duplex/pause modes.
		 */
		phylink_get_fixed_state(pl, &link_state);
		phylink_get_ksettings(&link_state, kset);
		break;

	case MLO_AN_INBAND:
		/* If there is a phy attached, then use the reported
		 * settings from the phy with no modification.
		 */
		if (pl->phydev)
			break;

		phylink_get_mac_state(pl, &link_state);

		/* The MAC is reporting the link results from its own PCS
		 * layer via in-band status. Report these as the current
		 * link settings.
		 */
		phylink_get_ksettings(&link_state, kset);
		break;
	}

	return 0;
}