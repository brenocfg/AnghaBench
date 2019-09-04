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
struct tegra_kbc {int keypress_caused_wake; int /*<<< orphan*/  lock; scalar_t__ cp_dly_jiffies; int /*<<< orphan*/  timer; scalar_t__ mmio; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ KBC_INT_0 ; 
 int KBC_INT_FIFO_CNT_INT_STATUS ; 
 int KBC_INT_KEYPRESS_INT_STATUS ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tegra_kbc_set_fifo_interrupt (struct tegra_kbc*,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t tegra_kbc_isr(int irq, void *args)
{
	struct tegra_kbc *kbc = args;
	unsigned long flags;
	u32 val;

	spin_lock_irqsave(&kbc->lock, flags);

	/*
	 * Quickly bail out & reenable interrupts if the fifo threshold
	 * count interrupt wasn't the interrupt source
	 */
	val = readl(kbc->mmio + KBC_INT_0);
	writel(val, kbc->mmio + KBC_INT_0);

	if (val & KBC_INT_FIFO_CNT_INT_STATUS) {
		/*
		 * Until all keys are released, defer further processing to
		 * the polling loop in tegra_kbc_keypress_timer.
		 */
		tegra_kbc_set_fifo_interrupt(kbc, false);
		mod_timer(&kbc->timer, jiffies + kbc->cp_dly_jiffies);
	} else if (val & KBC_INT_KEYPRESS_INT_STATUS) {
		/* We can be here only through system resume path */
		kbc->keypress_caused_wake = true;
	}

	spin_unlock_irqrestore(&kbc->lock, flags);

	return IRQ_HANDLED;
}