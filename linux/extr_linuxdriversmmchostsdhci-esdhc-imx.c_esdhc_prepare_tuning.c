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
typedef  int u32 ;
struct sdhci_host {scalar_t__ ioaddr; int /*<<< orphan*/  mmc; } ;

/* Variables and functions */
 scalar_t__ ESDHC_MIX_CTRL ; 
 int ESDHC_MIX_CTRL_EXE_TUNE ; 
 int ESDHC_MIX_CTRL_FBCLK_SEL ; 
 int ESDHC_MIX_CTRL_SMPCLK_SEL ; 
 scalar_t__ ESDHC_TUNE_CTRL_STATUS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void esdhc_prepare_tuning(struct sdhci_host *host, u32 val)
{
	u32 reg;

	/* FIXME: delay a bit for card to be ready for next tuning due to errors */
	mdelay(1);

	reg = readl(host->ioaddr + ESDHC_MIX_CTRL);
	reg |= ESDHC_MIX_CTRL_EXE_TUNE | ESDHC_MIX_CTRL_SMPCLK_SEL |
			ESDHC_MIX_CTRL_FBCLK_SEL;
	writel(reg, host->ioaddr + ESDHC_MIX_CTRL);
	writel(val << 8, host->ioaddr + ESDHC_TUNE_CTRL_STATUS);
	dev_dbg(mmc_dev(host->mmc),
		"tuning with delay 0x%x ESDHC_TUNE_CTRL_STATUS 0x%x\n",
			val, readl(host->ioaddr + ESDHC_TUNE_CTRL_STATUS));
}