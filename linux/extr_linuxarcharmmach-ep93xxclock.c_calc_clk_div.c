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
struct clk {int rate; struct clk* parent; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long abs (unsigned long) ; 
 struct clk clk_pll1 ; 
 struct clk clk_pll2 ; 
 struct clk clk_xtali ; 
 unsigned long max3 (int,int,int) ; 
 unsigned long min (unsigned long,unsigned long) ; 

__attribute__((used)) static int calc_clk_div(struct clk *clk, unsigned long rate,
			int *psel, int *esel, int *pdiv, int *div)
{
	struct clk *mclk;
	unsigned long max_rate, actual_rate, mclk_rate, rate_err = -1;
	int i, found = 0, __div = 0, __pdiv = 0;

	/* Don't exceed the maximum rate */
	max_rate = max3(clk_pll1.rate / 4, clk_pll2.rate / 4, clk_xtali.rate / 4);
	rate = min(rate, max_rate);

	/*
	 * Try the two pll's and the external clock
	 * Because the valid predividers are 2, 2.5 and 3, we multiply
	 * all the clocks by 2 to avoid floating point math.
	 *
	 * This is based on the algorithm in the ep93xx raster guide:
	 * http://be-a-maverick.com/en/pubs/appNote/AN269REV1.pdf
	 *
	 */
	for (i = 0; i < 3; i++) {
		if (i == 0)
			mclk = &clk_xtali;
		else if (i == 1)
			mclk = &clk_pll1;
		else
			mclk = &clk_pll2;
		mclk_rate = mclk->rate * 2;

		/* Try each predivider value */
		for (__pdiv = 4; __pdiv <= 6; __pdiv++) {
			__div = mclk_rate / (rate * __pdiv);
			if (__div < 2 || __div > 127)
				continue;

			actual_rate = mclk_rate / (__pdiv * __div);

			if (!found || abs(actual_rate - rate) < rate_err) {
				*pdiv = __pdiv - 3;
				*div = __div;
				*psel = (i == 2);
				*esel = (i != 0);
				clk->parent = mclk;
				clk->rate = actual_rate;
				rate_err = abs(actual_rate - rate);
				found = 1;
			}
		}
	}

	if (!found)
		return -EINVAL;

	return 0;
}