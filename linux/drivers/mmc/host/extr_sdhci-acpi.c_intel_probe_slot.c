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
struct TYPE_2__ {int /*<<< orphan*/  start_signal_voltage_switch; int /*<<< orphan*/  get_cd; } ;
struct sdhci_host {int timeout_clk; TYPE_1__ mmc_host_ops; int /*<<< orphan*/  mmc; } ;
struct sdhci_acpi_host {struct sdhci_host* host; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct intel_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDHCI_CAPABILITIES ; 
 int /*<<< orphan*/  SDHCI_CAPABILITIES_1 ; 
 int /*<<< orphan*/  bxt_get_cd ; 
 int /*<<< orphan*/  intel_dsm_init (struct intel_host*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_start_signal_voltage_switch ; 
 struct sdhci_acpi_host* platform_get_drvdata (struct platform_device*) ; 
 struct intel_host* sdhci_acpi_priv (struct sdhci_acpi_host*) ; 
 int sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int intel_probe_slot(struct platform_device *pdev, const char *hid,
			    const char *uid)
{
	struct sdhci_acpi_host *c = platform_get_drvdata(pdev);
	struct intel_host *intel_host = sdhci_acpi_priv(c);
	struct sdhci_host *host = c->host;

	if (hid && uid && !strcmp(hid, "80860F14") && !strcmp(uid, "1") &&
	    sdhci_readl(host, SDHCI_CAPABILITIES) == 0x446cc8b2 &&
	    sdhci_readl(host, SDHCI_CAPABILITIES_1) == 0x00000807)
		host->timeout_clk = 1000; /* 1000 kHz i.e. 1 MHz */

	if (hid && !strcmp(hid, "80865ACA"))
		host->mmc_host_ops.get_cd = bxt_get_cd;

	intel_dsm_init(intel_host, &pdev->dev, host->mmc);

	host->mmc_host_ops.start_signal_voltage_switch =
					intel_start_signal_voltage_switch;

	return 0;
}