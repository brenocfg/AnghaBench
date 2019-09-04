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
typedef  int u16 ;
struct usdhi6_host {int status_mask; struct mmc_host* mmc; } ;
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct mmc_host {scalar_t__ card; TYPE_1__ detect; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  USDHI6_SD_INFO1 ; 
 int USDHI6_SD_INFO1_CARD ; 
 int USDHI6_SD_INFO1_CARD_EJECT ; 
 int USDHI6_SD_INFO1_CARD_INSERT ; 
 int /*<<< orphan*/  mmc_detect_change (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int usdhi6_read (struct usdhi6_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usdhi6_write (struct usdhi6_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  work_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t usdhi6_cd(int irq, void *dev_id)
{
	struct usdhi6_host *host = dev_id;
	struct mmc_host *mmc = host->mmc;
	u16 status;

	/* We're only interested in hotplug events here */
	status = usdhi6_read(host, USDHI6_SD_INFO1) & ~host->status_mask &
		USDHI6_SD_INFO1_CARD;

	if (!status)
		return IRQ_NONE;

	/* Ack */
	usdhi6_write(host, USDHI6_SD_INFO1, ~status);

	if (!work_pending(&mmc->detect.work) &&
	    (((status & USDHI6_SD_INFO1_CARD_INSERT) &&
	      !mmc->card) ||
	     ((status & USDHI6_SD_INFO1_CARD_EJECT) &&
	      mmc->card)))
		mmc_detect_change(mmc, msecs_to_jiffies(100));

	return IRQ_HANDLED;
}