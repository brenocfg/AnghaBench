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
struct sdhci_host {int tuning_done; int /*<<< orphan*/  mmc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_SEND_TUNING_BLOCK_HS200 ; 
 int SDHCI_CTRL_EXEC_TUNING ; 
 int SDHCI_CTRL_TUNED_CLK ; 
 int /*<<< orphan*/  SDHCI_HOST_CONTROL2 ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int sdhci_readw (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_reset_tuning (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_send_tuning (struct sdhci_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __sdhci_o2_execute_tuning(struct sdhci_host *host, u32 opcode)
{
	int i;

	sdhci_send_tuning(host, MMC_SEND_TUNING_BLOCK_HS200);

	for (i = 0; i < 150; i++) {
		u16 ctrl = sdhci_readw(host, SDHCI_HOST_CONTROL2);

		if (!(ctrl & SDHCI_CTRL_EXEC_TUNING)) {
			if (ctrl & SDHCI_CTRL_TUNED_CLK) {
				host->tuning_done = true;
				return;
			}
			pr_warn("%s: HW tuning failed !\n",
				mmc_hostname(host->mmc));
			break;
		}

		mdelay(1);
	}

	pr_info("%s: Tuning failed, falling back to fixed sampling clock\n",
		mmc_hostname(host->mmc));
	sdhci_reset_tuning(host);
}