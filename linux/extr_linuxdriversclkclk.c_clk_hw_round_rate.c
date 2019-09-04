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
struct clk_rate_request {unsigned long rate; int /*<<< orphan*/  max_rate; int /*<<< orphan*/  min_rate; } ;
struct clk_hw {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_core_get_boundaries (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int clk_core_round_rate_nolock (int /*<<< orphan*/ ,struct clk_rate_request*) ; 

unsigned long clk_hw_round_rate(struct clk_hw *hw, unsigned long rate)
{
	int ret;
	struct clk_rate_request req;

	clk_core_get_boundaries(hw->core, &req.min_rate, &req.max_rate);
	req.rate = rate;

	ret = clk_core_round_rate_nolock(hw->core, &req);
	if (ret)
		return 0;

	return req.rate;
}