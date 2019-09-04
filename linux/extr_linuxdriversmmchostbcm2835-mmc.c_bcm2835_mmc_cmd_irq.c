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
struct bcm2835_host {int /*<<< orphan*/  finish_tasklet; TYPE_1__* cmd; int /*<<< orphan*/  mmc; } ;
struct TYPE_2__ {int error; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EILSEQ ; 
 int ETIMEDOUT ; 
 int SDHCI_INT_CRC ; 
 int SDHCI_INT_END_BIT ; 
 int SDHCI_INT_INDEX ; 
 int SDHCI_INT_RESPONSE ; 
 int SDHCI_INT_TIMEOUT ; 
 int /*<<< orphan*/  bcm2835_mmc_dumpregs (struct bcm2835_host*) ; 
 int /*<<< orphan*/  bcm2835_mmc_finish_command (struct bcm2835_host*) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bcm2835_mmc_cmd_irq(struct bcm2835_host *host, u32 intmask)
{

	BUG_ON(intmask == 0);

	if (!host->cmd) {
		pr_err("%s: Got command interrupt 0x%08x even "
			"though no command operation was in progress.\n",
			mmc_hostname(host->mmc), (unsigned)intmask);
		bcm2835_mmc_dumpregs(host);
		return;
	}

	if (intmask & SDHCI_INT_TIMEOUT)
		host->cmd->error = -ETIMEDOUT;
	else if (intmask & (SDHCI_INT_CRC | SDHCI_INT_END_BIT |
			SDHCI_INT_INDEX)) {
			host->cmd->error = -EILSEQ;
	}

	if (host->cmd->error) {
		tasklet_schedule(&host->finish_tasklet);
		return;
	}

	if (intmask & SDHCI_INT_RESPONSE)
		bcm2835_mmc_finish_command(host);

}