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
struct mmc_host {int /*<<< orphan*/  ongoing_mrq; } ;

/* Variables and functions */
 struct mmc_request* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  completion_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void mmc_wait_ongoing_tfr_cmd(struct mmc_host *host)
{
	struct mmc_request *ongoing_mrq = READ_ONCE(host->ongoing_mrq);

	/*
	 * If there is an ongoing transfer, wait for the command line to become
	 * available.
	 */
	if (ongoing_mrq && !completion_done(&ongoing_mrq->cmd_completion))
		wait_for_completion(&ongoing_mrq->cmd_completion);
}