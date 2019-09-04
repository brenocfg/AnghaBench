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
struct clk_plldiv {int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_PMC_MCKR ; 
 int /*<<< orphan*/  AT91_PMC_PLLADIV2 ; 
 int EINVAL ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk_plldiv* to_clk_plldiv (struct clk_hw*) ; 

__attribute__((used)) static int clk_plldiv_set_rate(struct clk_hw *hw, unsigned long rate,
			       unsigned long parent_rate)
{
	struct clk_plldiv *plldiv = to_clk_plldiv(hw);

	if ((parent_rate != rate) && (parent_rate / 2 != rate))
		return -EINVAL;

	regmap_update_bits(plldiv->regmap, AT91_PMC_MCKR, AT91_PMC_PLLADIV2,
			   parent_rate != rate ? AT91_PMC_PLLADIV2 : 0);

	return 0;
}