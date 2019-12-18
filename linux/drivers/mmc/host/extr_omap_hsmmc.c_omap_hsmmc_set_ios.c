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
struct omap_hsmmc_host {int /*<<< orphan*/  mmc; int /*<<< orphan*/  base; TYPE_1__* pdata; scalar_t__ power_mode; } ;
struct mmc_ios {int /*<<< orphan*/  vdd; scalar_t__ power_mode; } ;
struct mmc_host {int dummy; } ;
struct TYPE_2__ {int controller_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUAL_VOLT_OCR_BIT ; 
 int /*<<< orphan*/  HCTL ; 
#define  MMC_POWER_OFF 130 
#define  MMC_POWER_ON 129 
#define  MMC_POWER_UP 128 
 int OMAP_HSMMC_READ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OMAP_HSMMC_SUPPORTS_DUAL_VOLT ; 
 int SDVSDET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 struct omap_hsmmc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  omap_hsmmc_set_bus_mode (struct omap_hsmmc_host*) ; 
 int /*<<< orphan*/  omap_hsmmc_set_bus_width (struct omap_hsmmc_host*) ; 
 int /*<<< orphan*/  omap_hsmmc_set_clock (struct omap_hsmmc_host*) ; 
 int /*<<< orphan*/  omap_hsmmc_set_power (struct omap_hsmmc_host*,int) ; 
 scalar_t__ omap_hsmmc_switch_opcond (struct omap_hsmmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_init_stream (struct omap_hsmmc_host*) ; 

__attribute__((used)) static void omap_hsmmc_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct omap_hsmmc_host *host = mmc_priv(mmc);
	int do_send_init_stream = 0;

	if (ios->power_mode != host->power_mode) {
		switch (ios->power_mode) {
		case MMC_POWER_OFF:
			omap_hsmmc_set_power(host, 0);
			break;
		case MMC_POWER_UP:
			omap_hsmmc_set_power(host, 1);
			break;
		case MMC_POWER_ON:
			do_send_init_stream = 1;
			break;
		}
		host->power_mode = ios->power_mode;
	}

	/* FIXME: set registers based only on changes to ios */

	omap_hsmmc_set_bus_width(host);

	if (host->pdata->controller_flags & OMAP_HSMMC_SUPPORTS_DUAL_VOLT) {
		/* Only MMC1 can interface at 3V without some flavor
		 * of external transceiver; but they all handle 1.8V.
		 */
		if ((OMAP_HSMMC_READ(host->base, HCTL) & SDVSDET) &&
			(ios->vdd == DUAL_VOLT_OCR_BIT)) {
				/*
				 * The mmc_select_voltage fn of the core does
				 * not seem to set the power_mode to
				 * MMC_POWER_UP upon recalculating the voltage.
				 * vdd 1.8v.
				 */
			if (omap_hsmmc_switch_opcond(host, ios->vdd) != 0)
				dev_dbg(mmc_dev(host->mmc),
						"Switch operation failed\n");
		}
	}

	omap_hsmmc_set_clock(host);

	if (do_send_init_stream)
		send_init_stream(host);

	omap_hsmmc_set_bus_mode(host);
}