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
struct tegra_dfll {int dummy; } ;
struct dfll_rate_req {int dummy; } ;
struct clk_rate_request {int /*<<< orphan*/  rate; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct tegra_dfll* clk_hw_to_dfll (struct clk_hw*) ; 
 int dfll_calculate_rate_request (struct tegra_dfll*,struct dfll_rate_req*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dfll_clk_determine_rate(struct clk_hw *hw,
				   struct clk_rate_request *clk_req)
{
	struct tegra_dfll *td = clk_hw_to_dfll(hw);
	struct dfll_rate_req req;
	int ret;

	ret = dfll_calculate_rate_request(td, &req, clk_req->rate);
	if (ret)
		return ret;

	/*
	 * Don't set the rounded rate, since it doesn't really matter as
	 * the output rate will be voltage controlled anyway, and cpufreq
	 * freaks out if any rounding happens.
	 */

	return 0;
}