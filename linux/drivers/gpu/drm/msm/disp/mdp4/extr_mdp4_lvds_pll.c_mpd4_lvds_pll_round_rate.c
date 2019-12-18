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
struct pll_rate {long rate; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct pll_rate* find_rate (unsigned long) ; 

__attribute__((used)) static long mpd4_lvds_pll_round_rate(struct clk_hw *hw, unsigned long rate,
		unsigned long *parent_rate)
{
	const struct pll_rate *pll_rate = find_rate(rate);
	return pll_rate->rate;
}