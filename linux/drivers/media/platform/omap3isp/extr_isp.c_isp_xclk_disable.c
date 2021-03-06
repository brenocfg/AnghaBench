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
struct isp_xclk {int enabled; int /*<<< orphan*/  lock; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  isp_xclk_update (struct isp_xclk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct isp_xclk* to_isp_xclk (struct clk_hw*) ; 

__attribute__((used)) static void isp_xclk_disable(struct clk_hw *hw)
{
	struct isp_xclk *xclk = to_isp_xclk(hw);
	unsigned long flags;

	spin_lock_irqsave(&xclk->lock, flags);
	isp_xclk_update(xclk, 0);
	xclk->enabled = false;
	spin_unlock_irqrestore(&xclk->lock, flags);
}