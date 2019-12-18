#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mmc_omap_slot {int saved_con; int /*<<< orphan*/  id; int /*<<< orphan*/ * mmc; struct mmc_omap_host* host; } ;
struct mmc_omap_host {struct mmc_omap_slot* current_slot; TYPE_1__* pdata; int /*<<< orphan*/  clk_timer; int /*<<< orphan*/  slot_lock; int /*<<< orphan*/ * mmc; int /*<<< orphan*/  slot_wq; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* switch_slot ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CON ; 
 int /*<<< orphan*/  OMAP_MMC_READ (struct mmc_omap_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OMAP_MMC_WRITE (struct mmc_omap_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_omap_fclk_enable (struct mmc_omap_host*,int) ; 
 int /*<<< orphan*/  mmc_omap_fclk_offdelay (struct mmc_omap_slot*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mmc_omap_select_slot(struct mmc_omap_slot *slot, int claimed)
{
	struct mmc_omap_host *host = slot->host;
	unsigned long flags;

	if (claimed)
		goto no_claim;
	spin_lock_irqsave(&host->slot_lock, flags);
	while (host->mmc != NULL) {
		spin_unlock_irqrestore(&host->slot_lock, flags);
		wait_event(host->slot_wq, host->mmc == NULL);
		spin_lock_irqsave(&host->slot_lock, flags);
	}
	host->mmc = slot->mmc;
	spin_unlock_irqrestore(&host->slot_lock, flags);
no_claim:
	del_timer(&host->clk_timer);
	if (host->current_slot != slot || !claimed)
		mmc_omap_fclk_offdelay(host->current_slot);

	if (host->current_slot != slot) {
		OMAP_MMC_WRITE(host, CON, slot->saved_con & 0xFC00);
		if (host->pdata->switch_slot != NULL)
			host->pdata->switch_slot(mmc_dev(slot->mmc), slot->id);
		host->current_slot = slot;
	}

	if (claimed) {
		mmc_omap_fclk_enable(host, 1);

		/* Doing the dummy read here seems to work around some bug
		 * at least in OMAP24xx silicon where the command would not
		 * start after writing the CMD register. Sigh. */
		OMAP_MMC_READ(host, CON);

		OMAP_MMC_WRITE(host, CON, slot->saved_con);
	} else
		mmc_omap_fclk_enable(host, 0);
}