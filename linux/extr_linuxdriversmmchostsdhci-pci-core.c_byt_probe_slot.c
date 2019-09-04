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
struct sdhci_pci_slot {TYPE_1__* host; } ;
struct mmc_host_ops {int /*<<< orphan*/  start_signal_voltage_switch; int /*<<< orphan*/  execute_tuning; } ;
struct TYPE_2__ {struct mmc_host_ops mmc_host_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  byt_read_dsm (struct sdhci_pci_slot*) ; 
 int /*<<< orphan*/  intel_execute_tuning ; 
 int /*<<< orphan*/  intel_start_signal_voltage_switch ; 

__attribute__((used)) static void byt_probe_slot(struct sdhci_pci_slot *slot)
{
	struct mmc_host_ops *ops = &slot->host->mmc_host_ops;

	byt_read_dsm(slot);

	ops->execute_tuning = intel_execute_tuning;
	ops->start_signal_voltage_switch = intel_start_signal_voltage_switch;
}