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
struct clk_rate_request {int /*<<< orphan*/  best_parent_rate; int /*<<< orphan*/  rate; struct clk_hw* best_parent_hw; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_hw_round_rate (struct clk_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clk_rcg_bypass2_determine_rate(struct clk_hw *hw,
				struct clk_rate_request *req)
{
	struct clk_hw *p;

	p = req->best_parent_hw;
	req->best_parent_rate = clk_hw_round_rate(p, req->rate);
	req->rate = req->best_parent_rate;

	return 0;
}