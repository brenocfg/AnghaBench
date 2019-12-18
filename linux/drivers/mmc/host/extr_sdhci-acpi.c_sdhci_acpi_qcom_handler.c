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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  VENDOR_SPECIFIC_PWRCTL_CLEAR_REG ; 
 int /*<<< orphan*/  VENDOR_SPECIFIC_PWRCTL_CTL_REG ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t sdhci_acpi_qcom_handler(int irq, void *ptr)
{
	struct sdhci_host *host = ptr;

	sdhci_writel(host, 0x3, VENDOR_SPECIFIC_PWRCTL_CLEAR_REG);
	sdhci_writel(host, 0x1, VENDOR_SPECIFIC_PWRCTL_CTL_REG);

	return IRQ_HANDLED;
}