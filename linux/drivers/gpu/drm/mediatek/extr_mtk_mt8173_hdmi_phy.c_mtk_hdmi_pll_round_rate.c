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
struct mtk_hdmi_phy {unsigned long pll_rate; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct mtk_hdmi_phy* to_mtk_hdmi_phy (struct clk_hw*) ; 

__attribute__((used)) static long mtk_hdmi_pll_round_rate(struct clk_hw *hw, unsigned long rate,
				    unsigned long *parent_rate)
{
	struct mtk_hdmi_phy *hdmi_phy = to_mtk_hdmi_phy(hw);

	hdmi_phy->pll_rate = rate;
	if (rate <= 74250000)
		*parent_rate = rate;
	else
		*parent_rate = rate / 2;

	return rate;
}