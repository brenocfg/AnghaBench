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
typedef  int /*<<< orphan*/  u8 ;
struct sdhci_host {int quirks2; int quirks; int /*<<< orphan*/  pwr; int /*<<< orphan*/  mmc; } ;

/* Variables and functions */
 unsigned char MMC_POWER_OFF ; 
#define  MMC_VDD_165_195 133 
#define  MMC_VDD_20_21 132 
#define  MMC_VDD_29_30 131 
#define  MMC_VDD_30_31 130 
#define  MMC_VDD_32_33 129 
#define  MMC_VDD_33_34 128 
 int /*<<< orphan*/  SDHCI_POWER_180 ; 
 int /*<<< orphan*/  SDHCI_POWER_300 ; 
 int /*<<< orphan*/  SDHCI_POWER_330 ; 
 int /*<<< orphan*/  SDHCI_POWER_CONTROL ; 
 int /*<<< orphan*/  SDHCI_POWER_ON ; 
 int SDHCI_QUIRK2_CARD_ON_NEEDS_BUS_ON ; 
 int SDHCI_QUIRK_DELAY_AFTER_POWER ; 
 int SDHCI_QUIRK_NO_SIMULT_VDD_AND_POWER ; 
 int SDHCI_QUIRK_SINGLE_POWER_WRITE ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_runtime_pm_bus_off (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_runtime_pm_bus_on (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_writeb (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sdhci_set_power_noreg(struct sdhci_host *host, unsigned char mode,
			   unsigned short vdd)
{
	u8 pwr = 0;

	if (mode != MMC_POWER_OFF) {
		switch (1 << vdd) {
		case MMC_VDD_165_195:
		/*
		 * Without a regulator, SDHCI does not support 2.0v
		 * so we only get here if the driver deliberately
		 * added the 2.0v range to ocr_avail. Map it to 1.8v
		 * for the purpose of turning on the power.
		 */
		case MMC_VDD_20_21:
			pwr = SDHCI_POWER_180;
			break;
		case MMC_VDD_29_30:
		case MMC_VDD_30_31:
			pwr = SDHCI_POWER_300;
			break;
		case MMC_VDD_32_33:
		case MMC_VDD_33_34:
			pwr = SDHCI_POWER_330;
			break;
		default:
			WARN(1, "%s: Invalid vdd %#x\n",
			     mmc_hostname(host->mmc), vdd);
			break;
		}
	}

	if (host->pwr == pwr)
		return;

	host->pwr = pwr;

	if (pwr == 0) {
		sdhci_writeb(host, 0, SDHCI_POWER_CONTROL);
		if (host->quirks2 & SDHCI_QUIRK2_CARD_ON_NEEDS_BUS_ON)
			sdhci_runtime_pm_bus_off(host);
	} else {
		/*
		 * Spec says that we should clear the power reg before setting
		 * a new value. Some controllers don't seem to like this though.
		 */
		if (!(host->quirks & SDHCI_QUIRK_SINGLE_POWER_WRITE))
			sdhci_writeb(host, 0, SDHCI_POWER_CONTROL);

		/*
		 * At least the Marvell CaFe chip gets confused if we set the
		 * voltage and set turn on power at the same time, so set the
		 * voltage first.
		 */
		if (host->quirks & SDHCI_QUIRK_NO_SIMULT_VDD_AND_POWER)
			sdhci_writeb(host, pwr, SDHCI_POWER_CONTROL);

		pwr |= SDHCI_POWER_ON;

		sdhci_writeb(host, pwr, SDHCI_POWER_CONTROL);

		if (host->quirks2 & SDHCI_QUIRK2_CARD_ON_NEEDS_BUS_ON)
			sdhci_runtime_pm_bus_on(host);

		/*
		 * Some controllers need an extra 10ms delay of 10ms before
		 * they can apply clock after applying power
		 */
		if (host->quirks & SDHCI_QUIRK_DELAY_AFTER_POWER)
			mdelay(10);
	}
}