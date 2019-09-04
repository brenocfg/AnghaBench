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
typedef  int u8 ;
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 int MMC_BUS_WIDTH_4 ; 
 int MMC_BUS_WIDTH_8 ; 
 int SDHCI_CTRL_4BITBUS ; 
 int /*<<< orphan*/  SDHCI_HOST_CONTROL ; 
 int SDHCI_SIRF_8BITBUS ; 
 int sdhci_readb (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writeb (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdhci_sirf_set_bus_width(struct sdhci_host *host, int width)
{
	u8 ctrl;

	ctrl = sdhci_readb(host, SDHCI_HOST_CONTROL);
	ctrl &= ~(SDHCI_CTRL_4BITBUS | SDHCI_SIRF_8BITBUS);

	/*
	 * CSR atlas7 and prima2 SD host version is not 3.0
	 * 8bit-width enable bit of CSR SD hosts is 3,
	 * while stardard hosts use bit 5
	 */
	if (width == MMC_BUS_WIDTH_8)
		ctrl |= SDHCI_SIRF_8BITBUS;
	else if (width == MMC_BUS_WIDTH_4)
		ctrl |= SDHCI_CTRL_4BITBUS;

	sdhci_writeb(host, ctrl, SDHCI_HOST_CONTROL);
}