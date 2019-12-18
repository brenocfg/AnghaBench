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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct sdhci_host {int tuning_loop_count; scalar_t__ tuning_delay; int /*<<< orphan*/  mmc; int /*<<< orphan*/  tuning_done; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ETIMEDOUT ; 
 int SDHCI_CTRL_EXEC_TUNING ; 
 int SDHCI_CTRL_TUNED_CLK ; 
 int /*<<< orphan*/  SDHCI_HOST_CONTROL2 ; 
 int /*<<< orphan*/  mdelay (scalar_t__) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_abort_tuning (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int sdhci_readw (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_reset_tuning (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_send_tuning (struct sdhci_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __sdhci_execute_tuning(struct sdhci_host *host, u32 opcode)
{
	int i;

	/*
	 * Issue opcode repeatedly till Execute Tuning is set to 0 or the number
	 * of loops reaches tuning loop count.
	 */
	for (i = 0; i < host->tuning_loop_count; i++) {
		u16 ctrl;

		sdhci_send_tuning(host, opcode);

		if (!host->tuning_done) {
			pr_info("%s: Tuning timeout, falling back to fixed sampling clock\n",
				mmc_hostname(host->mmc));
			sdhci_abort_tuning(host, opcode);
			return -ETIMEDOUT;
		}

		/* Spec does not require a delay between tuning cycles */
		if (host->tuning_delay > 0)
			mdelay(host->tuning_delay);

		ctrl = sdhci_readw(host, SDHCI_HOST_CONTROL2);
		if (!(ctrl & SDHCI_CTRL_EXEC_TUNING)) {
			if (ctrl & SDHCI_CTRL_TUNED_CLK)
				return 0; /* Success! */
			break;
		}

	}

	pr_info("%s: Tuning failed, falling back to fixed sampling clock\n",
		mmc_hostname(host->mmc));
	sdhci_reset_tuning(host);
	return -EAGAIN;
}