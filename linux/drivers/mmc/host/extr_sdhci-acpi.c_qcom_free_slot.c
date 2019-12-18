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
struct sdhci_host {int dummy; } ;
struct sdhci_acpi_host {struct sdhci_host* host; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (struct device*) ; 
 int ENODEV ; 
 char* acpi_device_hid (struct acpi_device*) ; 
 int /*<<< orphan*/  free_irq (int,struct sdhci_host*) ; 
 struct sdhci_acpi_host* platform_get_drvdata (struct platform_device*) ; 
 int* sdhci_acpi_priv (struct sdhci_acpi_host*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int qcom_free_slot(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct sdhci_acpi_host *c = platform_get_drvdata(pdev);
	struct sdhci_host *host = c->host;
	struct acpi_device *adev;
	int *irq = sdhci_acpi_priv(c);
	const char *hid;

	adev = ACPI_COMPANION(dev);
	if (!adev)
		return -ENODEV;

	hid = acpi_device_hid(adev);
	if (strcmp(hid, "QCOM8051"))
		return 0;

	if (*irq < 0)
		return 0;

	free_irq(*irq, host);
	return 0;
}