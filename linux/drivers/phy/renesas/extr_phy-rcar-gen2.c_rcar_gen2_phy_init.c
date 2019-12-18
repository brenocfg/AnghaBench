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
typedef  int /*<<< orphan*/  u32 ;
struct rcar_gen2_phy_driver {int /*<<< orphan*/  lock; scalar_t__ base; int /*<<< orphan*/  clk; } ;
struct rcar_gen2_phy {int /*<<< orphan*/  select_value; int /*<<< orphan*/  number; struct rcar_gen2_channel* channel; } ;
struct rcar_gen2_channel {int /*<<< orphan*/  select_mask; int /*<<< orphan*/  selected_phy; struct rcar_gen2_phy_driver* drv; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ USBHS_UGCTRL2 ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int cmpxchg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct rcar_gen2_phy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int rcar_gen2_phy_init(struct phy *p)
{
	struct rcar_gen2_phy *phy = phy_get_drvdata(p);
	struct rcar_gen2_channel *channel = phy->channel;
	struct rcar_gen2_phy_driver *drv = channel->drv;
	unsigned long flags;
	u32 ugctrl2;

	/*
	 * Try to acquire exclusive access to PHY.  The first driver calling
	 * phy_init()  on a given channel wins, and all attempts  to use another
	 * PHY on this channel will fail until phy_exit() is called by the first
	 * driver.   Achieving this with cmpxcgh() should be SMP-safe.
	 */
	if (cmpxchg(&channel->selected_phy, -1, phy->number) != -1)
		return -EBUSY;

	clk_prepare_enable(drv->clk);

	spin_lock_irqsave(&drv->lock, flags);
	ugctrl2 = readl(drv->base + USBHS_UGCTRL2);
	ugctrl2 &= ~channel->select_mask;
	ugctrl2 |= phy->select_value;
	writel(ugctrl2, drv->base + USBHS_UGCTRL2);
	spin_unlock_irqrestore(&drv->lock, flags);
	return 0;
}