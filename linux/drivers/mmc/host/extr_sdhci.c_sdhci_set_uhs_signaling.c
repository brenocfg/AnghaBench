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
typedef  int /*<<< orphan*/  u16 ;
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 unsigned int MMC_TIMING_MMC_DDR52 ; 
 unsigned int MMC_TIMING_MMC_HS ; 
 unsigned int MMC_TIMING_MMC_HS200 ; 
 unsigned int MMC_TIMING_MMC_HS400 ; 
 unsigned int MMC_TIMING_SD_HS ; 
 unsigned int MMC_TIMING_UHS_DDR50 ; 
 unsigned int MMC_TIMING_UHS_SDR104 ; 
 unsigned int MMC_TIMING_UHS_SDR12 ; 
 unsigned int MMC_TIMING_UHS_SDR25 ; 
 unsigned int MMC_TIMING_UHS_SDR50 ; 
 int /*<<< orphan*/  SDHCI_CTRL_HS400 ; 
 int /*<<< orphan*/  SDHCI_CTRL_UHS_DDR50 ; 
 int /*<<< orphan*/  SDHCI_CTRL_UHS_MASK ; 
 int /*<<< orphan*/  SDHCI_CTRL_UHS_SDR104 ; 
 int /*<<< orphan*/  SDHCI_CTRL_UHS_SDR12 ; 
 int /*<<< orphan*/  SDHCI_CTRL_UHS_SDR25 ; 
 int /*<<< orphan*/  SDHCI_CTRL_UHS_SDR50 ; 
 int /*<<< orphan*/  SDHCI_HOST_CONTROL2 ; 
 int /*<<< orphan*/  sdhci_readw (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writew (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sdhci_set_uhs_signaling(struct sdhci_host *host, unsigned timing)
{
	u16 ctrl_2;

	ctrl_2 = sdhci_readw(host, SDHCI_HOST_CONTROL2);
	/* Select Bus Speed Mode for host */
	ctrl_2 &= ~SDHCI_CTRL_UHS_MASK;
	if ((timing == MMC_TIMING_MMC_HS200) ||
	    (timing == MMC_TIMING_UHS_SDR104))
		ctrl_2 |= SDHCI_CTRL_UHS_SDR104;
	else if (timing == MMC_TIMING_UHS_SDR12)
		ctrl_2 |= SDHCI_CTRL_UHS_SDR12;
	else if (timing == MMC_TIMING_SD_HS ||
		 timing == MMC_TIMING_MMC_HS ||
		 timing == MMC_TIMING_UHS_SDR25)
		ctrl_2 |= SDHCI_CTRL_UHS_SDR25;
	else if (timing == MMC_TIMING_UHS_SDR50)
		ctrl_2 |= SDHCI_CTRL_UHS_SDR50;
	else if ((timing == MMC_TIMING_UHS_DDR50) ||
		 (timing == MMC_TIMING_MMC_DDR52))
		ctrl_2 |= SDHCI_CTRL_UHS_DDR50;
	else if (timing == MMC_TIMING_MMC_HS400)
		ctrl_2 |= SDHCI_CTRL_HS400; /* Non-standard */
	sdhci_writew(host, ctrl_2, SDHCI_HOST_CONTROL2);
}