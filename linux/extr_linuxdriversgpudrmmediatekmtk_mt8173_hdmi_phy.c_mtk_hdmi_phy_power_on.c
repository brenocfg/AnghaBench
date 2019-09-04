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
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_hdmi_phy_enable_tmds (struct mtk_hdmi_phy*) ; 
 struct mtk_hdmi_phy* phy_get_drvdata (struct phy*) ; 

__attribute__((used)) static int mtk_hdmi_phy_power_on(struct phy *phy)
{
	struct mtk_hdmi_phy *hdmi_phy = phy_get_drvdata(phy);
	int ret;

	ret = clk_prepare_enable(hdmi_phy->pll);
	if (ret < 0)
		return ret;

	mtk_hdmi_phy_enable_tmds(hdmi_phy);

	return 0;
}