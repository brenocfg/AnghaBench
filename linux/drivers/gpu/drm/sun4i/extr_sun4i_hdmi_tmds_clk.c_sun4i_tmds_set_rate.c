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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct sun4i_tmds {TYPE_1__* hdmi; scalar_t__ div_offset; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {scalar_t__ base; } ;

/* Variables and functions */
 int SUN4I_HDMI_PAD_CTRL1_HALVE_CLK ; 
 scalar_t__ SUN4I_HDMI_PAD_CTRL1_REG ; 
 int SUN4I_HDMI_PLL_CTRL_DIV (scalar_t__) ; 
 int SUN4I_HDMI_PLL_CTRL_DIV_MASK ; 
 scalar_t__ SUN4I_HDMI_PLL_CTRL_REG ; 
 struct sun4i_tmds* hw_to_tmds (struct clk_hw*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  sun4i_tmds_calc_divider (unsigned long,unsigned long,scalar_t__,scalar_t__*,int*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int sun4i_tmds_set_rate(struct clk_hw *hw, unsigned long rate,
			       unsigned long parent_rate)
{
	struct sun4i_tmds *tmds = hw_to_tmds(hw);
	bool half;
	u32 reg;
	u8 div;

	sun4i_tmds_calc_divider(rate, parent_rate, tmds->div_offset,
				&div, &half);

	reg = readl(tmds->hdmi->base + SUN4I_HDMI_PAD_CTRL1_REG);
	reg &= ~SUN4I_HDMI_PAD_CTRL1_HALVE_CLK;
	if (half)
		reg |= SUN4I_HDMI_PAD_CTRL1_HALVE_CLK;
	writel(reg, tmds->hdmi->base + SUN4I_HDMI_PAD_CTRL1_REG);

	reg = readl(tmds->hdmi->base + SUN4I_HDMI_PLL_CTRL_REG);
	reg &= ~SUN4I_HDMI_PLL_CTRL_DIV_MASK;
	writel(reg | SUN4I_HDMI_PLL_CTRL_DIV(div - tmds->div_offset),
	       tmds->hdmi->base + SUN4I_HDMI_PLL_CTRL_REG);

	return 0;
}