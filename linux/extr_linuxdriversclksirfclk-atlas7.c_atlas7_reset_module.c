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
struct reset_controller_dev {int dummy; } ;
struct atlas7_reset_desc {int clk_bit; int rst_bit; int /*<<< orphan*/  lock; scalar_t__ rst_ofs; scalar_t__ clk_ofs; } ;

/* Variables and functions */
 struct atlas7_reset_desc* atlas7_reset_unit ; 
 int clkc_readl (scalar_t__) ; 
 int /*<<< orphan*/  clkc_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int atlas7_reset_module(struct reset_controller_dev *rcdev,
					unsigned long reset_idx)
{
	struct atlas7_reset_desc *reset = &atlas7_reset_unit[reset_idx];
	unsigned long flags;

	/*
	 * HW suggest unit reset sequence:
	 * assert sw reset (0)
	 * setting sw clk_en to if the clock was disabled before reset
	 * delay 16 clocks
	 * disable clock (sw clk_en = 0)
	 * de-assert reset (1)
	 * after this sequence, restore clock or not is decided by SW
	 */

	spin_lock_irqsave(reset->lock, flags);
	/* clock enable or not */
	if (clkc_readl(reset->clk_ofs + 8) & (1 << reset->clk_bit)) {
		clkc_writel(1 << reset->rst_bit, reset->rst_ofs + 4);
		udelay(2);
		clkc_writel(1 << reset->clk_bit, reset->clk_ofs + 4);
		clkc_writel(1 << reset->rst_bit, reset->rst_ofs);
		/* restore clock enable */
		clkc_writel(1 << reset->clk_bit, reset->clk_ofs);
	} else {
		clkc_writel(1 << reset->rst_bit, reset->rst_ofs + 4);
		clkc_writel(1 << reset->clk_bit, reset->clk_ofs);
		udelay(2);
		clkc_writel(1 << reset->clk_bit, reset->clk_ofs + 4);
		clkc_writel(1 << reset->rst_bit, reset->rst_ofs);
	}
	spin_unlock_irqrestore(reset->lock, flags);

	return 0;
}