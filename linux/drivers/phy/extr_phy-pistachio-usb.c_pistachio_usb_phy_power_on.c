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
struct pistachio_usb_phy {unsigned int refclk; int /*<<< orphan*/  phy_clk; int /*<<< orphan*/  dev; int /*<<< orphan*/  cr_top; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned long*) ; 
 int EINVAL ; 
 int EIO ; 
 int ETIMEDOUT ; 
 unsigned int REFCLK_XO_CRYSTAL ; 
 int /*<<< orphan*/  USB_PHY_CONTROL1 ; 
 unsigned int USB_PHY_CONTROL1_FSEL_MASK ; 
 unsigned int USB_PHY_CONTROL1_FSEL_SHIFT ; 
 int /*<<< orphan*/  USB_PHY_STATUS ; 
 unsigned int USB_PHY_STATUS_RX_PHY_CLK ; 
 unsigned int USB_PHY_STATUS_RX_UTMI_CLK ; 
 unsigned int USB_PHY_STATUS_VBUS_FAULT ; 
 int /*<<< orphan*/  USB_PHY_STRAP_CONTROL ; 
 unsigned int USB_PHY_STRAP_CONTROL_REFCLK_MASK ; 
 unsigned int USB_PHY_STRAP_CONTROL_REFCLK_SHIFT ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 unsigned long* fsel_rate_map ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 struct pistachio_usb_phy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int pistachio_usb_phy_power_on(struct phy *phy)
{
	struct pistachio_usb_phy *p_phy = phy_get_drvdata(phy);
	unsigned long timeout, rate;
	unsigned int i;
	int ret;

	ret = clk_prepare_enable(p_phy->phy_clk);
	if (ret < 0) {
		dev_err(p_phy->dev, "Failed to enable PHY clock: %d\n", ret);
		return ret;
	}

	regmap_update_bits(p_phy->cr_top, USB_PHY_STRAP_CONTROL,
			   USB_PHY_STRAP_CONTROL_REFCLK_MASK <<
			   USB_PHY_STRAP_CONTROL_REFCLK_SHIFT,
			   p_phy->refclk << USB_PHY_STRAP_CONTROL_REFCLK_SHIFT);

	rate = clk_get_rate(p_phy->phy_clk);
	if (p_phy->refclk == REFCLK_XO_CRYSTAL && rate != 12000000) {
		dev_err(p_phy->dev, "Unsupported rate for XO crystal: %ld\n",
			rate);
		ret = -EINVAL;
		goto disable_clk;
	}

	for (i = 0; i < ARRAY_SIZE(fsel_rate_map); i++) {
		if (rate == fsel_rate_map[i])
			break;
	}
	if (i == ARRAY_SIZE(fsel_rate_map)) {
		dev_err(p_phy->dev, "Unsupported clock rate: %lu\n", rate);
		ret = -EINVAL;
		goto disable_clk;
	}

	regmap_update_bits(p_phy->cr_top, USB_PHY_CONTROL1,
			   USB_PHY_CONTROL1_FSEL_MASK <<
			   USB_PHY_CONTROL1_FSEL_SHIFT,
			   i << USB_PHY_CONTROL1_FSEL_SHIFT);

	timeout = jiffies + msecs_to_jiffies(200);
	while (time_before(jiffies, timeout)) {
		unsigned int val;

		regmap_read(p_phy->cr_top, USB_PHY_STATUS, &val);
		if (val & USB_PHY_STATUS_VBUS_FAULT) {
			dev_err(p_phy->dev, "VBUS fault detected\n");
			ret = -EIO;
			goto disable_clk;
		}
		if ((val & USB_PHY_STATUS_RX_PHY_CLK) &&
		    (val & USB_PHY_STATUS_RX_UTMI_CLK))
			return 0;
		usleep_range(1000, 1500);
	}

	dev_err(p_phy->dev, "Timed out waiting for PHY to power on\n");
	ret = -ETIMEDOUT;

disable_clk:
	clk_disable_unprepare(p_phy->phy_clk);
	return ret;
}