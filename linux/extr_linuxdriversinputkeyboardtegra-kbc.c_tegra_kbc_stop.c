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
typedef  int u32 ;
struct tegra_kbc {int /*<<< orphan*/  clk; int /*<<< orphan*/  timer; int /*<<< orphan*/  irq; int /*<<< orphan*/  lock; scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ KBC_CONTROL_0 ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void tegra_kbc_stop(struct tegra_kbc *kbc)
{
	unsigned long flags;
	u32 val;

	spin_lock_irqsave(&kbc->lock, flags);
	val = readl(kbc->mmio + KBC_CONTROL_0);
	val &= ~1;
	writel(val, kbc->mmio + KBC_CONTROL_0);
	spin_unlock_irqrestore(&kbc->lock, flags);

	disable_irq(kbc->irq);
	del_timer_sync(&kbc->timer);

	clk_disable_unprepare(kbc->clk);
}