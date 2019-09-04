#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  regmap; } ;
struct TYPE_6__ {TYPE_2__* parent_map; } ;
struct clk_rcg {int /*<<< orphan*/  ns_reg; TYPE_1__ clkr; TYPE_3__ s; } ;
struct clk_hw {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  src_to_ns (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk_rcg* to_clk_rcg (struct clk_hw*) ; 

__attribute__((used)) static int clk_rcg_set_parent(struct clk_hw *hw, u8 index)
{
	struct clk_rcg *rcg = to_clk_rcg(hw);
	u32 ns;

	regmap_read(rcg->clkr.regmap, rcg->ns_reg, &ns);
	ns = src_to_ns(&rcg->s, rcg->s.parent_map[index].cfg, ns);
	regmap_write(rcg->clkr.regmap, rcg->ns_reg, ns);

	return 0;
}