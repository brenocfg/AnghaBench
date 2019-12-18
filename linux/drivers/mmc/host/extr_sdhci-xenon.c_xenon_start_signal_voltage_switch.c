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
struct sdhci_host {int dummy; } ;
struct mmc_ios {int /*<<< orphan*/  signal_voltage; } ;
struct TYPE_2__ {int /*<<< orphan*/  vqmmc; } ;
struct mmc_host {TYPE_1__ supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ ) ; 
 struct sdhci_host* mmc_priv (struct mmc_host*) ; 
 int sdhci_start_signal_voltage_switch (struct mmc_host*,struct mmc_ios*) ; 
 int /*<<< orphan*/  xenon_enable_internal_clk (struct sdhci_host*) ; 
 int /*<<< orphan*/  xenon_soc_pad_ctrl (struct sdhci_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xenon_start_signal_voltage_switch(struct mmc_host *mmc,
					     struct mmc_ios *ios)
{
	struct sdhci_host *host = mmc_priv(mmc);

	/*
	 * Before SD/SDIO set signal voltage, SD bus clock should be
	 * disabled. However, sdhci_set_clock will also disable the Internal
	 * clock in mmc_set_signal_voltage().
	 * If Internal clock is disabled, the 3.3V/1.8V bit can not be updated.
	 * Thus here manually enable internal clock.
	 *
	 * After switch completes, it is unnecessary to disable internal clock,
	 * since keeping internal clock active obeys SD spec.
	 */
	xenon_enable_internal_clk(host);

	xenon_soc_pad_ctrl(host, ios->signal_voltage);

	/*
	 * If Vqmmc is fixed on platform, vqmmc regulator should be unavailable.
	 * Thus SDHCI_CTRL_VDD_180 bit might not work then.
	 * Skip the standard voltage switch to avoid any issue.
	 */
	if (PTR_ERR(mmc->supply.vqmmc) == -ENODEV)
		return 0;

	return sdhci_start_signal_voltage_switch(mmc, ios);
}