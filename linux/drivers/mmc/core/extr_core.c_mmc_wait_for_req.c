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
struct mmc_request {int /*<<< orphan*/  cap_cmd_during_tfr; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mmc_start_req (struct mmc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  mmc_wait_for_req_done (struct mmc_host*,struct mmc_request*) ; 

void mmc_wait_for_req(struct mmc_host *host, struct mmc_request *mrq)
{
	__mmc_start_req(host, mrq);

	if (!mrq->cap_cmd_during_tfr)
		mmc_wait_for_req_done(host, mrq);
}