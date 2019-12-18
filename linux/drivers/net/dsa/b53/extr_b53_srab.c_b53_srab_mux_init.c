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
typedef  int u32 ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct b53_srab_priv {int mux_config; struct b53_srab_port_priv* port_intrs; } ;
struct b53_srab_port_priv {scalar_t__ mode; } ;
struct b53_device {TYPE_1__* pdata; struct b53_srab_priv* priv; } ;
struct TYPE_2__ {scalar_t__ chip_id; } ;

/* Variables and functions */
 int B53_MUX_CONFIG_P5 ; 
 scalar_t__ BCM58XX_DEVICE_ID ; 
 scalar_t__ IS_ERR (int) ; 
#define  MUX_CONFIG_GMII 132 
#define  MUX_CONFIG_INTERNAL 131 
 int MUX_CONFIG_MASK ; 
#define  MUX_CONFIG_MII_LITE 130 
#define  MUX_CONFIG_RGMII 129 
#define  MUX_CONFIG_SGMII 128 
 scalar_t__ PHY_INTERFACE_MODE_GMII ; 
 scalar_t__ PHY_INTERFACE_MODE_INTERNAL ; 
 scalar_t__ PHY_INTERFACE_MODE_MII ; 
 scalar_t__ PHY_INTERFACE_MODE_NA ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII ; 
 scalar_t__ PHY_INTERFACE_MODE_SGMII ; 
 int b53_serdes_init (struct b53_device*,unsigned int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned int,int /*<<< orphan*/ ) ; 
 int devm_platform_ioremap_resource (struct platform_device*,int) ; 
 int /*<<< orphan*/  phy_modes (scalar_t__) ; 
 struct b53_device* platform_get_drvdata (struct platform_device*) ; 
 int readl (int) ; 

__attribute__((used)) static void b53_srab_mux_init(struct platform_device *pdev)
{
	struct b53_device *dev = platform_get_drvdata(pdev);
	struct b53_srab_priv *priv = dev->priv;
	struct b53_srab_port_priv *p;
	unsigned int port;
	u32 reg, off = 0;
	int ret;

	if (dev->pdata && dev->pdata->chip_id != BCM58XX_DEVICE_ID)
		return;

	priv->mux_config = devm_platform_ioremap_resource(pdev, 1);
	if (IS_ERR(priv->mux_config))
		return;

	/* Obtain the port mux configuration so we know which lanes
	 * actually map to SerDes lanes
	 */
	for (port = 5; port > 3; port--, off += 4) {
		p = &priv->port_intrs[port];

		reg = readl(priv->mux_config + B53_MUX_CONFIG_P5 + off);
		switch (reg & MUX_CONFIG_MASK) {
		case MUX_CONFIG_SGMII:
			p->mode = PHY_INTERFACE_MODE_SGMII;
			ret = b53_serdes_init(dev, port);
			if (ret)
				continue;
			break;
		case MUX_CONFIG_MII_LITE:
			p->mode = PHY_INTERFACE_MODE_MII;
			break;
		case MUX_CONFIG_GMII:
			p->mode = PHY_INTERFACE_MODE_GMII;
			break;
		case MUX_CONFIG_RGMII:
			p->mode = PHY_INTERFACE_MODE_RGMII;
			break;
		case MUX_CONFIG_INTERNAL:
			p->mode = PHY_INTERFACE_MODE_INTERNAL;
			break;
		default:
			p->mode = PHY_INTERFACE_MODE_NA;
			break;
		}

		if (p->mode != PHY_INTERFACE_MODE_NA)
			dev_info(&pdev->dev, "Port %d mode: %s\n",
				 port, phy_modes(p->mode));
	}
}