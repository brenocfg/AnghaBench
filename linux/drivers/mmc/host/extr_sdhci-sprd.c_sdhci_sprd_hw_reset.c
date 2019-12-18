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
struct sdhci_host {scalar_t__ ioaddr; } ;

/* Variables and functions */
 int SDHCI_HW_RESET_CARD ; 
 scalar_t__ SDHCI_SOFTWARE_RESET ; 
 int readb_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writeb_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void sdhci_sprd_hw_reset(struct sdhci_host *host)
{
	int val;

	/*
	 * Note: don't use sdhci_writeb() API here since it is redirected to
	 * sdhci_sprd_writeb() in which we have a workaround for
	 * SDHCI_SOFTWARE_RESET which would make bit SDHCI_HW_RESET_CARD can
	 * not be cleared.
	 */
	val = readb_relaxed(host->ioaddr + SDHCI_SOFTWARE_RESET);
	val &= ~SDHCI_HW_RESET_CARD;
	writeb_relaxed(val, host->ioaddr + SDHCI_SOFTWARE_RESET);
	/* wait for 10 us */
	usleep_range(10, 20);

	val |= SDHCI_HW_RESET_CARD;
	writeb_relaxed(val, host->ioaddr + SDHCI_SOFTWARE_RESET);
	usleep_range(300, 500);
}