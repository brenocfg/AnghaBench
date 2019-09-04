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
struct clk_sama5d4_h32mx {int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned int AT91_PMC_H32MXDIV ; 
 int /*<<< orphan*/  AT91_PMC_MCKR ; 
 unsigned long H32MX_MAX_FREQ ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct clk_sama5d4_h32mx* to_clk_sama5d4_h32mx (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_sama5d4_h32mx_recalc_rate(struct clk_hw *hw,
						 unsigned long parent_rate)
{
	struct clk_sama5d4_h32mx *h32mxclk = to_clk_sama5d4_h32mx(hw);
	unsigned int mckr;

	regmap_read(h32mxclk->regmap, AT91_PMC_MCKR, &mckr);
	if (mckr & AT91_PMC_H32MXDIV)
		return parent_rate / 2;

	if (parent_rate > H32MX_MAX_FREQ)
		pr_warn("H32MX clock is too fast\n");
	return parent_rate;
}