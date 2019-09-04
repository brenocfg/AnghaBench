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
struct tmio_mmc_host {unsigned int sdio_irq_mask; struct tmio_mmc_data* pdata; struct mmc_host* mmc; } ;
struct tmio_mmc_data {int flags; } ;
struct mmc_host {int caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_SDIO_STATUS ; 
 int MMC_CAP_SDIO_IRQ ; 
 int TMIO_MMC_SDIO_IRQ ; 
 int TMIO_MMC_SDIO_STATUS_SETBITS ; 
 unsigned int TMIO_SDIO_MASK_ALL ; 
 unsigned int TMIO_SDIO_SETBITS_MASK ; 
 unsigned int TMIO_SDIO_STAT_IOIRQ ; 
 int /*<<< orphan*/  mmc_signal_sdio_irq (struct mmc_host*) ; 
 unsigned int sd_ctrl_read16 (struct tmio_mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_ctrl_write16 (struct tmio_mmc_host*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static bool __tmio_mmc_sdio_irq(struct tmio_mmc_host *host)
{
	struct mmc_host *mmc = host->mmc;
	struct tmio_mmc_data *pdata = host->pdata;
	unsigned int ireg, status;
	unsigned int sdio_status;

	if (!(pdata->flags & TMIO_MMC_SDIO_IRQ))
		return false;

	status = sd_ctrl_read16(host, CTL_SDIO_STATUS);
	ireg = status & TMIO_SDIO_MASK_ALL & ~host->sdio_irq_mask;

	sdio_status = status & ~TMIO_SDIO_MASK_ALL;
	if (pdata->flags & TMIO_MMC_SDIO_STATUS_SETBITS)
		sdio_status |= TMIO_SDIO_SETBITS_MASK;

	sd_ctrl_write16(host, CTL_SDIO_STATUS, sdio_status);

	if (mmc->caps & MMC_CAP_SDIO_IRQ && ireg & TMIO_SDIO_STAT_IOIRQ)
		mmc_signal_sdio_irq(mmc);

	return ireg;
}