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
typedef  int u32 ;
struct phylink_link_state {scalar_t__ interface; int pause; scalar_t__ speed; scalar_t__ an_enabled; scalar_t__ duplex; int /*<<< orphan*/  advertising; } ;
struct phylink_config {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct mvneta_port {scalar_t__ phy_interface; scalar_t__ comphy; } ;

/* Variables and functions */
 int MLO_PAUSE_AN ; 
 int MLO_PAUSE_TXRX_MASK ; 
 int MVNETA_GMAC0_PORT_1000BASE_X ; 
 int MVNETA_GMAC2_INBAND_AN_ENABLE ; 
 int MVNETA_GMAC2_PCS_ENABLE ; 
 int MVNETA_GMAC2_PORT_RESET ; 
 int MVNETA_GMAC2_PORT_RGMII ; 
 int MVNETA_GMAC4_SHORT_PREAMBLE_ENABLE ; 
 int MVNETA_GMAC_1MS_CLOCK_ENABLE ; 
 int MVNETA_GMAC_ADVERT_SYM_FLOW_CTRL ; 
 int MVNETA_GMAC_AN_DUPLEX_EN ; 
 int MVNETA_GMAC_AN_FLOW_CTRL_EN ; 
 int MVNETA_GMAC_AN_SPEED_EN ; 
 int /*<<< orphan*/  MVNETA_GMAC_AUTONEG_CONFIG ; 
 int /*<<< orphan*/  MVNETA_GMAC_CLOCK_DIVIDER ; 
 int MVNETA_GMAC_CONFIG_FLOW_CTRL ; 
 int MVNETA_GMAC_CONFIG_FULL_DUPLEX ; 
 int MVNETA_GMAC_CONFIG_GMII_SPEED ; 
 int MVNETA_GMAC_CONFIG_MII_SPEED ; 
 int /*<<< orphan*/  MVNETA_GMAC_CTRL_0 ; 
 int /*<<< orphan*/  MVNETA_GMAC_CTRL_2 ; 
 int /*<<< orphan*/  MVNETA_GMAC_CTRL_4 ; 
 int MVNETA_GMAC_FORCE_LINK_DOWN ; 
 int MVNETA_GMAC_FORCE_LINK_PASS ; 
 int MVNETA_GMAC_INBAND_AN_ENABLE ; 
 int MVNETA_GMAC_INBAND_RESTART_AN ; 
 scalar_t__ PHY_INTERFACE_MODE_1000BASEX ; 
 scalar_t__ PHY_INTERFACE_MODE_2500BASEX ; 
 scalar_t__ PHY_INTERFACE_MODE_QSGMII ; 
 scalar_t__ PHY_INTERFACE_MODE_SGMII ; 
 int /*<<< orphan*/  Pause ; 
 scalar_t__ SPEED_100 ; 
 scalar_t__ SPEED_1000 ; 
 scalar_t__ SPEED_2500 ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvneta_comphy_init (struct mvneta_port*) ; 
 int mvreg_read (struct mvneta_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvreg_write (struct mvneta_port*,int /*<<< orphan*/ ,int) ; 
 struct mvneta_port* netdev_priv (struct net_device*) ; 
 scalar_t__ phy_interface_mode_is_8023z (scalar_t__) ; 
 int /*<<< orphan*/  phy_power_off (scalar_t__) ; 
 int /*<<< orphan*/  phylink_autoneg_inband (unsigned int) ; 
 scalar_t__ phylink_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_device* to_net_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvneta_mac_config(struct phylink_config *config, unsigned int mode,
			      const struct phylink_link_state *state)
{
	struct net_device *ndev = to_net_dev(config->dev);
	struct mvneta_port *pp = netdev_priv(ndev);
	u32 new_ctrl0, gmac_ctrl0 = mvreg_read(pp, MVNETA_GMAC_CTRL_0);
	u32 new_ctrl2, gmac_ctrl2 = mvreg_read(pp, MVNETA_GMAC_CTRL_2);
	u32 new_ctrl4, gmac_ctrl4 = mvreg_read(pp, MVNETA_GMAC_CTRL_4);
	u32 new_clk, gmac_clk = mvreg_read(pp, MVNETA_GMAC_CLOCK_DIVIDER);
	u32 new_an, gmac_an = mvreg_read(pp, MVNETA_GMAC_AUTONEG_CONFIG);

	new_ctrl0 = gmac_ctrl0 & ~MVNETA_GMAC0_PORT_1000BASE_X;
	new_ctrl2 = gmac_ctrl2 & ~(MVNETA_GMAC2_INBAND_AN_ENABLE |
				   MVNETA_GMAC2_PORT_RESET);
	new_ctrl4 = gmac_ctrl4 & ~(MVNETA_GMAC4_SHORT_PREAMBLE_ENABLE);
	new_clk = gmac_clk & ~MVNETA_GMAC_1MS_CLOCK_ENABLE;
	new_an = gmac_an & ~(MVNETA_GMAC_INBAND_AN_ENABLE |
			     MVNETA_GMAC_INBAND_RESTART_AN |
			     MVNETA_GMAC_CONFIG_MII_SPEED |
			     MVNETA_GMAC_CONFIG_GMII_SPEED |
			     MVNETA_GMAC_AN_SPEED_EN |
			     MVNETA_GMAC_ADVERT_SYM_FLOW_CTRL |
			     MVNETA_GMAC_CONFIG_FLOW_CTRL |
			     MVNETA_GMAC_AN_FLOW_CTRL_EN |
			     MVNETA_GMAC_CONFIG_FULL_DUPLEX |
			     MVNETA_GMAC_AN_DUPLEX_EN);

	/* Even though it might look weird, when we're configured in
	 * SGMII or QSGMII mode, the RGMII bit needs to be set.
	 */
	new_ctrl2 |= MVNETA_GMAC2_PORT_RGMII;

	if (state->interface == PHY_INTERFACE_MODE_QSGMII ||
	    state->interface == PHY_INTERFACE_MODE_SGMII ||
	    phy_interface_mode_is_8023z(state->interface))
		new_ctrl2 |= MVNETA_GMAC2_PCS_ENABLE;

	if (phylink_test(state->advertising, Pause))
		new_an |= MVNETA_GMAC_ADVERT_SYM_FLOW_CTRL;
	if (state->pause & MLO_PAUSE_TXRX_MASK)
		new_an |= MVNETA_GMAC_CONFIG_FLOW_CTRL;

	if (!phylink_autoneg_inband(mode)) {
		/* Phy or fixed speed */
		if (state->duplex)
			new_an |= MVNETA_GMAC_CONFIG_FULL_DUPLEX;

		if (state->speed == SPEED_1000 || state->speed == SPEED_2500)
			new_an |= MVNETA_GMAC_CONFIG_GMII_SPEED;
		else if (state->speed == SPEED_100)
			new_an |= MVNETA_GMAC_CONFIG_MII_SPEED;
	} else if (state->interface == PHY_INTERFACE_MODE_SGMII) {
		/* SGMII mode receives the state from the PHY */
		new_ctrl2 |= MVNETA_GMAC2_INBAND_AN_ENABLE;
		new_clk |= MVNETA_GMAC_1MS_CLOCK_ENABLE;
		new_an = (new_an & ~(MVNETA_GMAC_FORCE_LINK_DOWN |
				     MVNETA_GMAC_FORCE_LINK_PASS)) |
			 MVNETA_GMAC_INBAND_AN_ENABLE |
			 MVNETA_GMAC_AN_SPEED_EN |
			 MVNETA_GMAC_AN_DUPLEX_EN;
	} else {
		/* 802.3z negotiation - only 1000base-X */
		new_ctrl0 |= MVNETA_GMAC0_PORT_1000BASE_X;
		new_clk |= MVNETA_GMAC_1MS_CLOCK_ENABLE;
		new_an = (new_an & ~(MVNETA_GMAC_FORCE_LINK_DOWN |
				     MVNETA_GMAC_FORCE_LINK_PASS)) |
			 MVNETA_GMAC_INBAND_AN_ENABLE |
			 MVNETA_GMAC_CONFIG_GMII_SPEED |
			 /* The MAC only supports FD mode */
			 MVNETA_GMAC_CONFIG_FULL_DUPLEX;

		if (state->pause & MLO_PAUSE_AN && state->an_enabled)
			new_an |= MVNETA_GMAC_AN_FLOW_CTRL_EN;
	}

	/* Armada 370 documentation says we can only change the port mode
	 * and in-band enable when the link is down, so force it down
	 * while making these changes. We also do this for GMAC_CTRL2 */
	if ((new_ctrl0 ^ gmac_ctrl0) & MVNETA_GMAC0_PORT_1000BASE_X ||
	    (new_ctrl2 ^ gmac_ctrl2) & MVNETA_GMAC2_INBAND_AN_ENABLE ||
	    (new_an  ^ gmac_an) & MVNETA_GMAC_INBAND_AN_ENABLE) {
		mvreg_write(pp, MVNETA_GMAC_AUTONEG_CONFIG,
			    (gmac_an & ~MVNETA_GMAC_FORCE_LINK_PASS) |
			    MVNETA_GMAC_FORCE_LINK_DOWN);
	}


	/* When at 2.5G, the link partner can send frames with shortened
	 * preambles.
	 */
	if (state->speed == SPEED_2500)
		new_ctrl4 |= MVNETA_GMAC4_SHORT_PREAMBLE_ENABLE;

	if (pp->comphy && pp->phy_interface != state->interface &&
	    (state->interface == PHY_INTERFACE_MODE_SGMII ||
	     state->interface == PHY_INTERFACE_MODE_1000BASEX ||
	     state->interface == PHY_INTERFACE_MODE_2500BASEX)) {
		pp->phy_interface = state->interface;

		WARN_ON(phy_power_off(pp->comphy));
		WARN_ON(mvneta_comphy_init(pp));
	}

	if (new_ctrl0 != gmac_ctrl0)
		mvreg_write(pp, MVNETA_GMAC_CTRL_0, new_ctrl0);
	if (new_ctrl2 != gmac_ctrl2)
		mvreg_write(pp, MVNETA_GMAC_CTRL_2, new_ctrl2);
	if (new_ctrl4 != gmac_ctrl4)
		mvreg_write(pp, MVNETA_GMAC_CTRL_4, new_ctrl4);
	if (new_clk != gmac_clk)
		mvreg_write(pp, MVNETA_GMAC_CLOCK_DIVIDER, new_clk);
	if (new_an != gmac_an)
		mvreg_write(pp, MVNETA_GMAC_AUTONEG_CONFIG, new_an);

	if (gmac_ctrl2 & MVNETA_GMAC2_PORT_RESET) {
		while ((mvreg_read(pp, MVNETA_GMAC_CTRL_2) &
			MVNETA_GMAC2_PORT_RESET) != 0)
			continue;
	}
}