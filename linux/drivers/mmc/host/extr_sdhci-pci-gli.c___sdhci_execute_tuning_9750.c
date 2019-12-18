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
struct sdhci_host {int /*<<< orphan*/  mmc; int /*<<< orphan*/  tuning_done; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ETIMEDOUT ; 
 int GLI_MAX_TUNING_LOOP ; 
 int SDHCI_CTRL_EXEC_TUNING ; 
 int SDHCI_CTRL_TUNED_CLK ; 
 int /*<<< orphan*/  SDHCI_HOST_CONTROL2 ; 
 int /*<<< orphan*/  gli_set_9750_rx_inv (struct sdhci_host*,int) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_abort_tuning (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int sdhci_readw (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_reset_tuning (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_send_tuning (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_start_tuning (struct sdhci_host*) ; 

__attribute__((used)) static int __sdhci_execute_tuning_9750(struct sdhci_host *host, u32 opcode)
{
	int i;
	int rx_inv;

	for (rx_inv = 0; rx_inv < 2; rx_inv++) {
		gli_set_9750_rx_inv(host, !!rx_inv);
		sdhci_start_tuning(host);

		for (i = 0; i < GLI_MAX_TUNING_LOOP; i++) {
			u16 ctrl;

			sdhci_send_tuning(host, opcode);

			if (!host->tuning_done) {
				sdhci_abort_tuning(host, opcode);
				break;
			}

			ctrl = sdhci_readw(host, SDHCI_HOST_CONTROL2);
			if (!(ctrl & SDHCI_CTRL_EXEC_TUNING)) {
				if (ctrl & SDHCI_CTRL_TUNED_CLK)
					return 0; /* Success! */
				break;
			}
		}
	}
	if (!host->tuning_done) {
		pr_info("%s: Tuning timeout, falling back to fixed sampling clock\n",
			mmc_hostname(host->mmc));
		return -ETIMEDOUT;
	}

	pr_info("%s: Tuning failed, falling back to fixed sampling clock\n",
		mmc_hostname(host->mmc));
	sdhci_reset_tuning(host);

	return -EAGAIN;
}