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
struct mmc_host_ops {int /*<<< orphan*/  execute_tuning; } ;
struct TYPE_2__ {struct mmc_host_ops mmc_host_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  amd_execute_tuning ; 

__attribute__((used)) static int amd_probe_slot(struct sdhci_pci_slot *slot)
{
	struct mmc_host_ops *ops = &slot->host->mmc_host_ops;

	ops->execute_tuning = amd_execute_tuning;

	return 0;
}