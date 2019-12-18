#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sunxi_priv_data {int /*<<< orphan*/  regmap_field; TYPE_1__* variant; } ;
struct stmmac_priv {TYPE_2__* plat; TYPE_3__* device; } ;
struct device_node {int dummy; } ;
struct TYPE_9__ {struct device_node* of_node; } ;
struct TYPE_8__ {int interface; int /*<<< orphan*/  phy_node; struct sunxi_priv_data* bsp_priv; } ;
struct TYPE_7__ {int default_syscon_value; int tx_delay_max; int rx_delay_max; scalar_t__ support_rmii; scalar_t__ soc_has_internal_phy; } ;

/* Variables and functions */
 int EINVAL ; 
 int H3_EPHY_ADDR_SHIFT ; 
 int H3_EPHY_CLK_SEL ; 
 int H3_EPHY_LED_POL ; 
 int H3_EPHY_SELECT ; 
#define  PHY_INTERFACE_MODE_MII 130 
#define  PHY_INTERFACE_MODE_RGMII 129 
#define  PHY_INTERFACE_MODE_RMII 128 
 int SYSCON_EPIT ; 
 int SYSCON_ERXDC_SHIFT ; 
 int SYSCON_ETCS_EXT_GMII ; 
 int SYSCON_ETCS_INT_GMII ; 
 int SYSCON_ETCS_MASK ; 
 int SYSCON_ETXDC_SHIFT ; 
 int SYSCON_RMII_EN ; 
 int /*<<< orphan*/  dev_dbg (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (TYPE_3__*,char*,int,int) ; 
 int of_mdio_parse_addr (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 
 int phy_modes (int) ; 
 int regmap_field_read (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_field_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sun8i_dwmac_set_syscon(struct stmmac_priv *priv)
{
	struct sunxi_priv_data *gmac = priv->plat->bsp_priv;
	struct device_node *node = priv->device->of_node;
	int ret;
	u32 reg, val;

	ret = regmap_field_read(gmac->regmap_field, &val);
	if (ret) {
		dev_err(priv->device, "Fail to read from regmap field.\n");
		return ret;
	}

	reg = gmac->variant->default_syscon_value;
	if (reg != val)
		dev_warn(priv->device,
			 "Current syscon value is not the default %x (expect %x)\n",
			 val, reg);

	if (gmac->variant->soc_has_internal_phy) {
		if (of_property_read_bool(node, "allwinner,leds-active-low"))
			reg |= H3_EPHY_LED_POL;
		else
			reg &= ~H3_EPHY_LED_POL;

		/* Force EPHY xtal frequency to 24MHz. */
		reg |= H3_EPHY_CLK_SEL;

		ret = of_mdio_parse_addr(priv->device, priv->plat->phy_node);
		if (ret < 0) {
			dev_err(priv->device, "Could not parse MDIO addr\n");
			return ret;
		}
		/* of_mdio_parse_addr returns a valid (0 ~ 31) PHY
		 * address. No need to mask it again.
		 */
		reg |= 1 << H3_EPHY_ADDR_SHIFT;
	} else {
		/* For SoCs without internal PHY the PHY selection bit should be
		 * set to 0 (external PHY).
		 */
		reg &= ~H3_EPHY_SELECT;
	}

	if (!of_property_read_u32(node, "allwinner,tx-delay-ps", &val)) {
		if (val % 100) {
			dev_err(priv->device, "tx-delay must be a multiple of 100\n");
			return -EINVAL;
		}
		val /= 100;
		dev_dbg(priv->device, "set tx-delay to %x\n", val);
		if (val <= gmac->variant->tx_delay_max) {
			reg &= ~(gmac->variant->tx_delay_max <<
				 SYSCON_ETXDC_SHIFT);
			reg |= (val << SYSCON_ETXDC_SHIFT);
		} else {
			dev_err(priv->device, "Invalid TX clock delay: %d\n",
				val);
			return -EINVAL;
		}
	}

	if (!of_property_read_u32(node, "allwinner,rx-delay-ps", &val)) {
		if (val % 100) {
			dev_err(priv->device, "rx-delay must be a multiple of 100\n");
			return -EINVAL;
		}
		val /= 100;
		dev_dbg(priv->device, "set rx-delay to %x\n", val);
		if (val <= gmac->variant->rx_delay_max) {
			reg &= ~(gmac->variant->rx_delay_max <<
				 SYSCON_ERXDC_SHIFT);
			reg |= (val << SYSCON_ERXDC_SHIFT);
		} else {
			dev_err(priv->device, "Invalid RX clock delay: %d\n",
				val);
			return -EINVAL;
		}
	}

	/* Clear interface mode bits */
	reg &= ~(SYSCON_ETCS_MASK | SYSCON_EPIT);
	if (gmac->variant->support_rmii)
		reg &= ~SYSCON_RMII_EN;

	switch (priv->plat->interface) {
	case PHY_INTERFACE_MODE_MII:
		/* default */
		break;
	case PHY_INTERFACE_MODE_RGMII:
		reg |= SYSCON_EPIT | SYSCON_ETCS_INT_GMII;
		break;
	case PHY_INTERFACE_MODE_RMII:
		reg |= SYSCON_RMII_EN | SYSCON_ETCS_EXT_GMII;
		break;
	default:
		dev_err(priv->device, "Unsupported interface mode: %s",
			phy_modes(priv->plat->interface));
		return -EINVAL;
	}

	regmap_field_write(gmac->regmap_field, reg);

	return 0;
}