#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct tegra_thermctl_zone {TYPE_1__* ts; TYPE_2__* sg; } ;
struct TYPE_4__ {int /*<<< orphan*/  thermctl_isr_mask; } ;
struct TYPE_3__ {int /*<<< orphan*/  thermctl_lock; scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SET_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ THERMCTL_INTR_DISABLE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void thermal_irq_disable(struct tegra_thermctl_zone *zn)
{
	u32 r;

	/* multiple zones could be handling and setting trips at once */
	mutex_lock(&zn->ts->thermctl_lock);
	r = readl(zn->ts->regs + THERMCTL_INTR_DISABLE);
	r = REG_SET_MASK(r, zn->sg->thermctl_isr_mask, 0);
	writel(r, zn->ts->regs + THERMCTL_INTR_DISABLE);
	mutex_unlock(&zn->ts->thermctl_lock);
}