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
typedef  int u32 ;
struct pic32_periph_clk {int /*<<< orphan*/  ctrl_reg; TYPE_1__* core; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (unsigned long,unsigned long) ; 
 int EBUSY ; 
 int /*<<< orphan*/  LOCK_TIMEOUT_US ; 
 int PB_DIV_MASK ; 
 int PB_DIV_READY ; 
 struct pic32_periph_clk* clkhw_to_pbclk (struct clk_hw*) ; 
 int pbclk_read_pbdiv (struct pic32_periph_clk*) ; 
 int /*<<< orphan*/  pic32_syskey_unlock () ; 
 int readl (int /*<<< orphan*/ ) ; 
 int readl_poll_timeout (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pbclk_set_rate(struct clk_hw *hw, unsigned long rate,
			  unsigned long parent_rate)
{
	struct pic32_periph_clk *pb = clkhw_to_pbclk(hw);
	unsigned long flags;
	u32 v, div;
	int err;

	/* check & wait for DIV_READY */
	err = readl_poll_timeout(pb->ctrl_reg, v, v & PB_DIV_READY,
				 1, LOCK_TIMEOUT_US);
	if (err)
		return err;

	/* calculate clkdiv and best rate */
	div = DIV_ROUND_CLOSEST(parent_rate, rate);

	spin_lock_irqsave(&pb->core->reg_lock, flags);

	/* apply new div */
	v = readl(pb->ctrl_reg);
	v &= ~PB_DIV_MASK;
	v |= (div - 1);

	pic32_syskey_unlock();

	writel(v, pb->ctrl_reg);

	spin_unlock_irqrestore(&pb->core->reg_lock, flags);

	/* wait again for DIV_READY */
	err = readl_poll_timeout(pb->ctrl_reg, v, v & PB_DIV_READY,
				 1, LOCK_TIMEOUT_US);
	if (err)
		return err;

	/* confirm that new div is applied correctly */
	return (pbclk_read_pbdiv(pb) == div) ? 0 : -EBUSY;
}