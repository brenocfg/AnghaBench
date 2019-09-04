#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct freq_tbl {int /*<<< orphan*/  src; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent_map; } ;
struct clk_rcg {TYPE_1__ s; struct freq_tbl* freq_tbl; } ;
struct clk_rate_request {int /*<<< orphan*/  best_parent_rate; int /*<<< orphan*/  rate; struct clk_hw* best_parent_hw; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct clk_hw* clk_hw_get_parent_by_index (struct clk_hw*,int) ; 
 int /*<<< orphan*/  clk_hw_round_rate (struct clk_hw*,int /*<<< orphan*/ ) ; 
 int qcom_find_src_index (struct clk_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk_rcg* to_clk_rcg (struct clk_hw*) ; 

__attribute__((used)) static int clk_rcg_bypass_determine_rate(struct clk_hw *hw,
					 struct clk_rate_request *req)
{
	struct clk_rcg *rcg = to_clk_rcg(hw);
	const struct freq_tbl *f = rcg->freq_tbl;
	struct clk_hw *p;
	int index = qcom_find_src_index(hw, rcg->s.parent_map, f->src);

	req->best_parent_hw = p = clk_hw_get_parent_by_index(hw, index);
	req->best_parent_rate = clk_hw_round_rate(p, req->rate);
	req->rate = req->best_parent_rate;

	return 0;
}