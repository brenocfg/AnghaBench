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
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;
struct phy_device {struct ip101a_g_phy_priv* priv; TYPE_1__ mdio; } ;
struct ip101a_g_phy_priv {int /*<<< orphan*/  sel_intr32; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IP101GR_SEL_INTR32_INTR ; 
 int /*<<< orphan*/  IP101GR_SEL_INTR32_KEEP ; 
 int /*<<< orphan*/  IP101GR_SEL_INTR32_RXER ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ device_property_read_bool (struct device*,char*) ; 
 struct ip101a_g_phy_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip101a_g_probe(struct phy_device *phydev)
{
	struct device *dev = &phydev->mdio.dev;
	struct ip101a_g_phy_priv *priv;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	/* Both functions (RX error and interrupt status) are sharing the same
	 * pin on the 32-pin IP101GR, so this is an exclusive choice.
	 */
	if (device_property_read_bool(dev, "icplus,select-rx-error") &&
	    device_property_read_bool(dev, "icplus,select-interrupt")) {
		dev_err(dev,
			"RXER and INTR mode cannot be selected together\n");
		return -EINVAL;
	}

	if (device_property_read_bool(dev, "icplus,select-rx-error"))
		priv->sel_intr32 = IP101GR_SEL_INTR32_RXER;
	else if (device_property_read_bool(dev, "icplus,select-interrupt"))
		priv->sel_intr32 = IP101GR_SEL_INTR32_INTR;
	else
		priv->sel_intr32 = IP101GR_SEL_INTR32_KEEP;

	phydev->priv = priv;

	return 0;
}