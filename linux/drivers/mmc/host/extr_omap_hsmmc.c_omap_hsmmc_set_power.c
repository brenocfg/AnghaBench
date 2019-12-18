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
struct omap_hsmmc_host {struct mmc_host* mmc; } ;
struct TYPE_2__ {int /*<<< orphan*/  vmmc; } ;
struct mmc_host {TYPE_1__ supply; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int omap_hsmmc_disable_supply (struct mmc_host*) ; 
 int omap_hsmmc_enable_supply (struct mmc_host*) ; 
 int omap_hsmmc_set_pbias (struct omap_hsmmc_host*,int) ; 

__attribute__((used)) static int omap_hsmmc_set_power(struct omap_hsmmc_host *host, int power_on)
{
	struct mmc_host *mmc = host->mmc;
	int ret = 0;

	/*
	 * If we don't see a Vcc regulator, assume it's a fixed
	 * voltage always-on regulator.
	 */
	if (IS_ERR(mmc->supply.vmmc))
		return 0;

	ret = omap_hsmmc_set_pbias(host, false);
	if (ret)
		return ret;

	/*
	 * Assume Vcc regulator is used only to power the card ... OMAP
	 * VDDS is used to power the pins, optionally with a transceiver to
	 * support cards using voltages other than VDDS (1.8V nominal).  When a
	 * transceiver is used, DAT3..7 are muxed as transceiver control pins.
	 *
	 * In some cases this regulator won't support enable/disable;
	 * e.g. it's a fixed rail for a WLAN chip.
	 *
	 * In other cases vcc_aux switches interface power.  Example, for
	 * eMMC cards it represents VccQ.  Sometimes transceivers or SDIO
	 * chips/cards need an interface voltage rail too.
	 */
	if (power_on) {
		ret = omap_hsmmc_enable_supply(mmc);
		if (ret)
			return ret;

		ret = omap_hsmmc_set_pbias(host, true);
		if (ret)
			goto err_set_voltage;
	} else {
		ret = omap_hsmmc_disable_supply(mmc);
		if (ret)
			return ret;
	}

	return 0;

err_set_voltage:
	omap_hsmmc_disable_supply(mmc);

	return ret;
}