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
struct usb_phy_generic {int /*<<< orphan*/  clk; int /*<<< orphan*/  vcc; } ;
struct usb_phy {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct usb_phy_generic* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nop_reset (struct usb_phy_generic*) ; 
 scalar_t__ regulator_enable (int /*<<< orphan*/ ) ; 

int usb_gen_phy_init(struct usb_phy *phy)
{
	struct usb_phy_generic *nop = dev_get_drvdata(phy->dev);
	int ret;

	if (!IS_ERR(nop->vcc)) {
		if (regulator_enable(nop->vcc))
			dev_err(phy->dev, "Failed to enable power\n");
	}

	if (!IS_ERR(nop->clk)) {
		ret = clk_prepare_enable(nop->clk);
		if (ret)
			return ret;
	}

	nop_reset(nop);

	return 0;
}