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
typedef  int /*<<< orphan*/  u8 ;
struct sdhci_host {scalar_t__ ioaddr; TYPE_2__* mmc; } ;
struct TYPE_3__ {unsigned char timing; } ;
struct TYPE_4__ {TYPE_1__ ios; } ;

/* Variables and functions */
#define  MMC_TIMING_MMC_HS 131 
#define  MMC_TIMING_SD_HS 130 
#define  MMC_TIMING_UHS_SDR12 129 
#define  MMC_TIMING_UHS_SDR25 128 
 int /*<<< orphan*/  SDHCI_CTRL_HISPD ; 
 int SDHCI_HOST_CONTROL ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sdhci_am654_write_b(struct sdhci_host *host, u8 val, int reg)
{
	unsigned char timing = host->mmc->ios.timing;

	if (reg == SDHCI_HOST_CONTROL) {
		switch (timing) {
		/*
		 * According to the data manual, HISPD bit
		 * should not be set in these speed modes.
		 */
		case MMC_TIMING_SD_HS:
		case MMC_TIMING_MMC_HS:
		case MMC_TIMING_UHS_SDR12:
		case MMC_TIMING_UHS_SDR25:
			val &= ~SDHCI_CTRL_HISPD;
		}
	}

	writeb(val, host->ioaddr + reg);
}