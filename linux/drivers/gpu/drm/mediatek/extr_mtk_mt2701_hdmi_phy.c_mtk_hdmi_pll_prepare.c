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
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_CON0 ; 
 int /*<<< orphan*/  HDMI_CON2 ; 
 int /*<<< orphan*/  HDMI_CON6 ; 
 int /*<<< orphan*/  HDMI_CON7 ; 
 int /*<<< orphan*/  RG_HDMITX_EN_DRV_MASK ; 
 int /*<<< orphan*/  RG_HDMITX_EN_MBIAS ; 
 int /*<<< orphan*/  RG_HDMITX_EN_PRED_MASK ; 
 int /*<<< orphan*/  RG_HDMITX_EN_SER_MASK ; 
 int /*<<< orphan*/  RG_HDMITX_EN_SLDO_MASK ; 
 int /*<<< orphan*/  RG_HDMITX_EN_TX_CKLDO ; 
 int /*<<< orphan*/  RG_HDMITX_MBIAS_LPF_EN ; 
 int /*<<< orphan*/  RG_HTPLL_AUTOK_EN ; 
 int /*<<< orphan*/  RG_HTPLL_EN ; 
 int /*<<< orphan*/  RG_HTPLL_POSDIV_MASK ; 
 int /*<<< orphan*/  RG_HTPLL_RLH_EN ; 
 int /*<<< orphan*/  mtk_hdmi_phy_clear_bits (struct mtk_hdmi_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_hdmi_phy_set_bits (struct mtk_hdmi_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mtk_hdmi_phy* to_mtk_hdmi_phy (struct clk_hw*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int mtk_hdmi_pll_prepare(struct clk_hw *hw)
{
	struct mtk_hdmi_phy *hdmi_phy = to_mtk_hdmi_phy(hw);

	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON7, RG_HTPLL_AUTOK_EN);
	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON6, RG_HTPLL_RLH_EN);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON6, RG_HTPLL_POSDIV_MASK);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON2, RG_HDMITX_EN_MBIAS);
	usleep_range(80, 100);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON6, RG_HTPLL_EN);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON2, RG_HDMITX_EN_TX_CKLDO);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON0, RG_HDMITX_EN_SLDO_MASK);
	usleep_range(80, 100);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON2, RG_HDMITX_MBIAS_LPF_EN);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON0, RG_HDMITX_EN_SER_MASK);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON0, RG_HDMITX_EN_PRED_MASK);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON0, RG_HDMITX_EN_DRV_MASK);
	usleep_range(80, 100);
	return 0;
}