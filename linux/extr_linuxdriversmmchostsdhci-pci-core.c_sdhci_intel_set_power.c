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
typedef  int u8 ;
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 unsigned char MMC_POWER_OFF ; 
 int SDHCI_INTEL_PWR_TIMEOUT_CNT ; 
 int /*<<< orphan*/  SDHCI_INTEL_PWR_TIMEOUT_UDELAY ; 
 int /*<<< orphan*/  SDHCI_POWER_CONTROL ; 
 int SDHCI_POWER_ON ; 
 int sdhci_readb (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_set_power (struct sdhci_host*,unsigned char,unsigned short) ; 
 int /*<<< orphan*/  sdhci_writeb (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdhci_intel_set_power(struct sdhci_host *host, unsigned char mode,
				  unsigned short vdd)
{
	int cntr;
	u8 reg;

	sdhci_set_power(host, mode, vdd);

	if (mode == MMC_POWER_OFF)
		return;

	/*
	 * Bus power might not enable after D3 -> D0 transition due to the
	 * present state not yet having propagated. Retry for up to 2ms.
	 */
	for (cntr = 0; cntr < SDHCI_INTEL_PWR_TIMEOUT_CNT; cntr++) {
		reg = sdhci_readb(host, SDHCI_POWER_CONTROL);
		if (reg & SDHCI_POWER_ON)
			break;
		udelay(SDHCI_INTEL_PWR_TIMEOUT_UDELAY);
		reg |= SDHCI_POWER_ON;
		sdhci_writeb(host, reg, SDHCI_POWER_CONTROL);
	}
}