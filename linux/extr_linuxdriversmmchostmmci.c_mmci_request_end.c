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
struct mmci_host {int /*<<< orphan*/  mmc; int /*<<< orphan*/ * cmd; int /*<<< orphan*/ * mrq; int /*<<< orphan*/  data; scalar_t__ base; } ;
struct mmc_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ MMCICOMMAND ; 
 int /*<<< orphan*/  mmc_request_done (int /*<<< orphan*/ ,struct mmc_request*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
mmci_request_end(struct mmci_host *host, struct mmc_request *mrq)
{
	writel(0, host->base + MMCICOMMAND);

	BUG_ON(host->data);

	host->mrq = NULL;
	host->cmd = NULL;

	mmc_request_done(host->mmc, mrq);
}