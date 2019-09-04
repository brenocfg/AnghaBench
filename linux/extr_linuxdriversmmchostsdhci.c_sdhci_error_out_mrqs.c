#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sdhci_host {TYPE_2__* cmd; TYPE_1__* data_cmd; } ;
struct TYPE_4__ {int error; int /*<<< orphan*/  mrq; } ;
struct TYPE_3__ {int error; int /*<<< orphan*/  mrq; } ;

/* Variables and functions */
 int /*<<< orphan*/  sdhci_finish_mrq (struct sdhci_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdhci_error_out_mrqs(struct sdhci_host *host, int err)
{
	if (host->data_cmd) {
		host->data_cmd->error = err;
		sdhci_finish_mrq(host, host->data_cmd->mrq);
	}

	if (host->cmd) {
		host->cmd->error = err;
		sdhci_finish_mrq(host, host->cmd->mrq);
	}
}