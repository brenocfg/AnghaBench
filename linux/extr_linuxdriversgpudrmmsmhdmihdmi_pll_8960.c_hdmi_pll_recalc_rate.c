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
struct hdmi_pll_8960 {unsigned long pixclk; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct hdmi_pll_8960* hw_clk_to_pll (struct clk_hw*) ; 

__attribute__((used)) static unsigned long hdmi_pll_recalc_rate(struct clk_hw *hw,
					  unsigned long parent_rate)
{
	struct hdmi_pll_8960 *pll = hw_clk_to_pll(hw);

	return pll->pixclk;
}