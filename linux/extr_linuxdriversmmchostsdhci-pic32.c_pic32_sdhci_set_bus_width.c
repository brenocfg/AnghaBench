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
struct sdhci_host {scalar_t__ version; } ;

/* Variables and functions */
 int MMC_BUS_WIDTH_4 ; 
 int MMC_BUS_WIDTH_8 ; 
 int /*<<< orphan*/  SDHCI_CTRL_4BITBUS ; 
 int /*<<< orphan*/  SDHCI_CTRL_8BITBUS ; 
 int /*<<< orphan*/  SDHCI_CTRL_CDSSEL ; 
 int /*<<< orphan*/  SDHCI_CTRL_CDTLVL ; 
 int /*<<< orphan*/  SDHCI_HOST_CONTROL ; 
 scalar_t__ SDHCI_SPEC_300 ; 
 int /*<<< orphan*/  sdhci_readb (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writeb (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pic32_sdhci_set_bus_width(struct sdhci_host *host, int width)
{
	u8 ctrl;

	ctrl = sdhci_readb(host, SDHCI_HOST_CONTROL);
	if (width == MMC_BUS_WIDTH_8) {
		ctrl &= ~SDHCI_CTRL_4BITBUS;
		if (host->version >= SDHCI_SPEC_300)
			ctrl |= SDHCI_CTRL_8BITBUS;
	} else {
		if (host->version >= SDHCI_SPEC_300)
			ctrl &= ~SDHCI_CTRL_8BITBUS;
		if (width == MMC_BUS_WIDTH_4)
			ctrl |= SDHCI_CTRL_4BITBUS;
		else
			ctrl &= ~SDHCI_CTRL_4BITBUS;
	}

	/* CD select and test bits must be set for errata workaround. */
	ctrl &= ~SDHCI_CTRL_CDTLVL;
	ctrl |= SDHCI_CTRL_CDSSEL;
	sdhci_writeb(host, ctrl, SDHCI_HOST_CONTROL);
}