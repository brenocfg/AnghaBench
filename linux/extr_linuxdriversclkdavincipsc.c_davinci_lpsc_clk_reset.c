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
typedef  int /*<<< orphan*/  u32 ;
struct davinci_lpsc_clk {int /*<<< orphan*/  md; int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR_OR_NULL (struct davinci_lpsc_clk*) ; 
 int /*<<< orphan*/  MDCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MDCTL_LRESET ; 
 struct clk_hw* __clk_get_hw (struct clk*) ; 
 int /*<<< orphan*/  regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct davinci_lpsc_clk* to_davinci_lpsc_clk (struct clk_hw*) ; 

__attribute__((used)) static int davinci_lpsc_clk_reset(struct clk *clk, bool reset)
{
	struct clk_hw *hw = __clk_get_hw(clk);
	struct davinci_lpsc_clk *lpsc = to_davinci_lpsc_clk(hw);
	u32 mdctl;

	if (IS_ERR_OR_NULL(lpsc))
		return -EINVAL;

	mdctl = reset ? 0 : MDCTL_LRESET;
	regmap_write_bits(lpsc->regmap, MDCTL(lpsc->md), MDCTL_LRESET, mdctl);

	return 0;
}