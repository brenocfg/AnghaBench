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
struct sdhci_acpi_host {TYPE_2__* host; } ;
struct platform_device {int dummy; } ;
struct intel_host {int hs_caps; } ;
struct TYPE_4__ {TYPE_1__* mmc; } ;
struct TYPE_3__ {int /*<<< orphan*/  caps; } ;

/* Variables and functions */
 int INTEL_DSM_HS_CAPS_DDR50 ; 
 int INTEL_DSM_HS_CAPS_SDR104 ; 
 int INTEL_DSM_HS_CAPS_SDR25 ; 
 int INTEL_DSM_HS_CAPS_SDR50 ; 
 int /*<<< orphan*/  MMC_CAP_UHS_DDR50 ; 
 int /*<<< orphan*/  MMC_CAP_UHS_SDR104 ; 
 int /*<<< orphan*/  MMC_CAP_UHS_SDR25 ; 
 int /*<<< orphan*/  MMC_CAP_UHS_SDR50 ; 
 struct sdhci_acpi_host* platform_get_drvdata (struct platform_device*) ; 
 struct intel_host* sdhci_acpi_priv (struct sdhci_acpi_host*) ; 

__attribute__((used)) static int intel_setup_host(struct platform_device *pdev)
{
	struct sdhci_acpi_host *c = platform_get_drvdata(pdev);
	struct intel_host *intel_host = sdhci_acpi_priv(c);

	if (!(intel_host->hs_caps & INTEL_DSM_HS_CAPS_SDR25))
		c->host->mmc->caps &= ~MMC_CAP_UHS_SDR25;

	if (!(intel_host->hs_caps & INTEL_DSM_HS_CAPS_SDR50))
		c->host->mmc->caps &= ~MMC_CAP_UHS_SDR50;

	if (!(intel_host->hs_caps & INTEL_DSM_HS_CAPS_DDR50))
		c->host->mmc->caps &= ~MMC_CAP_UHS_DDR50;

	if (!(intel_host->hs_caps & INTEL_DSM_HS_CAPS_SDR104))
		c->host->mmc->caps &= ~MMC_CAP_UHS_SDR104;

	return 0;
}