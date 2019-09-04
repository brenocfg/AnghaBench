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
struct sun8i_hdmi_phy {TYPE_1__* variant; int /*<<< orphan*/  regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* phy_init ) (struct sun8i_hdmi_phy*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SUN8I_HDMI_PHY_READ_EN_MAGIC ; 
 int /*<<< orphan*/  SUN8I_HDMI_PHY_READ_EN_REG ; 
 int /*<<< orphan*/  SUN8I_HDMI_PHY_UNSCRAMBLE_MAGIC ; 
 int /*<<< orphan*/  SUN8I_HDMI_PHY_UNSCRAMBLE_REG ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sun8i_hdmi_phy*) ; 

void sun8i_hdmi_phy_init(struct sun8i_hdmi_phy *phy)
{
	/* enable read access to HDMI controller */
	regmap_write(phy->regs, SUN8I_HDMI_PHY_READ_EN_REG,
		     SUN8I_HDMI_PHY_READ_EN_MAGIC);

	/* unscramble register offsets */
	regmap_write(phy->regs, SUN8I_HDMI_PHY_UNSCRAMBLE_REG,
		     SUN8I_HDMI_PHY_UNSCRAMBLE_MAGIC);

	phy->variant->phy_init(phy);
}