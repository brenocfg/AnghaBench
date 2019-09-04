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
struct ti_adpll_data {int /*<<< orphan*/  lock; scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADPLL_CLKCTRL_IDLE ; 
 scalar_t__ ADPLL_CLKCTRL_OFFSET ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ti_adpll_set_idle_bypass(struct ti_adpll_data *d)
{
	unsigned long flags;
	u32 v;

	spin_lock_irqsave(&d->lock, flags);
	v = readl_relaxed(d->regs + ADPLL_CLKCTRL_OFFSET);
	v |= BIT(ADPLL_CLKCTRL_IDLE);
	writel_relaxed(v, d->regs + ADPLL_CLKCTRL_OFFSET);
	spin_unlock_irqrestore(&d->lock, flags);
}