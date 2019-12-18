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

/* Variables and functions */
 int /*<<< orphan*/  SDHCI_AMD_RESET_DLL_REGISTER ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void sdhci_acpi_amd_hs400_dll(struct sdhci_host *host)
{
	/* AMD Platform requires dll setting */
	sdhci_writel(host, 0x40003210, SDHCI_AMD_RESET_DLL_REGISTER);
	usleep_range(10, 20);
	sdhci_writel(host, 0x40033210, SDHCI_AMD_RESET_DLL_REGISTER);
}