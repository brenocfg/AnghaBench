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
struct phylink_link_state {int interface; int pause; int speed; scalar_t__ duplex; scalar_t__ link; } ;
struct dsa_switch {int dummy; } ;
struct bcm_sf2_priv {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ BCM7445_DEVICE_ID ; 
 int /*<<< orphan*/  CORE_IMP0_PRT_ID ; 
 int CORE_STS_OVERRIDE_GMIIP2_PORT (int) ; 
 int CORE_STS_OVERRIDE_GMIIP_PORT (int) ; 
 scalar_t__ DUPLEX_FULL ; 
 int DUPLX_MODE ; 
 int EXT_EPHY ; 
 int EXT_GPHY ; 
 int EXT_REVMII ; 
 int ID_MODE_DIS ; 
 int LINK_STS ; 
 int MLO_PAUSE_TX ; 
 int MLO_PAUSE_TXRX_MASK ; 
#define  PHY_INTERFACE_MODE_MII 133 
#define  PHY_INTERFACE_MODE_REVMII 132 
#define  PHY_INTERFACE_MODE_RGMII 131 
#define  PHY_INTERFACE_MODE_RGMII_TXID 130 
 int PORT_MODE_MASK ; 
 int PORT_MODE_SHIFT ; 
 int /*<<< orphan*/  REG_RGMII_CNTRL_P (int) ; 
 int RX_PAUSE_EN ; 
 int SPDSTS_100 ; 
 int SPDSTS_1000 ; 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 int SPEED_SHIFT ; 
 int SW_OVERRIDE ; 
 int TX_PAUSE_EN ; 
 struct bcm_sf2_priv* bcm_sf2_to_priv (struct dsa_switch*) ; 
 int core_readl (struct bcm_sf2_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core_writel (struct bcm_sf2_priv*,int,int) ; 
 int reg_readl (struct bcm_sf2_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_writel (struct bcm_sf2_priv*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm_sf2_sw_mac_config(struct dsa_switch *ds, int port,
				  unsigned int mode,
				  const struct phylink_link_state *state)
{
	struct bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	u32 id_mode_dis = 0, port_mode;
	u32 reg, offset;

	if (port == core_readl(priv, CORE_IMP0_PRT_ID))
		return;

	if (priv->type == BCM7445_DEVICE_ID)
		offset = CORE_STS_OVERRIDE_GMIIP_PORT(port);
	else
		offset = CORE_STS_OVERRIDE_GMIIP2_PORT(port);

	switch (state->interface) {
	case PHY_INTERFACE_MODE_RGMII:
		id_mode_dis = 1;
		/* fallthrough */
	case PHY_INTERFACE_MODE_RGMII_TXID:
		port_mode = EXT_GPHY;
		break;
	case PHY_INTERFACE_MODE_MII:
		port_mode = EXT_EPHY;
		break;
	case PHY_INTERFACE_MODE_REVMII:
		port_mode = EXT_REVMII;
		break;
	default:
		/* all other PHYs: internal and MoCA */
		goto force_link;
	}

	/* Clear id_mode_dis bit, and the existing port mode, let
	 * RGMII_MODE_EN bet set by mac_link_{up,down}
	 */
	reg = reg_readl(priv, REG_RGMII_CNTRL_P(port));
	reg &= ~ID_MODE_DIS;
	reg &= ~(PORT_MODE_MASK << PORT_MODE_SHIFT);
	reg &= ~(RX_PAUSE_EN | TX_PAUSE_EN);

	reg |= port_mode;
	if (id_mode_dis)
		reg |= ID_MODE_DIS;

	if (state->pause & MLO_PAUSE_TXRX_MASK) {
		if (state->pause & MLO_PAUSE_TX)
			reg |= TX_PAUSE_EN;
		reg |= RX_PAUSE_EN;
	}

	reg_writel(priv, reg, REG_RGMII_CNTRL_P(port));

force_link:
	/* Force link settings detected from the PHY */
	reg = SW_OVERRIDE;
	switch (state->speed) {
	case SPEED_1000:
		reg |= SPDSTS_1000 << SPEED_SHIFT;
		break;
	case SPEED_100:
		reg |= SPDSTS_100 << SPEED_SHIFT;
		break;
	}

	if (state->link)
		reg |= LINK_STS;
	if (state->duplex == DUPLEX_FULL)
		reg |= DUPLX_MODE;

	core_writel(priv, reg, offset);
}