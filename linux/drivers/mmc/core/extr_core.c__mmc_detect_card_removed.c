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
struct mmc_host {int /*<<< orphan*/  card; TYPE_2__* ops; TYPE_1__* bus_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_cd ) (struct mmc_host*) ;} ;
struct TYPE_3__ {int (* alive ) (struct mmc_host*) ;} ;

/* Variables and functions */
 scalar_t__ mmc_card_removed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_card_set_removed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_detect_change (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int stub1 (struct mmc_host*) ; 
 int /*<<< orphan*/  stub2 (struct mmc_host*) ; 

int _mmc_detect_card_removed(struct mmc_host *host)
{
	int ret;

	if (!host->card || mmc_card_removed(host->card))
		return 1;

	ret = host->bus_ops->alive(host);

	/*
	 * Card detect status and alive check may be out of sync if card is
	 * removed slowly, when card detect switch changes while card/slot
	 * pads are still contacted in hardware (refer to "SD Card Mechanical
	 * Addendum, Appendix C: Card Detection Switch"). So reschedule a
	 * detect work 200ms later for this case.
	 */
	if (!ret && host->ops->get_cd && !host->ops->get_cd(host)) {
		mmc_detect_change(host, msecs_to_jiffies(200));
		pr_debug("%s: card removed too slowly\n", mmc_hostname(host));
	}

	if (ret) {
		mmc_card_set_removed(host->card);
		pr_debug("%s: card remove detected\n", mmc_hostname(host));
	}

	return ret;
}