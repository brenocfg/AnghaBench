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
struct clk_hw {int dummy; } ;
struct clk_apbc {int flags; scalar_t__ lock; int /*<<< orphan*/  base; int /*<<< orphan*/  delay; } ;

/* Variables and functions */
 unsigned int APBC_APBCLK ; 
 unsigned int APBC_FNCLK ; 
 int APBC_NO_BUS_CTRL ; 
 unsigned int APBC_POWER ; 
 int APBC_POWER_CTRL ; 
 unsigned int APBC_RST ; 
 unsigned int readl_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (scalar_t__,unsigned long) ; 
 struct clk_apbc* to_clk_apbc (struct clk_hw*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clk_apbc_prepare(struct clk_hw *hw)
{
	struct clk_apbc *apbc = to_clk_apbc(hw);
	unsigned int data;
	unsigned long flags = 0;

	/*
	 * It may share same register as MUX clock,
	 * and it will impact FNCLK enable. Spinlock is needed
	 */
	if (apbc->lock)
		spin_lock_irqsave(apbc->lock, flags);

	data = readl_relaxed(apbc->base);
	if (apbc->flags & APBC_POWER_CTRL)
		data |= APBC_POWER;
	data |= APBC_FNCLK;
	writel_relaxed(data, apbc->base);

	if (apbc->lock)
		spin_unlock_irqrestore(apbc->lock, flags);

	udelay(apbc->delay);

	if (apbc->lock)
		spin_lock_irqsave(apbc->lock, flags);

	data = readl_relaxed(apbc->base);
	data |= APBC_APBCLK;
	writel_relaxed(data, apbc->base);

	if (apbc->lock)
		spin_unlock_irqrestore(apbc->lock, flags);

	udelay(apbc->delay);

	if (!(apbc->flags & APBC_NO_BUS_CTRL)) {
		if (apbc->lock)
			spin_lock_irqsave(apbc->lock, flags);

		data = readl_relaxed(apbc->base);
		data &= ~APBC_RST;
		writel_relaxed(data, apbc->base);

		if (apbc->lock)
			spin_unlock_irqrestore(apbc->lock, flags);
	}

	return 0;
}