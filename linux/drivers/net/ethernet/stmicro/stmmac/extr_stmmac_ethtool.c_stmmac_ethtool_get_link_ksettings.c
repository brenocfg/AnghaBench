#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  pcs_speed; int /*<<< orphan*/  pcs_duplex; int /*<<< orphan*/  pcs_link; } ;
struct stmmac_priv {int /*<<< orphan*/  phylink; int /*<<< orphan*/  ioaddr; TYPE_2__ xstats; TYPE_1__* hw; } ;
struct rgmii_adv {int pause; int lp_pause; scalar_t__ lp_duplex; scalar_t__ duplex; } ;
struct net_device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  lp_advertising; int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct TYPE_7__ {int autoneg; int /*<<< orphan*/  port; int /*<<< orphan*/  speed; int /*<<< orphan*/  duplex; } ;
struct ethtool_link_ksettings {TYPE_4__ link_modes; TYPE_3__ base; } ;
struct TYPE_5__ {int pcs; } ;

/* Variables and functions */
 int ADVERTISED_1000baseT_Full ; 
 int ADVERTISED_1000baseT_Half ; 
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_100baseT_Half ; 
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_10baseT_Half ; 
 int ADVERTISED_Asym_Pause ; 
 int ADVERTISED_Autoneg ; 
 int ADVERTISED_Pause ; 
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  PORT_OTHER ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 int STMMAC_PCS_ASYM_PAUSE ; 
 int STMMAC_PCS_PAUSE ; 
 int STMMAC_PCS_RGMII ; 
 int STMMAC_PCS_SGMII ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_1000baseT_Half ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_100baseT_Half ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 
 int SUPPORTED_Autoneg ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ethtool_convert_link_mode_to_legacy_u32 (int*,int /*<<< orphan*/ ) ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 int phylink_ethtool_ksettings_get (int /*<<< orphan*/ ,struct ethtool_link_ksettings*) ; 
 scalar_t__ stmmac_pcs_get_adv_lp (struct stmmac_priv*,int /*<<< orphan*/ ,struct rgmii_adv*) ; 

__attribute__((used)) static int stmmac_ethtool_get_link_ksettings(struct net_device *dev,
					     struct ethtool_link_ksettings *cmd)
{
	struct stmmac_priv *priv = netdev_priv(dev);

	if (priv->hw->pcs & STMMAC_PCS_RGMII ||
	    priv->hw->pcs & STMMAC_PCS_SGMII) {
		struct rgmii_adv adv;
		u32 supported, advertising, lp_advertising;

		if (!priv->xstats.pcs_link) {
			cmd->base.speed = SPEED_UNKNOWN;
			cmd->base.duplex = DUPLEX_UNKNOWN;
			return 0;
		}
		cmd->base.duplex = priv->xstats.pcs_duplex;

		cmd->base.speed = priv->xstats.pcs_speed;

		/* Get and convert ADV/LP_ADV from the HW AN registers */
		if (stmmac_pcs_get_adv_lp(priv, priv->ioaddr, &adv))
			return -EOPNOTSUPP;	/* should never happen indeed */

		/* Encoding of PSE bits is defined in 802.3z, 37.2.1.4 */

		ethtool_convert_link_mode_to_legacy_u32(
			&supported, cmd->link_modes.supported);
		ethtool_convert_link_mode_to_legacy_u32(
			&advertising, cmd->link_modes.advertising);
		ethtool_convert_link_mode_to_legacy_u32(
			&lp_advertising, cmd->link_modes.lp_advertising);

		if (adv.pause & STMMAC_PCS_PAUSE)
			advertising |= ADVERTISED_Pause;
		if (adv.pause & STMMAC_PCS_ASYM_PAUSE)
			advertising |= ADVERTISED_Asym_Pause;
		if (adv.lp_pause & STMMAC_PCS_PAUSE)
			lp_advertising |= ADVERTISED_Pause;
		if (adv.lp_pause & STMMAC_PCS_ASYM_PAUSE)
			lp_advertising |= ADVERTISED_Asym_Pause;

		/* Reg49[3] always set because ANE is always supported */
		cmd->base.autoneg = ADVERTISED_Autoneg;
		supported |= SUPPORTED_Autoneg;
		advertising |= ADVERTISED_Autoneg;
		lp_advertising |= ADVERTISED_Autoneg;

		if (adv.duplex) {
			supported |= (SUPPORTED_1000baseT_Full |
				      SUPPORTED_100baseT_Full |
				      SUPPORTED_10baseT_Full);
			advertising |= (ADVERTISED_1000baseT_Full |
					ADVERTISED_100baseT_Full |
					ADVERTISED_10baseT_Full);
		} else {
			supported |= (SUPPORTED_1000baseT_Half |
				      SUPPORTED_100baseT_Half |
				      SUPPORTED_10baseT_Half);
			advertising |= (ADVERTISED_1000baseT_Half |
					ADVERTISED_100baseT_Half |
					ADVERTISED_10baseT_Half);
		}
		if (adv.lp_duplex)
			lp_advertising |= (ADVERTISED_1000baseT_Full |
					   ADVERTISED_100baseT_Full |
					   ADVERTISED_10baseT_Full);
		else
			lp_advertising |= (ADVERTISED_1000baseT_Half |
					   ADVERTISED_100baseT_Half |
					   ADVERTISED_10baseT_Half);
		cmd->base.port = PORT_OTHER;

		ethtool_convert_legacy_u32_to_link_mode(
			cmd->link_modes.supported, supported);
		ethtool_convert_legacy_u32_to_link_mode(
			cmd->link_modes.advertising, advertising);
		ethtool_convert_legacy_u32_to_link_mode(
			cmd->link_modes.lp_advertising, lp_advertising);

		return 0;
	}

	return phylink_ethtool_ksettings_get(priv->phylink, cmd);
}