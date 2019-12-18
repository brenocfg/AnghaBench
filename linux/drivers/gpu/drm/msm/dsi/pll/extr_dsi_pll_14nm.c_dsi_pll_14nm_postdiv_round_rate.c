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
struct dsi_pll_14nm_postdiv {int /*<<< orphan*/  flags; int /*<<< orphan*/  width; struct dsi_pll_14nm* pll; } ;
struct dsi_pll_14nm {int /*<<< orphan*/  id; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,unsigned long) ; 
 long divider_round_rate (struct clk_hw*,unsigned long,unsigned long*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dsi_pll_14nm_postdiv* to_pll_14nm_postdiv (struct clk_hw*) ; 

__attribute__((used)) static long dsi_pll_14nm_postdiv_round_rate(struct clk_hw *hw,
					    unsigned long rate,
					    unsigned long *prate)
{
	struct dsi_pll_14nm_postdiv *postdiv = to_pll_14nm_postdiv(hw);
	struct dsi_pll_14nm *pll_14nm = postdiv->pll;

	DBG("DSI%d PLL parent rate=%lu", pll_14nm->id, rate);

	return divider_round_rate(hw, rate, prate, NULL,
				  postdiv->width,
				  postdiv->flags);
}