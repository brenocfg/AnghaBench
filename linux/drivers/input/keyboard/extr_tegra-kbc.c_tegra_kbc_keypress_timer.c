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
struct timer_list {int dummy; } ;
struct tegra_kbc {int repoll_dly; unsigned int num_pressed_keys; int /*<<< orphan*/  lock; int /*<<< orphan*/  idev; int /*<<< orphan*/ * current_keys; int /*<<< orphan*/  timer; scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ KBC_INT_0 ; 
 struct tegra_kbc* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 struct tegra_kbc* kbc ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (unsigned long) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tegra_kbc_report_keys (struct tegra_kbc*) ; 
 int /*<<< orphan*/  tegra_kbc_set_fifo_interrupt (struct tegra_kbc*,int) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void tegra_kbc_keypress_timer(struct timer_list *t)
{
	struct tegra_kbc *kbc = from_timer(kbc, t, timer);
	unsigned long flags;
	u32 val;
	unsigned int i;

	spin_lock_irqsave(&kbc->lock, flags);

	val = (readl(kbc->mmio + KBC_INT_0) >> 4) & 0xf;
	if (val) {
		unsigned long dly;

		tegra_kbc_report_keys(kbc);

		/*
		 * If more than one keys are pressed we need not wait
		 * for the repoll delay.
		 */
		dly = (val == 1) ? kbc->repoll_dly : 1;
		mod_timer(&kbc->timer, jiffies + msecs_to_jiffies(dly));
	} else {
		/* Release any pressed keys and exit the polling loop */
		for (i = 0; i < kbc->num_pressed_keys; i++)
			input_report_key(kbc->idev, kbc->current_keys[i], 0);
		input_sync(kbc->idev);

		kbc->num_pressed_keys = 0;

		/* All keys are released so enable the keypress interrupt */
		tegra_kbc_set_fifo_interrupt(kbc, true);
	}

	spin_unlock_irqrestore(&kbc->lock, flags);
}