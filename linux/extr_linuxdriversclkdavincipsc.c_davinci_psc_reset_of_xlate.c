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
struct reset_controller_dev {int dummy; } ;
struct of_phandle_args {int dummy; } ;
struct davinci_lpsc_clk {int flags; int md; } ;
struct clk_hw {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int LPSC_LOCAL_RESET ; 
 int PTR_ERR (struct clk*) ; 
 struct clk_hw* __clk_get_hw (struct clk*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 struct clk* of_clk_get_from_provider (struct of_phandle_args*) ; 
 struct davinci_lpsc_clk* to_davinci_lpsc_clk (struct clk_hw*) ; 

__attribute__((used)) static int davinci_psc_reset_of_xlate(struct reset_controller_dev *rcdev,
				      const struct of_phandle_args *reset_spec)
{
	struct of_phandle_args clkspec = *reset_spec; /* discard const qualifier */
	struct clk *clk;
	struct clk_hw *hw;
	struct davinci_lpsc_clk *lpsc;

	/* the clock node is the same as the reset node */
	clk = of_clk_get_from_provider(&clkspec);
	if (IS_ERR(clk))
		return PTR_ERR(clk);

	hw = __clk_get_hw(clk);
	lpsc = to_davinci_lpsc_clk(hw);
	clk_put(clk);

	/* not all modules support local reset */
	if (!(lpsc->flags & LPSC_LOCAL_RESET))
		return -EINVAL;

	return lpsc->md;
}