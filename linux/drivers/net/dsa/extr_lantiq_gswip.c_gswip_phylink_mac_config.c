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
typedef  int /*<<< orphan*/  u32 ;
struct phylink_link_state {int interface; } ;
struct gswip_priv {int dummy; } ;
struct dsa_switch {int /*<<< orphan*/  dev; struct gswip_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GSWIP_MII_CFG_LDCLKDIS ; 
 int /*<<< orphan*/  GSWIP_MII_CFG_MODE_MASK ; 
 int /*<<< orphan*/  GSWIP_MII_CFG_MODE_MIIM ; 
 int /*<<< orphan*/  GSWIP_MII_CFG_MODE_MIIP ; 
 int /*<<< orphan*/  GSWIP_MII_CFG_MODE_RGMII ; 
 int /*<<< orphan*/  GSWIP_MII_CFG_MODE_RMIIM ; 
 int GSWIP_MII_PCDU_RXDLY_MASK ; 
 int GSWIP_MII_PCDU_TXDLY_MASK ; 
#define  PHY_INTERFACE_MODE_INTERNAL 135 
#define  PHY_INTERFACE_MODE_MII 134 
#define  PHY_INTERFACE_MODE_REVMII 133 
#define  PHY_INTERFACE_MODE_RGMII 132 
#define  PHY_INTERFACE_MODE_RGMII_ID 131 
#define  PHY_INTERFACE_MODE_RGMII_RXID 130 
#define  PHY_INTERFACE_MODE_RGMII_TXID 129 
#define  PHY_INTERFACE_MODE_RMII 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gswip_mii_mask_cfg (struct gswip_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gswip_mii_mask_pcdu (struct gswip_priv*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gswip_phylink_mac_config(struct dsa_switch *ds, int port,
				     unsigned int mode,
				     const struct phylink_link_state *state)
{
	struct gswip_priv *priv = ds->priv;
	u32 miicfg = 0;

	miicfg |= GSWIP_MII_CFG_LDCLKDIS;

	switch (state->interface) {
	case PHY_INTERFACE_MODE_MII:
	case PHY_INTERFACE_MODE_INTERNAL:
		miicfg |= GSWIP_MII_CFG_MODE_MIIM;
		break;
	case PHY_INTERFACE_MODE_REVMII:
		miicfg |= GSWIP_MII_CFG_MODE_MIIP;
		break;
	case PHY_INTERFACE_MODE_RMII:
		miicfg |= GSWIP_MII_CFG_MODE_RMIIM;
		break;
	case PHY_INTERFACE_MODE_RGMII:
	case PHY_INTERFACE_MODE_RGMII_ID:
	case PHY_INTERFACE_MODE_RGMII_RXID:
	case PHY_INTERFACE_MODE_RGMII_TXID:
		miicfg |= GSWIP_MII_CFG_MODE_RGMII;
		break;
	default:
		dev_err(ds->dev,
			"Unsupported interface: %d\n", state->interface);
		return;
	}
	gswip_mii_mask_cfg(priv, GSWIP_MII_CFG_MODE_MASK, miicfg, port);

	switch (state->interface) {
	case PHY_INTERFACE_MODE_RGMII_ID:
		gswip_mii_mask_pcdu(priv, GSWIP_MII_PCDU_TXDLY_MASK |
					  GSWIP_MII_PCDU_RXDLY_MASK, 0, port);
		break;
	case PHY_INTERFACE_MODE_RGMII_RXID:
		gswip_mii_mask_pcdu(priv, GSWIP_MII_PCDU_RXDLY_MASK, 0, port);
		break;
	case PHY_INTERFACE_MODE_RGMII_TXID:
		gswip_mii_mask_pcdu(priv, GSWIP_MII_PCDU_TXDLY_MASK, 0, port);
		break;
	default:
		break;
	}
}