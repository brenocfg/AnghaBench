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
struct clk_vco {int /*<<< orphan*/  rtbl_cnt; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 long clk_round_rate_index (struct clk_hw*,unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct clk_vco* to_clk_vco (struct clk_hw*) ; 
 int /*<<< orphan*/  vco_calc_rate ; 

__attribute__((used)) static long clk_vco_round_rate(struct clk_hw *hw, unsigned long drate,
		unsigned long *prate)
{
	struct clk_vco *vco = to_clk_vco(hw);
	int unused;

	return clk_round_rate_index(hw, drate, *prate, vco_calc_rate,
			vco->rtbl_cnt, &unused);
}