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
typedef  int /*<<< orphan*/  u_long ;
struct w6692_hw {int /*<<< orphan*/  irq; int /*<<< orphan*/  name; int /*<<< orphan*/  irqcnt; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int DEBUG_HW ; 
 int EIO ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int debug ; 
 int /*<<< orphan*/  disable_hwirq (struct w6692_hw*) ; 
 int /*<<< orphan*/  enable_hwirq (struct w6692_hw*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct w6692_hw*) ; 
 int /*<<< orphan*/  initW6692 (struct w6692_hw*) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct w6692_hw*) ; 
 int /*<<< orphan*/  reset_w6692 (struct w6692_hw*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w6692_irq ; 

__attribute__((used)) static int
init_card(struct w6692_hw *card)
{
	int	cnt = 3;
	u_long	flags;

	spin_lock_irqsave(&card->lock, flags);
	disable_hwirq(card);
	spin_unlock_irqrestore(&card->lock, flags);
	if (request_irq(card->irq, w6692_irq, IRQF_SHARED, card->name, card)) {
		pr_info("%s: couldn't get interrupt %d\n", card->name,
			card->irq);
		return -EIO;
	}
	while (cnt--) {
		spin_lock_irqsave(&card->lock, flags);
		initW6692(card);
		enable_hwirq(card);
		spin_unlock_irqrestore(&card->lock, flags);
		/* Timeout 10ms */
		msleep_interruptible(10);
		if (debug & DEBUG_HW)
			pr_notice("%s: IRQ %d count %d\n", card->name,
				  card->irq, card->irqcnt);
		if (!card->irqcnt) {
			pr_info("%s: IRQ(%d) getting no IRQs during init %d\n",
				card->name, card->irq, 3 - cnt);
			reset_w6692(card);
		} else
			return 0;
	}
	free_irq(card->irq, card);
	return -EIO;
}