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
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 unsigned int MMC_TIMING_MMC_HS400 ; 
 int /*<<< orphan*/  esdhc_tuning_block_enable (struct sdhci_host*,int) ; 
 int /*<<< orphan*/  sdhci_set_uhs_signaling (struct sdhci_host*,unsigned int) ; 

__attribute__((used)) static void esdhc_set_uhs_signaling(struct sdhci_host *host,
				   unsigned int timing)
{
	if (timing == MMC_TIMING_MMC_HS400)
		esdhc_tuning_block_enable(host, true);
	else
		sdhci_set_uhs_signaling(host, timing);
}