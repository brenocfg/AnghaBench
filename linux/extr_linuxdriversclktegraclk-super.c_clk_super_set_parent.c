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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct tegra_clk_super_mux {int flags; scalar_t__ div2_index; scalar_t__ pllx_index; scalar_t__ lock; int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 scalar_t__ SUPER_LP_DIV2_BYPASS ; 
 int /*<<< orphan*/  SUPER_STATE_IDLE ; 
 scalar_t__ SUPER_STATE_MASK ; 
 int /*<<< orphan*/  SUPER_STATE_RUN ; 
 int TEGRA_DIVIDER_2 ; 
 scalar_t__ clk_super_get_parent (struct clk_hw*) ; 
 scalar_t__ readl_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (scalar_t__,unsigned long) ; 
 scalar_t__ super_state (int /*<<< orphan*/ ) ; 
 scalar_t__ super_state_to_src_mask (struct tegra_clk_super_mux*) ; 
 scalar_t__ super_state_to_src_shift (struct tegra_clk_super_mux*,int /*<<< orphan*/ ) ; 
 struct tegra_clk_super_mux* to_clk_super_mux (struct clk_hw*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel_relaxed (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clk_super_set_parent(struct clk_hw *hw, u8 index)
{
	struct tegra_clk_super_mux *mux = to_clk_super_mux(hw);
	u32 val, state;
	int err = 0;
	u8 parent_index, shift;
	unsigned long flags = 0;

	if (mux->lock)
		spin_lock_irqsave(mux->lock, flags);

	val = readl_relaxed(mux->reg);
	state = val & SUPER_STATE_MASK;
	BUG_ON((state != super_state(SUPER_STATE_RUN)) &&
	       (state != super_state(SUPER_STATE_IDLE)));
	shift = (state == super_state(SUPER_STATE_IDLE)) ?
		super_state_to_src_shift(mux, SUPER_STATE_IDLE) :
		super_state_to_src_shift(mux, SUPER_STATE_RUN);

	/*
	 * For LP mode super-clock switch between PLLX direct
	 * and divided-by-2 outputs is allowed only when other
	 * than PLLX clock source is current parent.
	 */
	if ((mux->flags & TEGRA_DIVIDER_2) && ((index == mux->div2_index) ||
					       (index == mux->pllx_index))) {
		parent_index = clk_super_get_parent(hw);
		if ((parent_index == mux->div2_index) ||
		    (parent_index == mux->pllx_index)) {
			err = -EINVAL;
			goto out;
		}

		val ^= SUPER_LP_DIV2_BYPASS;
		writel_relaxed(val, mux->reg);
		udelay(2);

		if (index == mux->div2_index)
			index = mux->pllx_index;
	}
	val &= ~((super_state_to_src_mask(mux)) << shift);
	val |= (index & (super_state_to_src_mask(mux))) << shift;

	writel_relaxed(val, mux->reg);
	udelay(2);

out:
	if (mux->lock)
		spin_unlock_irqrestore(mux->lock, flags);

	return err;
}