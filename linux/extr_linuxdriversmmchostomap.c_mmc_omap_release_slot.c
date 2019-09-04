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
struct mmc_omap_slot {int /*<<< orphan*/ * mmc; int /*<<< orphan*/ * mrq; struct mmc_omap_host* host; } ;
struct mmc_omap_host {int nr_slots; int /*<<< orphan*/  slot_lock; int /*<<< orphan*/  slot_wq; int /*<<< orphan*/ * mmc; int /*<<< orphan*/  slot_release_work; int /*<<< orphan*/  mmc_omap_wq; struct mmc_omap_slot* next_slot; struct mmc_omap_slot* current_slot; struct mmc_omap_slot** slots; int /*<<< orphan*/  clk_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int HZ ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mmc_omap_fclk_enable (struct mmc_omap_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_omap_fclk_offdelay (struct mmc_omap_slot*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mmc_omap_release_slot(struct mmc_omap_slot *slot, int clk_enabled)
{
	struct mmc_omap_host *host = slot->host;
	unsigned long flags;
	int i;

	BUG_ON(slot == NULL || host->mmc == NULL);

	if (clk_enabled)
		/* Keeps clock running for at least 8 cycles on valid freq */
		mod_timer(&host->clk_timer, jiffies  + HZ/10);
	else {
		del_timer(&host->clk_timer);
		mmc_omap_fclk_offdelay(slot);
		mmc_omap_fclk_enable(host, 0);
	}

	spin_lock_irqsave(&host->slot_lock, flags);
	/* Check for any pending requests */
	for (i = 0; i < host->nr_slots; i++) {
		struct mmc_omap_slot *new_slot;

		if (host->slots[i] == NULL || host->slots[i]->mrq == NULL)
			continue;

		BUG_ON(host->next_slot != NULL);
		new_slot = host->slots[i];
		/* The current slot should not have a request in queue */
		BUG_ON(new_slot == host->current_slot);

		host->next_slot = new_slot;
		host->mmc = new_slot->mmc;
		spin_unlock_irqrestore(&host->slot_lock, flags);
		queue_work(host->mmc_omap_wq, &host->slot_release_work);
		return;
	}

	host->mmc = NULL;
	wake_up(&host->slot_wq);
	spin_unlock_irqrestore(&host->slot_lock, flags);
}