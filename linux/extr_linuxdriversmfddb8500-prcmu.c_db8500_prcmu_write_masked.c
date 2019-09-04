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

/* Variables and functions */
 scalar_t__ prcmu_base ; 
 int /*<<< orphan*/  prcmu_lock ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void db8500_prcmu_write_masked(unsigned int reg, u32 mask, u32 value)
{
	u32 val;
	unsigned long flags;

	spin_lock_irqsave(&prcmu_lock, flags);
	val = readl(prcmu_base + reg);
	val = ((val & ~mask) | (value & mask));
	writel(val, (prcmu_base + reg));
	spin_unlock_irqrestore(&prcmu_lock, flags);
}