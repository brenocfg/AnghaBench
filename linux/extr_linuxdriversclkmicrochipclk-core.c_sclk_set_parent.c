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
typedef  size_t u8 ;
typedef  int u32 ;
struct pic32_sys_clk {size_t* parent_map; int /*<<< orphan*/  mux_reg; TYPE_1__* core; int /*<<< orphan*/  slew_reg; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  LOCK_TIMEOUT_US ; 
 int OSC_CUR_MASK ; 
 int OSC_CUR_SHIFT ; 
 int OSC_NEW_MASK ; 
 int OSC_NEW_SHIFT ; 
 int OSC_SWEN ; 
 int /*<<< orphan*/  PIC32_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_hw_get_name (struct clk_hw*) ; 
 struct pic32_sys_clk* clkhw_to_sys_clk (struct clk_hw*) ; 
 int /*<<< orphan*/  cpu_nop5 () ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  pic32_syskey_unlock () ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int,int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int readl_poll_timeout_atomic (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sclk_set_parent(struct clk_hw *hw, u8 index)
{
	struct pic32_sys_clk *sclk = clkhw_to_sys_clk(hw);
	unsigned long flags;
	u32 nosc, cosc, v;
	int err;

	spin_lock_irqsave(&sclk->core->reg_lock, flags);

	/* find new_osc */
	nosc = sclk->parent_map ? sclk->parent_map[index] : index;

	/* set new parent */
	v = readl(sclk->mux_reg);
	v &= ~(OSC_NEW_MASK << OSC_NEW_SHIFT);
	v |= nosc << OSC_NEW_SHIFT;

	pic32_syskey_unlock();

	writel(v, sclk->mux_reg);

	/* initate switch */
	writel(OSC_SWEN, PIC32_SET(sclk->mux_reg));
	cpu_relax();

	/* add nop to flush pipeline (as cpu_clk is in-flux) */
	cpu_nop5();

	/* wait for SWEN bit to clear */
	err = readl_poll_timeout_atomic(sclk->slew_reg, v,
					!(v & OSC_SWEN), 1, LOCK_TIMEOUT_US);

	spin_unlock_irqrestore(&sclk->core->reg_lock, flags);

	/*
	 * SCLK clock-switching logic might reject a clock switching request
	 * if pre-requisites (like new clk_src not present or unstable) are
	 * not met.
	 * So confirm before claiming success.
	 */
	cosc = (readl(sclk->mux_reg) >> OSC_CUR_SHIFT) & OSC_CUR_MASK;
	if (cosc != nosc) {
		pr_err("%s: err, failed to set_parent() to %d, current %d\n",
		       clk_hw_get_name(hw), nosc, cosc);
		err = -EBUSY;
	}

	return err;
}