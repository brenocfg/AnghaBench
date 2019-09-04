#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct s3cmci_host {int real_rate; int /*<<< orphan*/  bus_width; scalar_t__ base; TYPE_3__* pdata; int /*<<< orphan*/  is2440; TYPE_2__* pdev; } ;
struct mmc_ios {int power_mode; int clock; int /*<<< orphan*/  bus_width; int /*<<< orphan*/  vdd; } ;
struct mmc_host {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_power ) (int,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_5__ {TYPE_1__ dev; } ;

/* Variables and functions */
#define  MMC_POWER_OFF 130 
#define  MMC_POWER_ON 129 
#define  MMC_POWER_UP 128 
 int /*<<< orphan*/  S3C2410_GPE (int) ; 
 scalar_t__ S3C2410_SDICON ; 
 int /*<<< orphan*/  S3C2410_SDICON_CLOCKTYPE ; 
 int /*<<< orphan*/  S3C2410_SDICON_FIFORESET ; 
 int /*<<< orphan*/  S3C2440_SDICON_SDRESET ; 
 int /*<<< orphan*/  S3C_GPIO_PULL_NONE ; 
 int /*<<< orphan*/  S3C_GPIO_SFN (int) ; 
 int /*<<< orphan*/  dbg (struct s3cmci_host*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dbg_conf ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct s3cmci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  s3c_gpio_cfgall_range (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3cmci_set_clk (struct s3cmci_host*,struct mmc_ios*) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void s3cmci_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct s3cmci_host *host = mmc_priv(mmc);
	u32 mci_con;

	/* Set the power state */

	mci_con = readl(host->base + S3C2410_SDICON);

	switch (ios->power_mode) {
	case MMC_POWER_ON:
	case MMC_POWER_UP:
		/* Configure GPE5...GPE10 pins in SD mode */
		if (!host->pdev->dev.of_node)
			s3c_gpio_cfgall_range(S3C2410_GPE(5), 6, S3C_GPIO_SFN(2),
					      S3C_GPIO_PULL_NONE);

		if (host->pdata->set_power)
			host->pdata->set_power(ios->power_mode, ios->vdd);

		if (!host->is2440)
			mci_con |= S3C2410_SDICON_FIFORESET;

		break;

	case MMC_POWER_OFF:
	default:
		if (!host->pdev->dev.of_node)
			gpio_direction_output(S3C2410_GPE(5), 0);

		if (host->is2440)
			mci_con |= S3C2440_SDICON_SDRESET;

		if (host->pdata->set_power)
			host->pdata->set_power(ios->power_mode, ios->vdd);

		break;
	}

	s3cmci_set_clk(host, ios);

	/* Set CLOCK_ENABLE */
	if (ios->clock)
		mci_con |= S3C2410_SDICON_CLOCKTYPE;
	else
		mci_con &= ~S3C2410_SDICON_CLOCKTYPE;

	writel(mci_con, host->base + S3C2410_SDICON);

	if ((ios->power_mode == MMC_POWER_ON) ||
	    (ios->power_mode == MMC_POWER_UP)) {
		dbg(host, dbg_conf, "running at %lukHz (requested: %ukHz).\n",
			host->real_rate/1000, ios->clock/1000);
	} else {
		dbg(host, dbg_conf, "powered down.\n");
	}

	host->bus_width = ios->bus_width;
}