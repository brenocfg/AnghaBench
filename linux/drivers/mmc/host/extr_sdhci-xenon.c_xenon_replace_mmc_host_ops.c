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
struct TYPE_2__ {int /*<<< orphan*/  enable_sdio_irq; int /*<<< orphan*/  execute_tuning; int /*<<< orphan*/  init_card; int /*<<< orphan*/  start_signal_voltage_switch; int /*<<< orphan*/  set_ios; } ;
struct sdhci_host {TYPE_1__ mmc_host_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  xenon_enable_sdio_irq ; 
 int /*<<< orphan*/  xenon_execute_tuning ; 
 int /*<<< orphan*/  xenon_init_card ; 
 int /*<<< orphan*/  xenon_set_ios ; 
 int /*<<< orphan*/  xenon_start_signal_voltage_switch ; 

__attribute__((used)) static void xenon_replace_mmc_host_ops(struct sdhci_host *host)
{
	host->mmc_host_ops.set_ios = xenon_set_ios;
	host->mmc_host_ops.start_signal_voltage_switch =
			xenon_start_signal_voltage_switch;
	host->mmc_host_ops.init_card = xenon_init_card;
	host->mmc_host_ops.execute_tuning = xenon_execute_tuning;
	host->mmc_host_ops.enable_sdio_irq = xenon_enable_sdio_irq;
}