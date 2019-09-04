#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sdhci_host {TYPE_1__* mmc; scalar_t__ ioaddr; } ;
struct TYPE_2__ {scalar_t__ actual_clock; } ;

/* Variables and functions */
 scalar_t__ ESDHC_STROBE_DLL_CLK_FREQ ; 
 scalar_t__ ESDHC_STROBE_DLL_CTRL ; 
 int ESDHC_STROBE_DLL_CTRL_ENABLE ; 
 int ESDHC_STROBE_DLL_CTRL_RESET ; 
 int ESDHC_STROBE_DLL_CTRL_SLV_DLY_TARGET_SHIFT ; 
 scalar_t__ ESDHC_STROBE_DLL_STATUS ; 
 int ESDHC_STROBE_DLL_STS_REF_LOCK ; 
 int ESDHC_STROBE_DLL_STS_SLV_LOCK ; 
 scalar_t__ ESDHC_VENDOR_SPEC ; 
 int ESDHC_VENDOR_SPEC_FRC_SDCLK_ON ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmc_dev (TYPE_1__*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void esdhc_set_strobe_dll(struct sdhci_host *host)
{
	u32 v;

	if (host->mmc->actual_clock > ESDHC_STROBE_DLL_CLK_FREQ) {
		/* disable clock before enabling strobe dll */
		writel(readl(host->ioaddr + ESDHC_VENDOR_SPEC) &
		       ~ESDHC_VENDOR_SPEC_FRC_SDCLK_ON,
		       host->ioaddr + ESDHC_VENDOR_SPEC);

		/* force a reset on strobe dll */
		writel(ESDHC_STROBE_DLL_CTRL_RESET,
			host->ioaddr + ESDHC_STROBE_DLL_CTRL);
		/*
		 * enable strobe dll ctrl and adjust the delay target
		 * for the uSDHC loopback read clock
		 */
		v = ESDHC_STROBE_DLL_CTRL_ENABLE |
			(7 << ESDHC_STROBE_DLL_CTRL_SLV_DLY_TARGET_SHIFT);
		writel(v, host->ioaddr + ESDHC_STROBE_DLL_CTRL);
		/* wait 1us to make sure strobe dll status register stable */
		udelay(1);
		v = readl(host->ioaddr + ESDHC_STROBE_DLL_STATUS);
		if (!(v & ESDHC_STROBE_DLL_STS_REF_LOCK))
			dev_warn(mmc_dev(host->mmc),
				"warning! HS400 strobe DLL status REF not lock!\n");
		if (!(v & ESDHC_STROBE_DLL_STS_SLV_LOCK))
			dev_warn(mmc_dev(host->mmc),
				"warning! HS400 strobe DLL status SLV not lock!\n");
	}
}