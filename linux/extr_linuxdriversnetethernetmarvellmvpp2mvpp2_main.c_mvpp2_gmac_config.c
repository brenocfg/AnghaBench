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
struct phylink_link_state {scalar_t__ interface; int pause; scalar_t__ speed; int /*<<< orphan*/  advertising; scalar_t__ duplex; } ;
struct mvpp2_port {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  Asym_Pause ; 
 int MLO_PAUSE_RX ; 
 int MLO_PAUSE_TX ; 
 int MVPP22_CTRL4_DP_CLK_SEL ; 
 int MVPP22_CTRL4_EXT_PIN_GMII_SEL ; 
 int MVPP22_CTRL4_QSGMII_BYPASS_ACTIVE ; 
 int MVPP22_CTRL4_RX_FC_EN ; 
 int MVPP22_CTRL4_SYNC_BYPASS_DIS ; 
 int MVPP22_CTRL4_TX_FC_EN ; 
 scalar_t__ MVPP22_GMAC_CTRL_4_REG ; 
 int MVPP2_GMAC_AN_DUPLEX_EN ; 
 int MVPP2_GMAC_AN_SPEED_EN ; 
 scalar_t__ MVPP2_GMAC_AUTONEG_CONFIG ; 
 int MVPP2_GMAC_CONFIG_FULL_DUPLEX ; 
 int MVPP2_GMAC_CONFIG_GMII_SPEED ; 
 int MVPP2_GMAC_CONFIG_MII_SPEED ; 
 scalar_t__ MVPP2_GMAC_CTRL_0_REG ; 
 scalar_t__ MVPP2_GMAC_CTRL_2_REG ; 
 int MVPP2_GMAC_FC_ADV_ASM_EN ; 
 int MVPP2_GMAC_FC_ADV_EN ; 
 int MVPP2_GMAC_FLOW_CTRL_AUTONEG ; 
 int MVPP2_GMAC_FORCE_LINK_DOWN ; 
 int MVPP2_GMAC_FORCE_LINK_PASS ; 
 int MVPP2_GMAC_INBAND_AN_MASK ; 
 int MVPP2_GMAC_IN_BAND_AUTONEG ; 
 int MVPP2_GMAC_IN_BAND_AUTONEG_BYPASS ; 
 int MVPP2_GMAC_PCS_ENABLE_MASK ; 
 int MVPP2_GMAC_PORT_RESET_MASK ; 
 int MVPP2_GMAC_PORT_TYPE_MASK ; 
 scalar_t__ PHY_INTERFACE_MODE_1000BASEX ; 
 scalar_t__ PHY_INTERFACE_MODE_2500BASEX ; 
 scalar_t__ PHY_INTERFACE_MODE_SGMII ; 
 int /*<<< orphan*/  Pause ; 
 scalar_t__ SPEED_100 ; 
 scalar_t__ SPEED_1000 ; 
 scalar_t__ phy_interface_mode_is_rgmii (scalar_t__) ; 
 scalar_t__ phylink_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mvpp2_gmac_config(struct mvpp2_port *port, unsigned int mode,
			      const struct phylink_link_state *state)
{
	u32 an, ctrl0, ctrl2, ctrl4;
	u32 old_ctrl2;

	an = readl(port->base + MVPP2_GMAC_AUTONEG_CONFIG);
	ctrl0 = readl(port->base + MVPP2_GMAC_CTRL_0_REG);
	ctrl2 = readl(port->base + MVPP2_GMAC_CTRL_2_REG);
	ctrl4 = readl(port->base + MVPP22_GMAC_CTRL_4_REG);

	old_ctrl2 = ctrl2;

	/* Force link down */
	an &= ~MVPP2_GMAC_FORCE_LINK_PASS;
	an |= MVPP2_GMAC_FORCE_LINK_DOWN;
	writel(an, port->base + MVPP2_GMAC_AUTONEG_CONFIG);

	/* Set the GMAC in a reset state */
	ctrl2 |= MVPP2_GMAC_PORT_RESET_MASK;
	writel(ctrl2, port->base + MVPP2_GMAC_CTRL_2_REG);

	an &= ~(MVPP2_GMAC_CONFIG_MII_SPEED | MVPP2_GMAC_CONFIG_GMII_SPEED |
		MVPP2_GMAC_AN_SPEED_EN | MVPP2_GMAC_FC_ADV_EN |
		MVPP2_GMAC_FC_ADV_ASM_EN | MVPP2_GMAC_FLOW_CTRL_AUTONEG |
		MVPP2_GMAC_CONFIG_FULL_DUPLEX | MVPP2_GMAC_AN_DUPLEX_EN |
		MVPP2_GMAC_FORCE_LINK_DOWN);
	ctrl0 &= ~MVPP2_GMAC_PORT_TYPE_MASK;
	ctrl2 &= ~(MVPP2_GMAC_PORT_RESET_MASK | MVPP2_GMAC_PCS_ENABLE_MASK);

	if (state->interface == PHY_INTERFACE_MODE_1000BASEX ||
	    state->interface == PHY_INTERFACE_MODE_2500BASEX) {
		/* 1000BaseX and 2500BaseX ports cannot negotiate speed nor can
		 * they negotiate duplex: they are always operating with a fixed
		 * speed of 1000/2500Mbps in full duplex, so force 1000/2500
		 * speed and full duplex here.
		 */
		ctrl0 |= MVPP2_GMAC_PORT_TYPE_MASK;
		an |= MVPP2_GMAC_CONFIG_GMII_SPEED |
		      MVPP2_GMAC_CONFIG_FULL_DUPLEX;
	} else if (!phy_interface_mode_is_rgmii(state->interface)) {
		an |= MVPP2_GMAC_AN_SPEED_EN | MVPP2_GMAC_FLOW_CTRL_AUTONEG;
	}

	if (state->duplex)
		an |= MVPP2_GMAC_CONFIG_FULL_DUPLEX;
	if (phylink_test(state->advertising, Pause))
		an |= MVPP2_GMAC_FC_ADV_EN;
	if (phylink_test(state->advertising, Asym_Pause))
		an |= MVPP2_GMAC_FC_ADV_ASM_EN;

	if (state->interface == PHY_INTERFACE_MODE_SGMII ||
	    state->interface == PHY_INTERFACE_MODE_1000BASEX ||
	    state->interface == PHY_INTERFACE_MODE_2500BASEX) {
		an |= MVPP2_GMAC_IN_BAND_AUTONEG;
		ctrl2 |= MVPP2_GMAC_INBAND_AN_MASK | MVPP2_GMAC_PCS_ENABLE_MASK;

		ctrl4 &= ~(MVPP22_CTRL4_EXT_PIN_GMII_SEL |
			   MVPP22_CTRL4_RX_FC_EN | MVPP22_CTRL4_TX_FC_EN);
		ctrl4 |= MVPP22_CTRL4_SYNC_BYPASS_DIS |
			 MVPP22_CTRL4_DP_CLK_SEL |
			 MVPP22_CTRL4_QSGMII_BYPASS_ACTIVE;

		if (state->pause & MLO_PAUSE_TX)
			ctrl4 |= MVPP22_CTRL4_TX_FC_EN;
		if (state->pause & MLO_PAUSE_RX)
			ctrl4 |= MVPP22_CTRL4_RX_FC_EN;
	} else if (phy_interface_mode_is_rgmii(state->interface)) {
		an |= MVPP2_GMAC_IN_BAND_AUTONEG_BYPASS;

		if (state->speed == SPEED_1000)
			an |= MVPP2_GMAC_CONFIG_GMII_SPEED;
		else if (state->speed == SPEED_100)
			an |= MVPP2_GMAC_CONFIG_MII_SPEED;

		ctrl4 &= ~MVPP22_CTRL4_DP_CLK_SEL;
		ctrl4 |= MVPP22_CTRL4_EXT_PIN_GMII_SEL |
			 MVPP22_CTRL4_SYNC_BYPASS_DIS |
			 MVPP22_CTRL4_QSGMII_BYPASS_ACTIVE;
	}

	writel(ctrl0, port->base + MVPP2_GMAC_CTRL_0_REG);
	writel(ctrl2, port->base + MVPP2_GMAC_CTRL_2_REG);
	writel(ctrl4, port->base + MVPP22_GMAC_CTRL_4_REG);
	writel(an, port->base + MVPP2_GMAC_AUTONEG_CONFIG);

	if (old_ctrl2 & MVPP2_GMAC_PORT_RESET_MASK) {
		while (readl(port->base + MVPP2_GMAC_CTRL_2_REG) &
		       MVPP2_GMAC_PORT_RESET_MASK)
			continue;
	}
}