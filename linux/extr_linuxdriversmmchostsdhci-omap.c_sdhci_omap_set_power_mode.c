#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sdhci_omap_host {scalar_t__ bus_mode; int /*<<< orphan*/  power_mode; } ;

/* Variables and functions */
 scalar_t__ MMC_POWER_OFF ; 
 int /*<<< orphan*/  sdhci_omap_disable_tuning (struct sdhci_omap_host*) ; 

__attribute__((used)) static void sdhci_omap_set_power_mode(struct sdhci_omap_host *omap_host,
				      u8 power_mode)
{
	if (omap_host->bus_mode == MMC_POWER_OFF)
		sdhci_omap_disable_tuning(omap_host);
	omap_host->power_mode = power_mode;
}