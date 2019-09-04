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
struct sdhci_pci_slot {TYPE_3__* chip; TYPE_2__* host; } ;
struct mmc_host {int dummy; } ;
struct intel_host {int /*<<< orphan*/  d3_retune; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  rpm_retune; TYPE_1__* pdev; } ;
struct TYPE_5__ {struct mmc_host* mmc; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_dsm_init (struct intel_host*,struct device*,struct mmc_host*) ; 
 struct intel_host* sdhci_pci_priv (struct sdhci_pci_slot*) ; 

__attribute__((used)) static void byt_read_dsm(struct sdhci_pci_slot *slot)
{
	struct intel_host *intel_host = sdhci_pci_priv(slot);
	struct device *dev = &slot->chip->pdev->dev;
	struct mmc_host *mmc = slot->host->mmc;

	intel_dsm_init(intel_host, dev, mmc);
	slot->chip->rpm_retune = intel_host->d3_retune;
}