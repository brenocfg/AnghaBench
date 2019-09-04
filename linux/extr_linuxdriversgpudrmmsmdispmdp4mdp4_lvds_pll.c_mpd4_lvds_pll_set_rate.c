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
struct mdp4_lvds_pll {unsigned long pixclk; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct mdp4_lvds_pll* to_mdp4_lvds_pll (struct clk_hw*) ; 

__attribute__((used)) static int mpd4_lvds_pll_set_rate(struct clk_hw *hw, unsigned long rate,
		unsigned long parent_rate)
{
	struct mdp4_lvds_pll *lvds_pll = to_mdp4_lvds_pll(hw);
	lvds_pll->pixclk = rate;
	return 0;
}