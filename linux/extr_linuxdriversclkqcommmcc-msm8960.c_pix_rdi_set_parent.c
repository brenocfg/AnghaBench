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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;
struct clk_pix_rdi {scalar_t__ s_mask; int /*<<< orphan*/  s_reg; TYPE_1__ clkr; scalar_t__ s2_mask; int /*<<< orphan*/  s2_reg; } ;
struct clk_hw {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_hw_get_num_parents (struct clk_hw*) ; 
 struct clk_hw* clk_hw_get_parent_by_index (struct clk_hw*,int) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 struct clk_pix_rdi* to_clk_pix_rdi (struct clk_hw*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int pix_rdi_set_parent(struct clk_hw *hw, u8 index)
{
	int i;
	int ret = 0;
	u32 val;
	struct clk_pix_rdi *rdi = to_clk_pix_rdi(hw);
	int num_parents = clk_hw_get_num_parents(hw);

	/*
	 * These clocks select three inputs via two muxes. One mux selects
	 * between csi0 and csi1 and the second mux selects between that mux's
	 * output and csi2. The source and destination selections for each
	 * mux must be clocking for the switch to succeed so just turn on
	 * all three sources because it's easier than figuring out what source
	 * needs to be on at what time.
	 */
	for (i = 0; i < num_parents; i++) {
		struct clk_hw *p = clk_hw_get_parent_by_index(hw, i);
		ret = clk_prepare_enable(p->clk);
		if (ret)
			goto err;
	}

	if (index == 2)
		val = rdi->s2_mask;
	else
		val = 0;
	regmap_update_bits(rdi->clkr.regmap, rdi->s2_reg, rdi->s2_mask, val);
	/*
	 * Wait at least 6 cycles of slowest clock
	 * for the glitch-free MUX to fully switch sources.
	 */
	udelay(1);

	if (index == 1)
		val = rdi->s_mask;
	else
		val = 0;
	regmap_update_bits(rdi->clkr.regmap, rdi->s_reg, rdi->s_mask, val);
	/*
	 * Wait at least 6 cycles of slowest clock
	 * for the glitch-free MUX to fully switch sources.
	 */
	udelay(1);

err:
	for (i--; i >= 0; i--) {
		struct clk_hw *p = clk_hw_get_parent_by_index(hw, i);
		clk_disable_unprepare(p->clk);
	}

	return ret;
}