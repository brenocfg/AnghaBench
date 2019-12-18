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
struct mmc_data {int flags; scalar_t__ host_cookie; int sg_count; int blksz; } ;
struct alcor_sdmmc_host {int dma_on; struct mmc_data* data; struct alcor_pci_priv* alcor_pci; } ;
struct alcor_pci_priv {int dummy; } ;

/* Variables and functions */
 int AU6601_DATA_DMA_MODE ; 
 int AU6601_DATA_START_XFER ; 
 int AU6601_DATA_WRITE ; 
 int /*<<< orphan*/  AU6601_DATA_XFER_CTRL ; 
 int /*<<< orphan*/  AU6601_REG_BLOCK_SIZE ; 
 scalar_t__ COOKIE_MAPPED ; 
 int MMC_DATA_WRITE ; 
 int /*<<< orphan*/  alcor_data_set_dma (struct alcor_sdmmc_host*) ; 
 int /*<<< orphan*/  alcor_write32 (struct alcor_pci_priv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alcor_write8 (struct alcor_pci_priv*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alcor_trigger_data_transfer(struct alcor_sdmmc_host *host)
{
	struct alcor_pci_priv *priv = host->alcor_pci;
	struct mmc_data *data = host->data;
	u8 ctrl = 0;

	if (data->flags & MMC_DATA_WRITE)
		ctrl |= AU6601_DATA_WRITE;

	if (data->host_cookie == COOKIE_MAPPED) {
		/*
		 * For DMA transfers, this function is called just once,
		 * at the start of the operation. The hardware can only
		 * perform DMA I/O on a single page at a time, so here
		 * we kick off the transfer with the first page, and expect
		 * subsequent pages to be transferred upon IRQ events
		 * indicating that the single-page DMA was completed.
		 */
		alcor_data_set_dma(host);
		ctrl |= AU6601_DATA_DMA_MODE;
		host->dma_on = 1;
		alcor_write32(priv, data->sg_count * 0x1000,
			       AU6601_REG_BLOCK_SIZE);
	} else {
		/*
		 * For PIO transfers, we break down each operation
		 * into several sector-sized transfers. When one sector has
		 * complete, the IRQ handler will call this function again
		 * to kick off the transfer of the next sector.
		 */
		alcor_write32(priv, data->blksz, AU6601_REG_BLOCK_SIZE);
	}

	alcor_write8(priv, ctrl | AU6601_DATA_START_XFER,
		      AU6601_DATA_XFER_CTRL);
}