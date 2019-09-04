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
struct phy {int dummy; } ;
struct mtk_hdmi_phy {int /*<<< orphan*/  pll; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_hdmi_phy_disable_tmds (struct mtk_hdmi_phy*) ; 
 struct mtk_hdmi_phy* phy_get_drvdata (struct phy*) ; 

__attribute__((used)) static int mtk_hdmi_phy_power_off(struct phy *phy)
{
	struct mtk_hdmi_phy *hdmi_phy = phy_get_drvdata(phy);

	mtk_hdmi_phy_disable_tmds(hdmi_phy);
	clk_disable_unprepare(hdmi_phy->pll);

	return 0;
}