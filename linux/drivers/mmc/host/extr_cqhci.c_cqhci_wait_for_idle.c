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
struct mmc_host {struct cqhci_host* cqe_private; } ;
struct cqhci_host {int /*<<< orphan*/  wait_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  cqhci_is_idle (struct cqhci_host*,int*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cqhci_wait_for_idle(struct mmc_host *mmc)
{
	struct cqhci_host *cq_host = mmc->cqe_private;
	int ret;

	wait_event(cq_host->wait_queue, cqhci_is_idle(cq_host, &ret));

	return ret;
}