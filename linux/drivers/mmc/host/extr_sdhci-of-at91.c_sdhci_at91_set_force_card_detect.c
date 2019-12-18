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
struct sdhci_host {scalar_t__ ioaddr; } ;

/* Variables and functions */
 scalar_t__ SDMMC_MC1R ; 
 int /*<<< orphan*/  SDMMC_MC1R_FCD ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sdhci_at91_set_force_card_detect(struct sdhci_host *host)
{
	u8 mc1r;

	mc1r = readb(host->ioaddr + SDMMC_MC1R);
	mc1r |= SDMMC_MC1R_FCD;
	writeb(mc1r, host->ioaddr + SDMMC_MC1R);
}