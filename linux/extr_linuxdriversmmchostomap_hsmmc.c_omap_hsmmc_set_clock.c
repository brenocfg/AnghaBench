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
struct omap_hsmmc_host {int /*<<< orphan*/  base; int /*<<< orphan*/  fclk; TYPE_2__* mmc; } ;
struct mmc_ios {scalar_t__ timing; int /*<<< orphan*/  clock; } ;
struct TYPE_4__ {struct mmc_ios ios; } ;
struct TYPE_3__ {int features; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAPA ; 
 unsigned long CLKD_MASK ; 
 int DTO ; 
 unsigned long DTO_MASK ; 
 int /*<<< orphan*/  HCTL ; 
 int HSMMC_HAS_HSPE_SUPPORT ; 
 unsigned long HSPE ; 
 unsigned long HSS ; 
 unsigned long ICE ; 
 unsigned long ICS ; 
 int /*<<< orphan*/  MMC_TIMEOUT_MS ; 
 scalar_t__ MMC_TIMING_MMC_DDR52 ; 
 scalar_t__ MMC_TIMING_UHS_DDR50 ; 
 unsigned long OMAP_HSMMC_READ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OMAP_HSMMC_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  SYSCTL ; 
 unsigned long calc_divisor (struct omap_hsmmc_host*,struct mmc_ios*) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mmc_dev (TYPE_2__*) ; 
 TYPE_1__* mmc_pdata (struct omap_hsmmc_host*) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_hsmmc_start_clock (struct omap_hsmmc_host*) ; 
 int /*<<< orphan*/  omap_hsmmc_stop_clock (struct omap_hsmmc_host*) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static void omap_hsmmc_set_clock(struct omap_hsmmc_host *host)
{
	struct mmc_ios *ios = &host->mmc->ios;
	unsigned long regval;
	unsigned long timeout;
	unsigned long clkdiv;

	dev_vdbg(mmc_dev(host->mmc), "Set clock to %uHz\n", ios->clock);

	omap_hsmmc_stop_clock(host);

	regval = OMAP_HSMMC_READ(host->base, SYSCTL);
	regval = regval & ~(CLKD_MASK | DTO_MASK);
	clkdiv = calc_divisor(host, ios);
	regval = regval | (clkdiv << 6) | (DTO << 16);
	OMAP_HSMMC_WRITE(host->base, SYSCTL, regval);
	OMAP_HSMMC_WRITE(host->base, SYSCTL,
		OMAP_HSMMC_READ(host->base, SYSCTL) | ICE);

	/* Wait till the ICS bit is set */
	timeout = jiffies + msecs_to_jiffies(MMC_TIMEOUT_MS);
	while ((OMAP_HSMMC_READ(host->base, SYSCTL) & ICS) != ICS
		&& time_before(jiffies, timeout))
		cpu_relax();

	/*
	 * Enable High-Speed Support
	 * Pre-Requisites
	 *	- Controller should support High-Speed-Enable Bit
	 *	- Controller should not be using DDR Mode
	 *	- Controller should advertise that it supports High Speed
	 *	  in capabilities register
	 *	- MMC/SD clock coming out of controller > 25MHz
	 */
	if ((mmc_pdata(host)->features & HSMMC_HAS_HSPE_SUPPORT) &&
	    (ios->timing != MMC_TIMING_MMC_DDR52) &&
	    (ios->timing != MMC_TIMING_UHS_DDR50) &&
	    ((OMAP_HSMMC_READ(host->base, CAPA) & HSS) == HSS)) {
		regval = OMAP_HSMMC_READ(host->base, HCTL);
		if (clkdiv && (clk_get_rate(host->fclk)/clkdiv) > 25000000)
			regval |= HSPE;
		else
			regval &= ~HSPE;

		OMAP_HSMMC_WRITE(host->base, HCTL, regval);
	}

	omap_hsmmc_start_clock(host);
}