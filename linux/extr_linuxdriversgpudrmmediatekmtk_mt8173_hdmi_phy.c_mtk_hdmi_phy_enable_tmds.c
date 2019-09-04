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
struct mtk_hdmi_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_CON3 ; 
 int RG_HDMITX_DRV_EN ; 
 int RG_HDMITX_PRD_EN ; 
 int RG_HDMITX_SER_EN ; 
 int /*<<< orphan*/  mtk_hdmi_phy_set_bits (struct mtk_hdmi_phy*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void mtk_hdmi_phy_enable_tmds(struct mtk_hdmi_phy *hdmi_phy)
{
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON3,
			      RG_HDMITX_SER_EN | RG_HDMITX_PRD_EN |
			      RG_HDMITX_DRV_EN);
	usleep_range(100, 150);
}