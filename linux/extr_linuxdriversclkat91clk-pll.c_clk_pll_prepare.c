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
typedef  int u8 ;
typedef  unsigned int u32 ;
typedef  int u16 ;
struct regmap {int dummy; } ;
struct clk_pll_layout {int mul_mask; int mul_shift; int /*<<< orphan*/  pllr_mask; } ;
struct clk_pll_characteristics {int* out; int* icpll; } ;
struct clk_pll {int id; int div; int mul; size_t range; struct clk_pll_characteristics* characteristics; struct clk_pll_layout* layout; struct regmap* regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int AT91_PMC_PLLICPR ; 
 int AT91_PMC_SR ; 
 int PLL_COUNT_SHIFT ; 
 int PLL_DIV (unsigned int) ; 
 int /*<<< orphan*/  PLL_ICPR_MASK (int) ; 
 int PLL_ICPR_SHIFT (int) ; 
 int PLL_MAX_COUNT ; 
 int PLL_MUL (unsigned int,struct clk_pll_layout const*) ; 
 int PLL_OUT_SHIFT ; 
 int PLL_REG (int) ; 
 unsigned int PLL_STATUS_MASK (int) ; 
 int /*<<< orphan*/  clk_pll_ready (struct regmap*,int) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int,int /*<<< orphan*/ ,int) ; 
 struct clk_pll* to_clk_pll (struct clk_hw*) ; 

__attribute__((used)) static int clk_pll_prepare(struct clk_hw *hw)
{
	struct clk_pll *pll = to_clk_pll(hw);
	struct regmap *regmap = pll->regmap;
	const struct clk_pll_layout *layout = pll->layout;
	const struct clk_pll_characteristics *characteristics =
							pll->characteristics;
	u8 id = pll->id;
	u32 mask = PLL_STATUS_MASK(id);
	int offset = PLL_REG(id);
	u8 out = 0;
	unsigned int pllr;
	unsigned int status;
	u8 div;
	u16 mul;

	regmap_read(regmap, offset, &pllr);
	div = PLL_DIV(pllr);
	mul = PLL_MUL(pllr, layout);

	regmap_read(regmap, AT91_PMC_SR, &status);
	if ((status & mask) &&
	    (div == pll->div && mul == pll->mul))
		return 0;

	if (characteristics->out)
		out = characteristics->out[pll->range];

	if (characteristics->icpll)
		regmap_update_bits(regmap, AT91_PMC_PLLICPR, PLL_ICPR_MASK(id),
			characteristics->icpll[pll->range] << PLL_ICPR_SHIFT(id));

	regmap_update_bits(regmap, offset, layout->pllr_mask,
			pll->div | (PLL_MAX_COUNT << PLL_COUNT_SHIFT) |
			(out << PLL_OUT_SHIFT) |
			((pll->mul & layout->mul_mask) << layout->mul_shift));

	while (!clk_pll_ready(regmap, pll->id))
		cpu_relax();

	return 0;
}