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
struct mmc_host {int dummy; } ;
struct atmel_mci_slot {int /*<<< orphan*/  sdio_irq; struct atmel_mci* host; } ;
struct atmel_mci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMCI_IDR ; 
 int /*<<< orphan*/  ATMCI_IER ; 
 int /*<<< orphan*/  atmci_writel (struct atmel_mci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct atmel_mci_slot* mmc_priv (struct mmc_host*) ; 

__attribute__((used)) static void atmci_enable_sdio_irq(struct mmc_host *mmc, int enable)
{
	struct atmel_mci_slot	*slot = mmc_priv(mmc);
	struct atmel_mci	*host = slot->host;

	if (enable)
		atmci_writel(host, ATMCI_IER, slot->sdio_irq);
	else
		atmci_writel(host, ATMCI_IDR, slot->sdio_irq);
}