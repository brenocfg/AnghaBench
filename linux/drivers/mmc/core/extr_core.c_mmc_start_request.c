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
struct mmc_request {int /*<<< orphan*/  cmd_completion; } ;
struct mmc_host {int /*<<< orphan*/  led; int /*<<< orphan*/  claimed; int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int ENOMEDIUM ; 
 int /*<<< orphan*/  LED_FULL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __mmc_start_request (struct mmc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  led_trigger_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mmc_card_removed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_mrq_pr_debug (struct mmc_host*,struct mmc_request*,int) ; 
 int mmc_mrq_prep (struct mmc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  mmc_retune_hold (struct mmc_host*) ; 

int mmc_start_request(struct mmc_host *host, struct mmc_request *mrq)
{
	int err;

	init_completion(&mrq->cmd_completion);

	mmc_retune_hold(host);

	if (mmc_card_removed(host->card))
		return -ENOMEDIUM;

	mmc_mrq_pr_debug(host, mrq, false);

	WARN_ON(!host->claimed);

	err = mmc_mrq_prep(host, mrq);
	if (err)
		return err;

	led_trigger_event(host->led, LED_FULL);
	__mmc_start_request(host, mrq);

	return 0;
}