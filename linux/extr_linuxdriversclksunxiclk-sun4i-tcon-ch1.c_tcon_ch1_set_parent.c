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
typedef  int u8 ;
typedef  int u32 ;
struct tcon_ch1_clk {int /*<<< orphan*/  lock; int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int TCON_CH1_SCLK2_MUX_MASK ; 
 int TCON_CH1_SCLK2_MUX_SHIFT ; 
 struct tcon_ch1_clk* hw_to_tclk (struct clk_hw*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcon_ch1_set_parent(struct clk_hw *hw, u8 index)
{
	struct tcon_ch1_clk *tclk = hw_to_tclk(hw);
	unsigned long flags;
	u32 reg;

	spin_lock_irqsave(&tclk->lock, flags);
	reg = readl(tclk->reg);
	reg &= ~(TCON_CH1_SCLK2_MUX_MASK << TCON_CH1_SCLK2_MUX_SHIFT);
	reg |= index << TCON_CH1_SCLK2_MUX_SHIFT;
	writel(reg, tclk->reg);
	spin_unlock_irqrestore(&tclk->lock, flags);

	return 0;
}