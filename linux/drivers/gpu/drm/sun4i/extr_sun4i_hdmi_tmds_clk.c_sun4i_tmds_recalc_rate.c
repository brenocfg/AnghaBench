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
typedef  int u32 ;
struct sun4i_tmds {int div_offset; TYPE_1__* hdmi; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {scalar_t__ base; } ;

/* Variables and functions */
 int SUN4I_HDMI_PAD_CTRL1_HALVE_CLK ; 
 scalar_t__ SUN4I_HDMI_PAD_CTRL1_REG ; 
 scalar_t__ SUN4I_HDMI_PLL_CTRL_REG ; 
 struct sun4i_tmds* hw_to_tmds (struct clk_hw*) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static unsigned long sun4i_tmds_recalc_rate(struct clk_hw *hw,
					    unsigned long parent_rate)
{
	struct sun4i_tmds *tmds = hw_to_tmds(hw);
	u32 reg;

	reg = readl(tmds->hdmi->base + SUN4I_HDMI_PAD_CTRL1_REG);
	if (reg & SUN4I_HDMI_PAD_CTRL1_HALVE_CLK)
		parent_rate /= 2;

	reg = readl(tmds->hdmi->base + SUN4I_HDMI_PLL_CTRL_REG);
	reg = ((reg >> 4) & 0xf) + tmds->div_offset;
	if (!reg)
		reg = 1;

	return parent_rate / reg;
}