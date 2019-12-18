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
typedef  int u32 ;
struct du_clk_params {unsigned long diff; unsigned long rate; int escr; struct clk* clk; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_CLOSEST (unsigned long,unsigned long) ; 
 unsigned long abs (unsigned long) ; 
 int clamp (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 unsigned long clk_round_rate (struct clk*,unsigned long) ; 

__attribute__((used)) static void rcar_du_escr_divider(struct clk *clk, unsigned long target,
				 u32 escr, struct du_clk_params *params)
{
	unsigned long rate;
	unsigned long diff;
	u32 div;

	/*
	 * If the target rate has already been achieved perfectly we can't do
	 * better.
	 */
	if (params->diff == 0)
		return;

	/*
	 * Compute the input clock rate and internal divisor values to obtain
	 * the clock rate closest to the target frequency.
	 */
	rate = clk_round_rate(clk, target);
	div = clamp(DIV_ROUND_CLOSEST(rate, target), 1UL, 64UL) - 1;
	diff = abs(rate / (div + 1) - target);

	/*
	 * Store the parameters if the resulting frequency is better than any
	 * previously calculated value.
	 */
	if (diff < params->diff) {
		params->clk = clk;
		params->rate = rate;
		params->diff = diff;
		params->escr = escr | div;
	}
}