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
typedef  int u32 ;
struct mmc_request {TYPE_1__* cmd; } ;
struct mmc_host {int dummy; } ;
struct mmc_davinci_host {scalar_t__ do_dma; int /*<<< orphan*/  mmc; scalar_t__ base; } ;
struct TYPE_2__ {int /*<<< orphan*/  error; } ;

/* Variables and functions */
 scalar_t__ DAVINCI_MMCST1 ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int MMCST1_BUSY ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mmc_davinci_prepare_data (struct mmc_davinci_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  mmc_davinci_start_command (struct mmc_davinci_host*,TYPE_1__*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 struct mmc_davinci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_request_done (struct mmc_host*,struct mmc_request*) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int readl (scalar_t__) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static void mmc_davinci_request(struct mmc_host *mmc, struct mmc_request *req)
{
	struct mmc_davinci_host *host = mmc_priv(mmc);
	unsigned long timeout = jiffies + msecs_to_jiffies(900);
	u32 mmcst1 = 0;

	/* Card may still be sending BUSY after a previous operation,
	 * typically some kind of write.  If so, we can't proceed yet.
	 */
	while (time_before(jiffies, timeout)) {
		mmcst1  = readl(host->base + DAVINCI_MMCST1);
		if (!(mmcst1 & MMCST1_BUSY))
			break;
		cpu_relax();
	}
	if (mmcst1 & MMCST1_BUSY) {
		dev_err(mmc_dev(host->mmc), "still BUSY? bad ... \n");
		req->cmd->error = -ETIMEDOUT;
		mmc_request_done(mmc, req);
		return;
	}

	host->do_dma = 0;
	mmc_davinci_prepare_data(host, req);
	mmc_davinci_start_command(host, req->cmd);
}