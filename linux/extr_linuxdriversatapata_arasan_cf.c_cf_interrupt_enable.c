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
struct arasan_cf_dev {scalar_t__ vbase; } ;

/* Variables and functions */
 scalar_t__ IRQ_EN ; 
 scalar_t__ IRQ_STS ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static inline void
cf_interrupt_enable(struct arasan_cf_dev *acdev, u32 mask, bool enable)
{
	u32 val = readl(acdev->vbase + IRQ_EN);
	/* clear & enable/disable irqs */
	if (enable) {
		writel(mask, acdev->vbase + IRQ_STS);
		writel(val | mask, acdev->vbase + IRQ_EN);
	} else
		writel(val & ~mask, acdev->vbase + IRQ_EN);
}