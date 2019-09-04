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

/* Variables and functions */
 int /*<<< orphan*/  bcm_perf_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_perf_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_mutex ; 
 int /*<<< orphan*/  reset_reg ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void __bcm63xx_core_set_reset(u32 mask, int enable)
{
	unsigned long flags;
	u32 val;

	if (!mask)
		return;

	spin_lock_irqsave(&reset_mutex, flags);
	val = bcm_perf_readl(reset_reg);

	if (enable)
		val &= ~mask;
	else
		val |= mask;

	bcm_perf_writel(val, reset_reg);
	spin_unlock_irqrestore(&reset_mutex, flags);
}