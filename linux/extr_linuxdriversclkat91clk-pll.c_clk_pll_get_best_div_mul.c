#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct clk_pll_layout {int dummy; } ;
struct TYPE_3__ {unsigned long min; unsigned long max; } ;
struct clk_pll_characteristics {int num_output; TYPE_2__* output; TYPE_1__ input; } ;
struct clk_pll {struct clk_pll_characteristics* characteristics; struct clk_pll_layout* layout; } ;
struct TYPE_4__ {long min; long max; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_CLOSEST (unsigned long,unsigned long) ; 
 unsigned long DIV_ROUND_UP (unsigned long,unsigned long) ; 
 long ERANGE ; 
 unsigned long PLL_DIV_MAX ; 
 unsigned long PLL_MUL_MAX (struct clk_pll_layout const*) ; 
 unsigned long PLL_MUL_MIN ; 
 unsigned long ULONG_MAX ; 

__attribute__((used)) static long clk_pll_get_best_div_mul(struct clk_pll *pll, unsigned long rate,
				     unsigned long parent_rate,
				     u32 *div, u32 *mul,
				     u32 *index) {
	const struct clk_pll_layout *layout = pll->layout;
	const struct clk_pll_characteristics *characteristics =
							pll->characteristics;
	unsigned long bestremainder = ULONG_MAX;
	unsigned long maxdiv, mindiv, tmpdiv;
	long bestrate = -ERANGE;
	unsigned long bestdiv;
	unsigned long bestmul;
	int i = 0;

	/* Check if parent_rate is a valid input rate */
	if (parent_rate < characteristics->input.min)
		return -ERANGE;

	/*
	 * Calculate minimum divider based on the minimum multiplier, the
	 * parent_rate and the requested rate.
	 * Should always be 2 according to the input and output characteristics
	 * of the PLL blocks.
	 */
	mindiv = (parent_rate * PLL_MUL_MIN) / rate;
	if (!mindiv)
		mindiv = 1;

	if (parent_rate > characteristics->input.max) {
		tmpdiv = DIV_ROUND_UP(parent_rate, characteristics->input.max);
		if (tmpdiv > PLL_DIV_MAX)
			return -ERANGE;

		if (tmpdiv > mindiv)
			mindiv = tmpdiv;
	}

	/*
	 * Calculate the maximum divider which is limited by PLL register
	 * layout (limited by the MUL or DIV field size).
	 */
	maxdiv = DIV_ROUND_UP(parent_rate * PLL_MUL_MAX(layout), rate);
	if (maxdiv > PLL_DIV_MAX)
		maxdiv = PLL_DIV_MAX;

	/*
	 * Iterate over the acceptable divider values to find the best
	 * divider/multiplier pair (the one that generates the closest
	 * rate to the requested one).
	 */
	for (tmpdiv = mindiv; tmpdiv <= maxdiv; tmpdiv++) {
		unsigned long remainder;
		unsigned long tmprate;
		unsigned long tmpmul;

		/*
		 * Calculate the multiplier associated with the current
		 * divider that provide the closest rate to the requested one.
		 */
		tmpmul = DIV_ROUND_CLOSEST(rate, parent_rate / tmpdiv);
		tmprate = (parent_rate / tmpdiv) * tmpmul;
		if (tmprate > rate)
			remainder = tmprate - rate;
		else
			remainder = rate - tmprate;

		/*
		 * Compare the remainder with the best remainder found until
		 * now and elect a new best multiplier/divider pair if the
		 * current remainder is smaller than the best one.
		 */
		if (remainder < bestremainder) {
			bestremainder = remainder;
			bestdiv = tmpdiv;
			bestmul = tmpmul;
			bestrate = tmprate;
		}

		/*
		 * We've found a perfect match!
		 * Stop searching now and use this multiplier/divider pair.
		 */
		if (!remainder)
			break;
	}

	/* We haven't found any multiplier/divider pair => return -ERANGE */
	if (bestrate < 0)
		return bestrate;

	/* Check if bestrate is a valid output rate  */
	for (i = 0; i < characteristics->num_output; i++) {
		if (bestrate >= characteristics->output[i].min &&
		    bestrate <= characteristics->output[i].max)
			break;
	}

	if (i >= characteristics->num_output)
		return -ERANGE;

	if (div)
		*div = bestdiv;
	if (mul)
		*mul = bestmul - 1;
	if (index)
		*index = i;

	return bestrate;
}