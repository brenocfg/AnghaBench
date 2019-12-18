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
struct timer_list {int dummy; } ;
struct sdhci_host {int /*<<< orphan*/  lock; TYPE_1__* cmd; int /*<<< orphan*/  mmc; } ;
struct TYPE_2__ {int /*<<< orphan*/  mrq; int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETIMEDOUT ; 
 struct sdhci_host* from_timer (struct sdhci_host*,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_data_line_cmd (TYPE_1__*) ; 
 int /*<<< orphan*/  sdhci_dumpregs (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_finish_mrq (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void sdhci_timeout_timer(struct timer_list *t)
{
	struct sdhci_host *host;
	unsigned long flags;

	host = from_timer(host, t, timer);

	spin_lock_irqsave(&host->lock, flags);

	if (host->cmd && !sdhci_data_line_cmd(host->cmd)) {
		pr_err("%s: Timeout waiting for hardware cmd interrupt.\n",
		       mmc_hostname(host->mmc));
		sdhci_dumpregs(host);

		host->cmd->error = -ETIMEDOUT;
		sdhci_finish_mrq(host, host->cmd->mrq);
	}

	spin_unlock_irqrestore(&host->lock, flags);
}