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
typedef  int /*<<< orphan*/  u32 ;
struct src_sel {int /*<<< orphan*/  parent_map; } ;
struct clk_rate_request {int dummy; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;
struct clk_dyn_rcg {int /*<<< orphan*/  freq_tbl; struct src_sel* s; int /*<<< orphan*/  bank_reg; TYPE_1__ clkr; } ;

/* Variables and functions */
 int _freq_tbl_determine_rate (struct clk_hw*,int /*<<< orphan*/ ,struct clk_rate_request*,int /*<<< orphan*/ ) ; 
 int reg_to_bank (struct clk_dyn_rcg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct clk_dyn_rcg* to_clk_dyn_rcg (struct clk_hw*) ; 

__attribute__((used)) static int clk_dyn_rcg_determine_rate(struct clk_hw *hw,
				      struct clk_rate_request *req)
{
	struct clk_dyn_rcg *rcg = to_clk_dyn_rcg(hw);
	u32 reg;
	int bank;
	struct src_sel *s;

	regmap_read(rcg->clkr.regmap, rcg->bank_reg, &reg);
	bank = reg_to_bank(rcg, reg);
	s = &rcg->s[bank];

	return _freq_tbl_determine_rate(hw, rcg->freq_tbl, req, s->parent_map);
}