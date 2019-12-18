#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tegra_xusb_usb2_port {int /*<<< orphan*/  supply; } ;
struct tegra_xusb_usb2_pad {int /*<<< orphan*/  lock; int /*<<< orphan*/  enable; } ;
struct tegra_xusb_usb2_lane {int hs_curr_level_offset; } ;
struct tegra_xusb_padctl {int dummy; } ;
struct tegra_xusb_lane {unsigned int index; TYPE_2__* pad; } ;
struct TYPE_3__ {int hs_squelch_level; int* hs_curr_level; int hs_term_range_adj; int hs_iref_cap; } ;
struct tegra124_xusb_padctl {TYPE_1__ fuse; } ;
struct phy {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {struct tegra_xusb_padctl* padctl; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  XUSB_PADCTL_USB2_BIAS_PAD_CTL0 ; 
 int XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_DISCON_LEVEL_MASK ; 
 int XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_DISCON_LEVEL_SHIFT ; 
 int XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_DISCON_LEVEL_VAL ; 
 int XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_SQUELCH_LEVEL_MASK ; 
 int XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_SQUELCH_LEVEL_SHIFT ; 
 int XUSB_PADCTL_USB2_BIAS_PAD_CTL0_PD ; 
 int /*<<< orphan*/  XUSB_PADCTL_USB2_OTG_PADX_CTL0 (unsigned int) ; 
 int /*<<< orphan*/  XUSB_PADCTL_USB2_OTG_PADX_CTL1 (unsigned int) ; 
 int XUSB_PADCTL_USB2_OTG_PAD_CTL0_HS_CURR_LEVEL_MASK ; 
 int XUSB_PADCTL_USB2_OTG_PAD_CTL0_HS_CURR_LEVEL_SHIFT ; 
 int XUSB_PADCTL_USB2_OTG_PAD_CTL0_HS_SLEW_MASK ; 
 int XUSB_PADCTL_USB2_OTG_PAD_CTL0_HS_SLEW_SHIFT ; 
 int XUSB_PADCTL_USB2_OTG_PAD_CTL0_HS_SLEW_VAL ; 
 int XUSB_PADCTL_USB2_OTG_PAD_CTL0_LS_RSLEW_MASK ; 
 int XUSB_PADCTL_USB2_OTG_PAD_CTL0_LS_RSLEW_SHIFT ; 
 int XUSB_PADCTL_USB2_OTG_PAD_CTL0_LS_RSLEW_VAL (unsigned int) ; 
 int XUSB_PADCTL_USB2_OTG_PAD_CTL0_PD ; 
 int XUSB_PADCTL_USB2_OTG_PAD_CTL0_PD2 ; 
 int XUSB_PADCTL_USB2_OTG_PAD_CTL0_PD_ZI ; 
 int XUSB_PADCTL_USB2_OTG_PAD_CTL1_HS_IREF_CAP_MASK ; 
 int XUSB_PADCTL_USB2_OTG_PAD_CTL1_HS_IREF_CAP_SHIFT ; 
 int XUSB_PADCTL_USB2_OTG_PAD_CTL1_PD_CHRP_FORCE_POWERUP ; 
 int XUSB_PADCTL_USB2_OTG_PAD_CTL1_PD_DISC_FORCE_POWERUP ; 
 int XUSB_PADCTL_USB2_OTG_PAD_CTL1_PD_DR ; 
 int XUSB_PADCTL_USB2_OTG_PAD_CTL1_TERM_RANGE_ADJ_MASK ; 
 int XUSB_PADCTL_USB2_OTG_PAD_CTL1_TERM_RANGE_ADJ_SHIFT ; 
 int /*<<< orphan*/  XUSB_PADCTL_USB2_PORT_CAP ; 
 int XUSB_PADCTL_USB2_PORT_CAP_HOST ; 
 int XUSB_PADCTL_USB2_PORT_CAP_PORTX_CAP_SHIFT (unsigned int) ; 
 int XUSB_PADCTL_USB2_PORT_CAP_PORT_CAP_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int padctl_readl (struct tegra_xusb_padctl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  padctl_writel (struct tegra_xusb_padctl*,int,int /*<<< orphan*/ ) ; 
 struct tegra_xusb_lane* phy_get_drvdata (struct phy*) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 struct tegra_xusb_usb2_port* tegra_xusb_find_usb2_port (struct tegra_xusb_padctl*,unsigned int) ; 
 struct tegra124_xusb_padctl* to_tegra124_xusb_padctl (struct tegra_xusb_padctl*) ; 
 struct tegra_xusb_usb2_lane* to_usb2_lane (struct tegra_xusb_lane*) ; 
 struct tegra_xusb_usb2_pad* to_usb2_pad (TYPE_2__*) ; 

__attribute__((used)) static int tegra124_usb2_phy_power_on(struct phy *phy)
{
	struct tegra_xusb_lane *lane = phy_get_drvdata(phy);
	struct tegra_xusb_usb2_lane *usb2 = to_usb2_lane(lane);
	struct tegra_xusb_usb2_pad *pad = to_usb2_pad(lane->pad);
	struct tegra_xusb_padctl *padctl = lane->pad->padctl;
	struct tegra124_xusb_padctl *priv;
	struct tegra_xusb_usb2_port *port;
	unsigned int index = lane->index;
	u32 value;
	int err;

	port = tegra_xusb_find_usb2_port(padctl, index);
	if (!port) {
		dev_err(&phy->dev, "no port found for USB2 lane %u\n", index);
		return -ENODEV;
	}

	priv = to_tegra124_xusb_padctl(padctl);

	value = padctl_readl(padctl, XUSB_PADCTL_USB2_BIAS_PAD_CTL0);
	value &= ~((XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_SQUELCH_LEVEL_MASK <<
		    XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_SQUELCH_LEVEL_SHIFT) |
		   (XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_DISCON_LEVEL_MASK <<
		    XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_DISCON_LEVEL_SHIFT));
	value |= (priv->fuse.hs_squelch_level <<
		  XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_SQUELCH_LEVEL_SHIFT) |
		 (XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_DISCON_LEVEL_VAL <<
		  XUSB_PADCTL_USB2_BIAS_PAD_CTL0_HS_DISCON_LEVEL_SHIFT);
	padctl_writel(padctl, value, XUSB_PADCTL_USB2_BIAS_PAD_CTL0);

	value = padctl_readl(padctl, XUSB_PADCTL_USB2_PORT_CAP);
	value &= ~(XUSB_PADCTL_USB2_PORT_CAP_PORT_CAP_MASK <<
		   XUSB_PADCTL_USB2_PORT_CAP_PORTX_CAP_SHIFT(index));
	value |= XUSB_PADCTL_USB2_PORT_CAP_HOST <<
		XUSB_PADCTL_USB2_PORT_CAP_PORTX_CAP_SHIFT(index);
	padctl_writel(padctl, value, XUSB_PADCTL_USB2_PORT_CAP);

	value = padctl_readl(padctl, XUSB_PADCTL_USB2_OTG_PADX_CTL0(index));
	value &= ~((XUSB_PADCTL_USB2_OTG_PAD_CTL0_HS_CURR_LEVEL_MASK <<
		    XUSB_PADCTL_USB2_OTG_PAD_CTL0_HS_CURR_LEVEL_SHIFT) |
		   (XUSB_PADCTL_USB2_OTG_PAD_CTL0_HS_SLEW_MASK <<
		    XUSB_PADCTL_USB2_OTG_PAD_CTL0_HS_SLEW_SHIFT) |
		   (XUSB_PADCTL_USB2_OTG_PAD_CTL0_LS_RSLEW_MASK <<
		    XUSB_PADCTL_USB2_OTG_PAD_CTL0_LS_RSLEW_SHIFT) |
		   XUSB_PADCTL_USB2_OTG_PAD_CTL0_PD |
		   XUSB_PADCTL_USB2_OTG_PAD_CTL0_PD2 |
		   XUSB_PADCTL_USB2_OTG_PAD_CTL0_PD_ZI);
	value |= (priv->fuse.hs_curr_level[index] +
		  usb2->hs_curr_level_offset) <<
		XUSB_PADCTL_USB2_OTG_PAD_CTL0_HS_CURR_LEVEL_SHIFT;
	value |= XUSB_PADCTL_USB2_OTG_PAD_CTL0_HS_SLEW_VAL <<
		XUSB_PADCTL_USB2_OTG_PAD_CTL0_HS_SLEW_SHIFT;
	value |= XUSB_PADCTL_USB2_OTG_PAD_CTL0_LS_RSLEW_VAL(index) <<
		XUSB_PADCTL_USB2_OTG_PAD_CTL0_LS_RSLEW_SHIFT;
	padctl_writel(padctl, value, XUSB_PADCTL_USB2_OTG_PADX_CTL0(index));

	value = padctl_readl(padctl, XUSB_PADCTL_USB2_OTG_PADX_CTL1(index));
	value &= ~((XUSB_PADCTL_USB2_OTG_PAD_CTL1_TERM_RANGE_ADJ_MASK <<
		    XUSB_PADCTL_USB2_OTG_PAD_CTL1_TERM_RANGE_ADJ_SHIFT) |
		   (XUSB_PADCTL_USB2_OTG_PAD_CTL1_HS_IREF_CAP_MASK <<
		    XUSB_PADCTL_USB2_OTG_PAD_CTL1_HS_IREF_CAP_SHIFT) |
		   XUSB_PADCTL_USB2_OTG_PAD_CTL1_PD_DR |
		   XUSB_PADCTL_USB2_OTG_PAD_CTL1_PD_CHRP_FORCE_POWERUP |
		   XUSB_PADCTL_USB2_OTG_PAD_CTL1_PD_DISC_FORCE_POWERUP);
	value |= (priv->fuse.hs_term_range_adj <<
		  XUSB_PADCTL_USB2_OTG_PAD_CTL1_TERM_RANGE_ADJ_SHIFT) |
		 (priv->fuse.hs_iref_cap <<
		  XUSB_PADCTL_USB2_OTG_PAD_CTL1_HS_IREF_CAP_SHIFT);
	padctl_writel(padctl, value, XUSB_PADCTL_USB2_OTG_PADX_CTL1(index));

	err = regulator_enable(port->supply);
	if (err)
		return err;

	mutex_lock(&pad->lock);

	if (pad->enable++ > 0)
		goto out;

	value = padctl_readl(padctl, XUSB_PADCTL_USB2_BIAS_PAD_CTL0);
	value &= ~XUSB_PADCTL_USB2_BIAS_PAD_CTL0_PD;
	padctl_writel(padctl, value, XUSB_PADCTL_USB2_BIAS_PAD_CTL0);

out:
	mutex_unlock(&pad->lock);
	return 0;
}