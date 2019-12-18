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
struct device {int /*<<< orphan*/  of_node; } ;
struct TYPE_2__ {struct device dev; } ;
struct phy_device {struct lan88xx_priv* priv; TYPE_1__ mdio; } ;
struct lan88xx_priv {void* chip_rev; void* chip_id; scalar_t__ wolopts; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int LAN78XX_FORCE_LED_OFF ; 
 int /*<<< orphan*/  LAN78XX_PHY_LED_MODE_SELECT ; 
 int /*<<< orphan*/  LAN88XX_MMD3_CHIP_ID ; 
 int /*<<< orphan*/  LAN88XX_MMD3_CHIP_REV ; 
 struct lan88xx_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int of_property_read_variable_u32_array (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ,int) ; 
 void* phy_read_mmd (struct phy_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lan88xx_probe(struct phy_device *phydev)
{
	struct device *dev = &phydev->mdio.dev;
	struct lan88xx_priv *priv;
	u32 led_modes[4];
	int len;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->wolopts = 0;

	len = of_property_read_variable_u32_array(dev->of_node,
						  "microchip,led-modes",
						  led_modes,
						  0,
						  ARRAY_SIZE(led_modes));
	if (len >= 0) {
		u32 reg = 0;
		int i;

		for (i = 0; i < len; i++) {
			if (led_modes[i] > 15)
				return -EINVAL;
			reg |= led_modes[i] << (i * 4);
		}
		for (; i < ARRAY_SIZE(led_modes); i++)
			reg |= LAN78XX_FORCE_LED_OFF << (i * 4);
		(void)phy_write(phydev, LAN78XX_PHY_LED_MODE_SELECT, reg);
	} else if (len == -EOVERFLOW) {
		return -EINVAL;
	}

	/* these values can be used to identify internal PHY */
	priv->chip_id = phy_read_mmd(phydev, 3, LAN88XX_MMD3_CHIP_ID);
	priv->chip_rev = phy_read_mmd(phydev, 3, LAN88XX_MMD3_CHIP_REV);

	phydev->priv = priv;

	return 0;
}