#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct wbsd_host {int flags; int /*<<< orphan*/  mmc; int /*<<< orphan*/  lock; int /*<<< orphan*/  finish_tasklet; TYPE_2__* mrq; scalar_t__ base; } ;
struct TYPE_4__ {TYPE_1__* cmd; } ;
struct TYPE_3__ {int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  ENOMEDIUM ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int WBSD_CARDPRESENT ; 
 scalar_t__ WBSD_CSR ; 
 int WBSD_FCARD_PRESENT ; 
 int WBSD_FIGNORE_DETECT ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  mmc_detect_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wbsd_reset (struct wbsd_host*) ; 

__attribute__((used)) static void wbsd_tasklet_card(unsigned long param)
{
	struct wbsd_host *host = (struct wbsd_host *)param;
	u8 csr;
	int delay = -1;

	spin_lock(&host->lock);

	if (host->flags & WBSD_FIGNORE_DETECT) {
		spin_unlock(&host->lock);
		return;
	}

	csr = inb(host->base + WBSD_CSR);
	WARN_ON(csr == 0xff);

	if (csr & WBSD_CARDPRESENT) {
		if (!(host->flags & WBSD_FCARD_PRESENT)) {
			DBG("Card inserted\n");
			host->flags |= WBSD_FCARD_PRESENT;

			delay = 500;
		}
	} else if (host->flags & WBSD_FCARD_PRESENT) {
		DBG("Card removed\n");
		host->flags &= ~WBSD_FCARD_PRESENT;

		if (host->mrq) {
			pr_err("%s: Card removed during transfer!\n",
				mmc_hostname(host->mmc));
			wbsd_reset(host);

			host->mrq->cmd->error = -ENOMEDIUM;
			tasklet_schedule(&host->finish_tasklet);
		}

		delay = 0;
	}

	/*
	 * Unlock first since we might get a call back.
	 */

	spin_unlock(&host->lock);

	if (delay != -1)
		mmc_detect_change(host->mmc, msecs_to_jiffies(delay));
}