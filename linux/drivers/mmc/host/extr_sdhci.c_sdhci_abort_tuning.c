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
struct sdhci_host {int /*<<< orphan*/  mmc; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDHCI_RESET_CMD ; 
 int /*<<< orphan*/  SDHCI_RESET_DATA ; 
 int /*<<< orphan*/  mmc_abort_tuning (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_do_reset (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_end_tuning (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_reset_tuning (struct sdhci_host*) ; 

void sdhci_abort_tuning(struct sdhci_host *host, u32 opcode)
{
	sdhci_reset_tuning(host);

	sdhci_do_reset(host, SDHCI_RESET_CMD);
	sdhci_do_reset(host, SDHCI_RESET_DATA);

	sdhci_end_tuning(host);

	mmc_abort_tuning(host->mmc, opcode);
}