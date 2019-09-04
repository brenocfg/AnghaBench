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
struct frac_rate_tbl {int div; } ;
struct clk_hw {int dummy; } ;
struct clk_frac {struct frac_rate_tbl* rtbl; } ;

/* Variables and functions */
 struct clk_frac* to_clk_frac (struct clk_hw*) ; 

__attribute__((used)) static unsigned long frac_calc_rate(struct clk_hw *hw, unsigned long prate,
		int index)
{
	struct clk_frac *frac = to_clk_frac(hw);
	struct frac_rate_tbl *rtbl = frac->rtbl;

	prate /= 10000;
	prate <<= 14;
	prate /= (2 * rtbl[index].div);
	prate *= 10000;

	return prate;
}