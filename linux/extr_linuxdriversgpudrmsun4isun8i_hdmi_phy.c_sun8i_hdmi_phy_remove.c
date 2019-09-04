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
struct sun8i_hdmi_phy {int /*<<< orphan*/  clk_bus; int /*<<< orphan*/  clk_mod; int /*<<< orphan*/  clk_pll1; int /*<<< orphan*/  clk_pll0; int /*<<< orphan*/  rst_phy; int /*<<< orphan*/  clk_phy; } ;
struct sun8i_dw_hdmi {struct sun8i_hdmi_phy* phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_put (int /*<<< orphan*/ ) ; 

void sun8i_hdmi_phy_remove(struct sun8i_dw_hdmi *hdmi)
{
	struct sun8i_hdmi_phy *phy = hdmi->phy;

	clk_disable_unprepare(phy->clk_mod);
	clk_disable_unprepare(phy->clk_bus);
	clk_disable_unprepare(phy->clk_phy);

	reset_control_assert(phy->rst_phy);

	reset_control_put(phy->rst_phy);

	clk_put(phy->clk_pll0);
	clk_put(phy->clk_pll1);
	clk_put(phy->clk_mod);
	clk_put(phy->clk_bus);
}