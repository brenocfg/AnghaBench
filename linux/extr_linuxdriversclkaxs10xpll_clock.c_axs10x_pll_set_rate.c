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
struct clk_hw {int dummy; } ;
struct axs10x_pll_clk {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; struct axs10x_pll_cfg* pll_cfg; } ;
struct axs10x_pll_cfg {unsigned long rate; int /*<<< orphan*/  odiv; int /*<<< orphan*/  fbdiv; int /*<<< orphan*/  idiv; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int PLL_ERROR ; 
 int PLL_LOCK ; 
 int /*<<< orphan*/  PLL_MAX_LOCK_TIME ; 
 int /*<<< orphan*/  PLL_REG_FBDIV ; 
 int /*<<< orphan*/  PLL_REG_IDIV ; 
 int /*<<< orphan*/  PLL_REG_ODIV ; 
 int /*<<< orphan*/  axs10x_encode_div (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  axs10x_pll_write (struct axs10x_pll_clk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned long,unsigned long) ; 
 int ioread32 (int /*<<< orphan*/ ) ; 
 struct axs10x_pll_clk* to_axs10x_pll_clk (struct clk_hw*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int axs10x_pll_set_rate(struct clk_hw *hw, unsigned long rate,
			       unsigned long parent_rate)
{
	int i;
	struct axs10x_pll_clk *clk = to_axs10x_pll_clk(hw);
	const struct axs10x_pll_cfg *pll_cfg = clk->pll_cfg;

	for (i = 0; pll_cfg[i].rate != 0; i++) {
		if (pll_cfg[i].rate == rate) {
			axs10x_pll_write(clk, PLL_REG_IDIV,
					 axs10x_encode_div(pll_cfg[i].idiv, 0));
			axs10x_pll_write(clk, PLL_REG_FBDIV,
					 axs10x_encode_div(pll_cfg[i].fbdiv, 0));
			axs10x_pll_write(clk, PLL_REG_ODIV,
					 axs10x_encode_div(pll_cfg[i].odiv, 1));

			/*
			 * Wait until CGU relocks and check error status.
			 * If after timeout CGU is unlocked yet return error
			 */
			udelay(PLL_MAX_LOCK_TIME);
			if (!(ioread32(clk->lock) & PLL_LOCK))
				return -ETIMEDOUT;

			if (ioread32(clk->lock) & PLL_ERROR)
				return -EINVAL;

			return 0;
		}
	}

	dev_err(clk->dev, "invalid rate=%ld, parent_rate=%ld\n", rate,
			parent_rate);
	return -EINVAL;
}