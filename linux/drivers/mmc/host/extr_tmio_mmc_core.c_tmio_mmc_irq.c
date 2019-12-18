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
struct tmio_mmc_host {unsigned int sdcard_irq_mask; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_STATUS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned int TMIO_MASK_IRQ ; 
 scalar_t__ __tmio_mmc_card_detect_irq (struct tmio_mmc_host*,unsigned int,unsigned int) ; 
 scalar_t__ __tmio_mmc_sdcard_irq (struct tmio_mmc_host*,unsigned int,unsigned int) ; 
 scalar_t__ __tmio_mmc_sdio_irq (struct tmio_mmc_host*) ; 
 unsigned int sd_ctrl_read16_and_16_as_32 (struct tmio_mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_ctrl_write32_as_16_and_16 (struct tmio_mmc_host*,int /*<<< orphan*/ ,unsigned int) ; 

irqreturn_t tmio_mmc_irq(int irq, void *devid)
{
	struct tmio_mmc_host *host = devid;
	unsigned int ireg, status;

	status = sd_ctrl_read16_and_16_as_32(host, CTL_STATUS);
	ireg = status & TMIO_MASK_IRQ & ~host->sdcard_irq_mask;

	/* Clear the status except the interrupt status */
	sd_ctrl_write32_as_16_and_16(host, CTL_STATUS, TMIO_MASK_IRQ);

	if (__tmio_mmc_card_detect_irq(host, ireg, status))
		return IRQ_HANDLED;
	if (__tmio_mmc_sdcard_irq(host, ireg, status))
		return IRQ_HANDLED;

	if (__tmio_mmc_sdio_irq(host))
		return IRQ_HANDLED;

	return IRQ_NONE;
}