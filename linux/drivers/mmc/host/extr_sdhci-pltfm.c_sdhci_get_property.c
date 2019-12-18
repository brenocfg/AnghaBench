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
typedef  int u32 ;
struct sdhci_pltfm_host {int clock; } ;
struct sdhci_host {TYPE_1__* mmc; int /*<<< orphan*/  quirks2; int /*<<< orphan*/  quirks; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  pm_caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_PM_KEEP_POWER ; 
 int /*<<< orphan*/  MMC_PM_WAKE_SDIO_IRQ ; 
 int /*<<< orphan*/  SDHCI_QUIRK2_NO_1_8_V ; 
 int /*<<< orphan*/  SDHCI_QUIRK_BROKEN_CARD_DETECTION ; 
 int /*<<< orphan*/  SDHCI_QUIRK_FORCE_1_BIT_DATA ; 
 int /*<<< orphan*/  SDHCI_QUIRK_INVERTED_WRITE_PROTECT ; 
 int /*<<< orphan*/  SDHCI_QUIRK_MULTIBLOCK_READ_ACMD12 ; 
 scalar_t__ device_property_present (struct device*,char*) ; 
 scalar_t__ device_property_read_bool (struct device*,char*) ; 
 scalar_t__ device_property_read_u32 (struct device*,char*,int*) ; 
 struct sdhci_host* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sdhci_get_compatibility (struct platform_device*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 scalar_t__ sdhci_wp_inverted (struct device*) ; 

void sdhci_get_property(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct sdhci_host *host = platform_get_drvdata(pdev);
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	u32 bus_width;

	if (device_property_present(dev, "sdhci,auto-cmd12"))
		host->quirks |= SDHCI_QUIRK_MULTIBLOCK_READ_ACMD12;

	if (device_property_present(dev, "sdhci,1-bit-only") ||
	    (device_property_read_u32(dev, "bus-width", &bus_width) == 0 &&
	    bus_width == 1))
		host->quirks |= SDHCI_QUIRK_FORCE_1_BIT_DATA;

	if (sdhci_wp_inverted(dev))
		host->quirks |= SDHCI_QUIRK_INVERTED_WRITE_PROTECT;

	if (device_property_present(dev, "broken-cd"))
		host->quirks |= SDHCI_QUIRK_BROKEN_CARD_DETECTION;

	if (device_property_present(dev, "no-1-8-v"))
		host->quirks2 |= SDHCI_QUIRK2_NO_1_8_V;

	sdhci_get_compatibility(pdev);

	device_property_read_u32(dev, "clock-frequency", &pltfm_host->clock);

	if (device_property_present(dev, "keep-power-in-suspend"))
		host->mmc->pm_caps |= MMC_PM_KEEP_POWER;

	if (device_property_read_bool(dev, "wakeup-source") ||
	    device_property_read_bool(dev, "enable-sdio-wakeup")) /* legacy */
		host->mmc->pm_caps |= MMC_PM_WAKE_SDIO_IRQ;
}