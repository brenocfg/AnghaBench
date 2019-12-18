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
struct phy {int dummy; } ;
struct mtk_hdmi_phy {int /*<<< orphan*/  pll; TYPE_1__* conf; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* hdmi_phy_disable_tmds ) (struct mtk_hdmi_phy*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct mtk_hdmi_phy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  stub1 (struct mtk_hdmi_phy*) ; 

__attribute__((used)) static int mtk_hdmi_phy_power_off(struct phy *phy)
{
	struct mtk_hdmi_phy *hdmi_phy = phy_get_drvdata(phy);

	hdmi_phy->conf->hdmi_phy_disable_tmds(hdmi_phy);
	clk_disable_unprepare(hdmi_phy->pll);

	return 0;
}