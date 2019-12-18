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
struct phy_g12a_usb3_pcie_priv {scalar_t__ mode; int /*<<< orphan*/  regmap; int /*<<< orphan*/  reset; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PHY_R0 ; 
 int /*<<< orphan*/  PHY_R0_PCIE_POWER_STATE ; 
 scalar_t__ PHY_TYPE_USB3 ; 
 int phy_g12a_usb3_init (struct phy*) ; 
 struct phy_g12a_usb3_pcie_priv* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int reset_control_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int phy_g12a_usb3_pcie_init(struct phy *phy)
{
	struct phy_g12a_usb3_pcie_priv *priv = phy_get_drvdata(phy);
	int ret;

	ret = reset_control_reset(priv->reset);
	if (ret)
		return ret;

	if (priv->mode == PHY_TYPE_USB3)
		return phy_g12a_usb3_init(phy);

	/* Power UP PCIE */
	/* TODO figure out when the bootloader has set USB3 mode before */
	regmap_update_bits(priv->regmap, PHY_R0,
			   PHY_R0_PCIE_POWER_STATE,
			   FIELD_PREP(PHY_R0_PCIE_POWER_STATE, 0x1c));

	return 0;
}