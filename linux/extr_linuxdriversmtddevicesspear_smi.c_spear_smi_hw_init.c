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
struct spear_smi {int /*<<< orphan*/  lock; scalar_t__ io_base; int /*<<< orphan*/  clk_rate; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int BANK_EN ; 
 int DIV_ROUND_UP (unsigned long,int /*<<< orphan*/ ) ; 
 int DSEL_TIME ; 
 int HOLD1 ; 
 scalar_t__ SMI_CR1 ; 
 scalar_t__ SMI_SR ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void spear_smi_hw_init(struct spear_smi *dev)
{
	unsigned long rate = 0;
	u32 prescale = 0;
	u32 val;

	rate = clk_get_rate(dev->clk);

	/* functional clock of smi */
	prescale = DIV_ROUND_UP(rate, dev->clk_rate);

	/*
	 * setting the standard values, fast mode, prescaler for
	 * SMI_MAX_CLOCK_FREQ (50MHz) operation and bank enable
	 */
	val = HOLD1 | BANK_EN | DSEL_TIME | (prescale << 8);

	mutex_lock(&dev->lock);
	/* clear all interrupt conditions */
	writel(0, dev->io_base + SMI_SR);

	writel(val, dev->io_base + SMI_CR1);
	mutex_unlock(&dev->lock);
}