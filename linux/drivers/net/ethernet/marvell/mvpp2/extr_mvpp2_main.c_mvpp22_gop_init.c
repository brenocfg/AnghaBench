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
struct mvpp2_port {int phy_interface; int /*<<< orphan*/  dev; int /*<<< orphan*/  gop_id; struct mvpp2* priv; } ;
struct mvpp2 {int /*<<< orphan*/  sysctrl_base; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GENCONF_PORT_CTRL0 ; 
 int GENCONF_PORT_CTRL0_CLK_DIV_PHASE_CLR ; 
 int /*<<< orphan*/  GENCONF_PORT_CTRL1 ; 
 int GENCONF_PORT_CTRL1_EN (int /*<<< orphan*/ ) ; 
 int GENCONF_PORT_CTRL1_RESET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENCONF_SOFT_RESET1 ; 
 int GENCONF_SOFT_RESET1_GOP ; 
#define  PHY_INTERFACE_MODE_1000BASEX 135 
#define  PHY_INTERFACE_MODE_10GKR 134 
#define  PHY_INTERFACE_MODE_2500BASEX 133 
#define  PHY_INTERFACE_MODE_RGMII 132 
#define  PHY_INTERFACE_MODE_RGMII_ID 131 
#define  PHY_INTERFACE_MODE_RGMII_RXID 130 
#define  PHY_INTERFACE_MODE_RGMII_TXID 129 
#define  PHY_INTERFACE_MODE_SGMII 128 
 int /*<<< orphan*/  mvpp22_gop_init_10gkr (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp22_gop_init_rgmii (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp22_gop_init_sgmii (struct mvpp2_port*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mvpp22_gop_init(struct mvpp2_port *port)
{
	struct mvpp2 *priv = port->priv;
	u32 val;

	if (!priv->sysctrl_base)
		return 0;

	switch (port->phy_interface) {
	case PHY_INTERFACE_MODE_RGMII:
	case PHY_INTERFACE_MODE_RGMII_ID:
	case PHY_INTERFACE_MODE_RGMII_RXID:
	case PHY_INTERFACE_MODE_RGMII_TXID:
		if (port->gop_id == 0)
			goto invalid_conf;
		mvpp22_gop_init_rgmii(port);
		break;
	case PHY_INTERFACE_MODE_SGMII:
	case PHY_INTERFACE_MODE_1000BASEX:
	case PHY_INTERFACE_MODE_2500BASEX:
		mvpp22_gop_init_sgmii(port);
		break;
	case PHY_INTERFACE_MODE_10GKR:
		if (port->gop_id != 0)
			goto invalid_conf;
		mvpp22_gop_init_10gkr(port);
		break;
	default:
		goto unsupported_conf;
	}

	regmap_read(priv->sysctrl_base, GENCONF_PORT_CTRL1, &val);
	val |= GENCONF_PORT_CTRL1_RESET(port->gop_id) |
	       GENCONF_PORT_CTRL1_EN(port->gop_id);
	regmap_write(priv->sysctrl_base, GENCONF_PORT_CTRL1, val);

	regmap_read(priv->sysctrl_base, GENCONF_PORT_CTRL0, &val);
	val |= GENCONF_PORT_CTRL0_CLK_DIV_PHASE_CLR;
	regmap_write(priv->sysctrl_base, GENCONF_PORT_CTRL0, val);

	regmap_read(priv->sysctrl_base, GENCONF_SOFT_RESET1, &val);
	val |= GENCONF_SOFT_RESET1_GOP;
	regmap_write(priv->sysctrl_base, GENCONF_SOFT_RESET1, val);

unsupported_conf:
	return 0;

invalid_conf:
	netdev_err(port->dev, "Invalid port configuration\n");
	return -EINVAL;
}