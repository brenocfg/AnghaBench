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
typedef  int /*<<< orphan*/  u8 ;
struct sun4i_ddc {int /*<<< orphan*/  reg; int /*<<< orphan*/  m_offset; int /*<<< orphan*/  pre_div; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int SUN4I_HDMI_DDC_CLK_M (int /*<<< orphan*/ ) ; 
 int SUN4I_HDMI_DDC_CLK_N (int /*<<< orphan*/ ) ; 
 struct sun4i_ddc* hw_to_ddc (struct clk_hw*) ; 
 int /*<<< orphan*/  regmap_field_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sun4i_ddc_calc_divider (unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sun4i_ddc_set_rate(struct clk_hw *hw, unsigned long rate,
			      unsigned long parent_rate)
{
	struct sun4i_ddc *ddc = hw_to_ddc(hw);
	u8 div_m, div_n;

	sun4i_ddc_calc_divider(rate, parent_rate, ddc->pre_div,
			       ddc->m_offset, &div_m, &div_n);

	regmap_field_write(ddc->reg,
			   SUN4I_HDMI_DDC_CLK_M(div_m) |
			   SUN4I_HDMI_DDC_CLK_N(div_n));

	return 0;
}