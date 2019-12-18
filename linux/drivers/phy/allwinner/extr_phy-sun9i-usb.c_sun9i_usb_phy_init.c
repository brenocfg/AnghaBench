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
struct sun9i_usb_phy {int /*<<< orphan*/  clk; int /*<<< orphan*/  hsic_clk; int /*<<< orphan*/  reset; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct sun9i_usb_phy* phy_get_drvdata (struct phy*) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun9i_usb_phy_passby (struct sun9i_usb_phy*,int) ; 

__attribute__((used)) static int sun9i_usb_phy_init(struct phy *_phy)
{
	struct sun9i_usb_phy *phy = phy_get_drvdata(_phy);
	int ret;

	ret = clk_prepare_enable(phy->clk);
	if (ret)
		goto err_clk;

	ret = clk_prepare_enable(phy->hsic_clk);
	if (ret)
		goto err_hsic_clk;

	ret = reset_control_deassert(phy->reset);
	if (ret)
		goto err_reset;

	sun9i_usb_phy_passby(phy, 1);
	return 0;

err_reset:
	clk_disable_unprepare(phy->hsic_clk);

err_hsic_clk:
	clk_disable_unprepare(phy->clk);

err_clk:
	return ret;
}