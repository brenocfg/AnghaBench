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
struct mtk_hdmi_phy {scalar_t__ regs; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ HDMI_CON2 ; 
 scalar_t__ HDMI_CON6 ; 
 int RG_HDMITX_EN_TX_POSDIV ; 
 unsigned long RG_HDMITX_TX_POSDIV ; 
 int RG_HDMITX_TX_POSDIV_MASK ; 
 int RG_HTPLL_FBKDIV ; 
 int RG_HTPLL_FBKDIV_MASK ; 
 int RG_HTPLL_PREDIV ; 
 int RG_HTPLL_PREDIV_MASK ; 
 int readl (scalar_t__) ; 
 struct mtk_hdmi_phy* to_mtk_hdmi_phy (struct clk_hw*) ; 

__attribute__((used)) static unsigned long mtk_hdmi_pll_recalc_rate(struct clk_hw *hw,
					      unsigned long parent_rate)
{
	struct mtk_hdmi_phy *hdmi_phy = to_mtk_hdmi_phy(hw);
	unsigned long out_rate, val;

	val = (readl(hdmi_phy->regs + HDMI_CON6)
	       & RG_HTPLL_PREDIV_MASK) >> RG_HTPLL_PREDIV;
	switch (val) {
	case 0x00:
		out_rate = parent_rate;
		break;
	case 0x01:
		out_rate = parent_rate / 2;
		break;
	default:
		out_rate = parent_rate / 4;
		break;
	}

	val = (readl(hdmi_phy->regs + HDMI_CON6)
	       & RG_HTPLL_FBKDIV_MASK) >> RG_HTPLL_FBKDIV;
	out_rate *= (val + 1) * 2;
	val = (readl(hdmi_phy->regs + HDMI_CON2)
	       & RG_HDMITX_TX_POSDIV_MASK);
	out_rate >>= (val >> RG_HDMITX_TX_POSDIV);

	if (readl(hdmi_phy->regs + HDMI_CON2) & RG_HDMITX_EN_TX_POSDIV)
		out_rate /= 5;

	return out_rate;
}