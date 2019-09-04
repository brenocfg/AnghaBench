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
struct mmc_request {int /*<<< orphan*/  recovery_notifier; int /*<<< orphan*/  done; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_blk_cqe_req_done ; 
 int /*<<< orphan*/  mmc_cqe_recovery_notifier ; 
 int mmc_cqe_start_req (struct mmc_host*,struct mmc_request*) ; 

__attribute__((used)) static int mmc_blk_cqe_start_req(struct mmc_host *host, struct mmc_request *mrq)
{
	mrq->done		= mmc_blk_cqe_req_done;
	mrq->recovery_notifier	= mmc_cqe_recovery_notifier;

	return mmc_cqe_start_req(host, mrq);
}