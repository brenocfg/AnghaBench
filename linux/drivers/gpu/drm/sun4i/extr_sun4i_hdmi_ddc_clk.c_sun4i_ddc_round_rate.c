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
struct sun4i_ddc {int /*<<< orphan*/  m_offset; int /*<<< orphan*/  pre_div; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct sun4i_ddc* hw_to_ddc (struct clk_hw*) ; 
 long sun4i_ddc_calc_divider (unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static long sun4i_ddc_round_rate(struct clk_hw *hw, unsigned long rate,
				 unsigned long *prate)
{
	struct sun4i_ddc *ddc = hw_to_ddc(hw);

	return sun4i_ddc_calc_divider(rate, *prate, ddc->pre_div,
				      ddc->m_offset, NULL, NULL);
}