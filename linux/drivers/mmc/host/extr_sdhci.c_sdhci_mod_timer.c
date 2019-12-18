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
struct sdhci_host {int /*<<< orphan*/  timer; int /*<<< orphan*/  data_timer; } ;
struct mmc_request {int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ sdhci_data_line_cmd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdhci_mod_timer(struct sdhci_host *host, struct mmc_request *mrq,
			    unsigned long timeout)
{
	if (sdhci_data_line_cmd(mrq->cmd))
		mod_timer(&host->data_timer, timeout);
	else
		mod_timer(&host->timer, timeout);
}