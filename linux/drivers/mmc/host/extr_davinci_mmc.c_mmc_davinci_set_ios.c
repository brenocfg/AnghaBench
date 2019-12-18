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
struct TYPE_2__ {struct davinci_mmc_config* platform_data; } ;
struct platform_device {int /*<<< orphan*/  id; TYPE_1__ dev; } ;
struct mmc_ios {int const power_mode; int bus_width; int /*<<< orphan*/  bus_mode; int /*<<< orphan*/  vdd; int /*<<< orphan*/  clock; } ;
struct mmc_host {int /*<<< orphan*/  parent; } ;
struct mmc_davinci_host {int /*<<< orphan*/  mmc; scalar_t__ base; int /*<<< orphan*/  bus_mode; int /*<<< orphan*/  version; } ;
struct davinci_mmc_config {int /*<<< orphan*/  (* set_power ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 scalar_t__ DAVINCI_MMCARGHL ; 
 scalar_t__ DAVINCI_MMCCMD ; 
 scalar_t__ DAVINCI_MMCCTL ; 
 scalar_t__ DAVINCI_MMCST0 ; 
 int MMCCMD_INITCK ; 
 int MMCCTL_WIDTH_4_BIT ; 
 int MMCCTL_WIDTH_8_BIT ; 
 int MMCST0_RSPDNE ; 
#define  MMC_BUS_WIDTH_1 132 
#define  MMC_BUS_WIDTH_4 131 
#define  MMC_BUS_WIDTH_8 130 
 int /*<<< orphan*/  MMC_CTLR_VERSION_2 ; 
#define  MMC_POWER_OFF 129 
#define  MMC_POWER_UP 128 
 int /*<<< orphan*/  calculate_clk_divider (struct mmc_host*,struct mmc_ios*) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 struct mmc_davinci_host* mmc_priv (struct mmc_host*) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mmc_davinci_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct mmc_davinci_host *host = mmc_priv(mmc);
	struct platform_device *pdev = to_platform_device(mmc->parent);
	struct davinci_mmc_config *config = pdev->dev.platform_data;

	dev_dbg(mmc_dev(host->mmc),
		"clock %dHz busmode %d powermode %d Vdd %04x\n",
		ios->clock, ios->bus_mode, ios->power_mode,
		ios->vdd);

	switch (ios->power_mode) {
	case MMC_POWER_OFF:
		if (config && config->set_power)
			config->set_power(pdev->id, false);
		break;
	case MMC_POWER_UP:
		if (config && config->set_power)
			config->set_power(pdev->id, true);
		break;
	}

	switch (ios->bus_width) {
	case MMC_BUS_WIDTH_8:
		dev_dbg(mmc_dev(host->mmc), "Enabling 8 bit mode\n");
		writel((readl(host->base + DAVINCI_MMCCTL) &
			~MMCCTL_WIDTH_4_BIT) | MMCCTL_WIDTH_8_BIT,
			host->base + DAVINCI_MMCCTL);
		break;
	case MMC_BUS_WIDTH_4:
		dev_dbg(mmc_dev(host->mmc), "Enabling 4 bit mode\n");
		if (host->version == MMC_CTLR_VERSION_2)
			writel((readl(host->base + DAVINCI_MMCCTL) &
				~MMCCTL_WIDTH_8_BIT) | MMCCTL_WIDTH_4_BIT,
				host->base + DAVINCI_MMCCTL);
		else
			writel(readl(host->base + DAVINCI_MMCCTL) |
				MMCCTL_WIDTH_4_BIT,
				host->base + DAVINCI_MMCCTL);
		break;
	case MMC_BUS_WIDTH_1:
		dev_dbg(mmc_dev(host->mmc), "Enabling 1 bit mode\n");
		if (host->version == MMC_CTLR_VERSION_2)
			writel(readl(host->base + DAVINCI_MMCCTL) &
				~(MMCCTL_WIDTH_8_BIT | MMCCTL_WIDTH_4_BIT),
				host->base + DAVINCI_MMCCTL);
		else
			writel(readl(host->base + DAVINCI_MMCCTL) &
				~MMCCTL_WIDTH_4_BIT,
				host->base + DAVINCI_MMCCTL);
		break;
	}

	calculate_clk_divider(mmc, ios);

	host->bus_mode = ios->bus_mode;
	if (ios->power_mode == MMC_POWER_UP) {
		unsigned long timeout = jiffies + msecs_to_jiffies(50);
		bool lose = true;

		/* Send clock cycles, poll completion */
		writel(0, host->base + DAVINCI_MMCARGHL);
		writel(MMCCMD_INITCK, host->base + DAVINCI_MMCCMD);
		while (time_before(jiffies, timeout)) {
			u32 tmp = readl(host->base + DAVINCI_MMCST0);

			if (tmp & MMCST0_RSPDNE) {
				lose = false;
				break;
			}
			cpu_relax();
		}
		if (lose)
			dev_warn(mmc_dev(host->mmc), "powerup timeout\n");
	}

	/* FIXME on power OFF, reset things ... */
}