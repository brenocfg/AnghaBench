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
struct sm501_devdata {int /*<<< orphan*/  reg_lock; scalar_t__ regs; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct sm501_devdata* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sm501_sync_regs (struct sm501_devdata*) ; 
 unsigned long smc501_readl (scalar_t__) ; 
 int /*<<< orphan*/  smc501_writel (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

unsigned long sm501_modify_reg(struct device *dev,
			       unsigned long reg,
			       unsigned long set,
			       unsigned long clear)
{
	struct sm501_devdata *sm = dev_get_drvdata(dev);
	unsigned long data;
	unsigned long save;

	spin_lock_irqsave(&sm->reg_lock, save);

	data = smc501_readl(sm->regs + reg);
	data |= set;
	data &= ~clear;

	smc501_writel(data, sm->regs + reg);
	sm501_sync_regs(sm);

	spin_unlock_irqrestore(&sm->reg_lock, save);

	return data;
}