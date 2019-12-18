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
struct usb_hcd {int dummy; } ;
struct tegra_ehci_hcd {int /*<<< orphan*/  rst; } ;
struct reset_control {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_3__ {scalar_t__ priv; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ IS_ERR (struct reset_control*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 TYPE_1__* hcd_to_ehci (struct usb_hcd*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct reset_control* of_reset_control_get_shared (struct device_node*,char*) ; 
 struct usb_hcd* platform_get_drvdata (struct platform_device*) ; 
 int reset_control_assert (int /*<<< orphan*/ ) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_put (struct reset_control*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int tegra_reset_usb_controller(struct platform_device *pdev)
{
	struct device_node *phy_np;
	struct usb_hcd *hcd = platform_get_drvdata(pdev);
	struct tegra_ehci_hcd *tegra =
		(struct tegra_ehci_hcd *)hcd_to_ehci(hcd)->priv;
	struct reset_control *rst;
	int err;

	phy_np = of_parse_phandle(pdev->dev.of_node, "nvidia,phy", 0);
	if (!phy_np)
		return -ENOENT;

	/*
	 * The 1st USB controller contains some UTMI pad registers that are
	 * global for all the controllers on the chip. Those registers are
	 * also cleared when reset is asserted to the 1st controller.
	 */
	rst = of_reset_control_get_shared(phy_np, "utmi-pads");
	if (IS_ERR(rst)) {
		dev_warn(&pdev->dev,
			 "can't get utmi-pads reset from the PHY\n");
		dev_warn(&pdev->dev,
			 "continuing, but please update your DT\n");
	} else {
		/*
		 * PHY driver performs UTMI-pads reset in a case of
		 * non-legacy DT.
		 */
		reset_control_put(rst);
	}

	of_node_put(phy_np);

	/* reset control is shared, hence initialize it first */
	err = reset_control_deassert(tegra->rst);
	if (err)
		return err;

	err = reset_control_assert(tegra->rst);
	if (err)
		return err;

	udelay(1);

	err = reset_control_deassert(tegra->rst);
	if (err)
		return err;

	return 0;
}