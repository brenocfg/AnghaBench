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
struct phylink_link_state {int pause; } ;
struct phylink {int link_an_mode; int /*<<< orphan*/  netdev; int /*<<< orphan*/  phylink_disable_state; int /*<<< orphan*/  supported; struct phylink_link_state link_config; } ;
struct ethtool_pauseparam {scalar_t__ rx_pause; scalar_t__ tx_pause; scalar_t__ autoneg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  Asym_Pause ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  MLO_AN_FIXED 130 
#define  MLO_AN_INBAND 129 
#define  MLO_AN_PHY 128 
 int MLO_PAUSE_AN ; 
 int MLO_PAUSE_RX ; 
 int MLO_PAUSE_TX ; 
 int MLO_PAUSE_TXRX_MASK ; 
 int /*<<< orphan*/  PHYLINK_DISABLE_STOPPED ; 
 int /*<<< orphan*/  Pause ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phylink_mac_an_restart (struct phylink*) ; 
 int /*<<< orphan*/  phylink_mac_config (struct phylink*,struct phylink_link_state*) ; 
 int /*<<< orphan*/  phylink_resolve_flow (struct phylink*,struct phylink_link_state*) ; 
 int /*<<< orphan*/  phylink_run_resolve (struct phylink*) ; 
 int /*<<< orphan*/  phylink_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int phylink_ethtool_set_pauseparam(struct phylink *pl,
				   struct ethtool_pauseparam *pause)
{
	struct phylink_link_state *config = &pl->link_config;

	ASSERT_RTNL();

	if (!phylink_test(pl->supported, Pause) &&
	    !phylink_test(pl->supported, Asym_Pause))
		return -EOPNOTSUPP;

	if (!phylink_test(pl->supported, Asym_Pause) &&
	    !pause->autoneg && pause->rx_pause != pause->tx_pause)
		return -EINVAL;

	config->pause &= ~(MLO_PAUSE_AN | MLO_PAUSE_TXRX_MASK);

	if (pause->autoneg)
		config->pause |= MLO_PAUSE_AN;
	if (pause->rx_pause)
		config->pause |= MLO_PAUSE_RX;
	if (pause->tx_pause)
		config->pause |= MLO_PAUSE_TX;

	if (!test_bit(PHYLINK_DISABLE_STOPPED, &pl->phylink_disable_state)) {
		switch (pl->link_an_mode) {
		case MLO_AN_PHY:
			/* Silently mark the carrier down, and then trigger a resolve */
			if (pl->netdev)
				netif_carrier_off(pl->netdev);
			phylink_run_resolve(pl);
			break;

		case MLO_AN_FIXED:
			/* Should we allow fixed links to change against the config? */
			phylink_resolve_flow(pl, config);
			phylink_mac_config(pl, config);
			break;

		case MLO_AN_INBAND:
			phylink_mac_config(pl, config);
			phylink_mac_an_restart(pl);
			break;
		}
	}

	return 0;
}