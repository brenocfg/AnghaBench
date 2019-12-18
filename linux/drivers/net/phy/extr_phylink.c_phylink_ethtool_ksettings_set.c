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
struct phylink_link_state {scalar_t__ duplex; int an_enabled; scalar_t__ speed; int /*<<< orphan*/  interface; int /*<<< orphan*/  advertising; } ;
struct phylink {scalar_t__ link_an_mode; int /*<<< orphan*/  state_mutex; struct phylink_link_state link_config; int /*<<< orphan*/  phylink_disable_state; scalar_t__ phydev; int /*<<< orphan*/  supported; } ;
struct phy_setting {scalar_t__ duplex; scalar_t__ speed; } ;
struct TYPE_4__ {scalar_t__ autoneg; scalar_t__ duplex; scalar_t__ speed; } ;
struct TYPE_3__ {int /*<<< orphan*/  advertising; } ;
struct ethtool_link_ksettings {TYPE_2__ base; TYPE_1__ link_modes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 scalar_t__ AUTONEG_DISABLE ; 
 scalar_t__ AUTONEG_ENABLE ; 
 scalar_t__ DUPLEX_UNKNOWN ; 
 int EINVAL ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_Autoneg_BIT ; 
 scalar_t__ MLO_AN_FIXED ; 
 int /*<<< orphan*/  PHYLINK_DISABLE_STOPPED ; 
 scalar_t__ SPEED_UNKNOWN ; 
 int /*<<< orphan*/  __ETHTOOL_DECLARE_LINK_MODE_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linkmode_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linkmode_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int phy_ethtool_ksettings_set (scalar_t__,struct ethtool_link_ksettings*) ; 
 struct phy_setting* phy_lookup_setting (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ phylink_is_empty_linkmode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phylink_mac_an_restart (struct phylink*) ; 
 int /*<<< orphan*/  phylink_mac_config (struct phylink*,struct phylink_link_state*) ; 
 scalar_t__ phylink_validate (struct phylink*,int /*<<< orphan*/ ,struct phylink_link_state*) ; 
 int /*<<< orphan*/  support ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int phylink_ethtool_ksettings_set(struct phylink *pl,
				  const struct ethtool_link_ksettings *kset)
{
	__ETHTOOL_DECLARE_LINK_MODE_MASK(support);
	struct ethtool_link_ksettings our_kset;
	struct phylink_link_state config;
	int ret;

	ASSERT_RTNL();

	if (kset->base.autoneg != AUTONEG_DISABLE &&
	    kset->base.autoneg != AUTONEG_ENABLE)
		return -EINVAL;

	linkmode_copy(support, pl->supported);
	config = pl->link_config;

	/* Mask out unsupported advertisements */
	linkmode_and(config.advertising, kset->link_modes.advertising,
		     support);

	/* FIXME: should we reject autoneg if phy/mac does not support it? */
	if (kset->base.autoneg == AUTONEG_DISABLE) {
		const struct phy_setting *s;

		/* Autonegotiation disabled, select a suitable speed and
		 * duplex.
		 */
		s = phy_lookup_setting(kset->base.speed, kset->base.duplex,
				       support, false);
		if (!s)
			return -EINVAL;

		/* If we have a fixed link (as specified by firmware), refuse
		 * to change link parameters.
		 */
		if (pl->link_an_mode == MLO_AN_FIXED &&
		    (s->speed != pl->link_config.speed ||
		     s->duplex != pl->link_config.duplex))
			return -EINVAL;

		config.speed = s->speed;
		config.duplex = s->duplex;
		config.an_enabled = false;

		__clear_bit(ETHTOOL_LINK_MODE_Autoneg_BIT, config.advertising);
	} else {
		/* If we have a fixed link, refuse to enable autonegotiation */
		if (pl->link_an_mode == MLO_AN_FIXED)
			return -EINVAL;

		config.speed = SPEED_UNKNOWN;
		config.duplex = DUPLEX_UNKNOWN;
		config.an_enabled = true;

		__set_bit(ETHTOOL_LINK_MODE_Autoneg_BIT, config.advertising);
	}

	if (phylink_validate(pl, support, &config))
		return -EINVAL;

	/* If autonegotiation is enabled, we must have an advertisement */
	if (config.an_enabled && phylink_is_empty_linkmode(config.advertising))
		return -EINVAL;

	our_kset = *kset;
	linkmode_copy(our_kset.link_modes.advertising, config.advertising);
	our_kset.base.speed = config.speed;
	our_kset.base.duplex = config.duplex;

	/* If we have a PHY, configure the phy */
	if (pl->phydev) {
		ret = phy_ethtool_ksettings_set(pl->phydev, &our_kset);
		if (ret)
			return ret;
	}

	mutex_lock(&pl->state_mutex);
	/* Configure the MAC to match the new settings */
	linkmode_copy(pl->link_config.advertising, our_kset.link_modes.advertising);
	pl->link_config.interface = config.interface;
	pl->link_config.speed = our_kset.base.speed;
	pl->link_config.duplex = our_kset.base.duplex;
	pl->link_config.an_enabled = our_kset.base.autoneg != AUTONEG_DISABLE;

	if (!test_bit(PHYLINK_DISABLE_STOPPED, &pl->phylink_disable_state)) {
		phylink_mac_config(pl, &pl->link_config);
		phylink_mac_an_restart(pl);
	}
	mutex_unlock(&pl->state_mutex);

	return 0;
}