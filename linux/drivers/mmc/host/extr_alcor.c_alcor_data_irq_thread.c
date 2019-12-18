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
typedef  int u32 ;
struct alcor_sdmmc_host {int /*<<< orphan*/  sg_count; scalar_t__ dma_on; int /*<<< orphan*/  blocks; int /*<<< orphan*/  dev; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int AU6601_INT_DATA_END ; 
 int AU6601_INT_DATA_MASK ; 
 int /*<<< orphan*/  AU6601_RESET_DATA ; 
 scalar_t__ alcor_data_irq_done (struct alcor_sdmmc_host*,int) ; 
 int /*<<< orphan*/  alcor_finish_data (struct alcor_sdmmc_host*) ; 
 int /*<<< orphan*/  alcor_reset (struct alcor_sdmmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void alcor_data_irq_thread(struct alcor_sdmmc_host *host, u32 intmask)
{
	intmask &= AU6601_INT_DATA_MASK;

	if (!intmask)
		return;

	if (!host->data) {
		dev_dbg(host->dev, "Got data interrupt 0x%08x even though no data operation was in progress.\n",
			intmask);
		alcor_reset(host, AU6601_RESET_DATA);
		return;
	}

	if (alcor_data_irq_done(host, intmask))
		return;

	if ((intmask & AU6601_INT_DATA_END) || !host->blocks ||
	    (host->dma_on && !host->sg_count))
		alcor_finish_data(host);
}