#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mmc_data {int flags; int blksz; int blocks; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; int /*<<< orphan*/  error; } ;
struct TYPE_4__ {scalar_t__ has_bad_data_ordering; int /*<<< orphan*/  has_rwproof; } ;
struct atmel_mci {int mode_reg; int data_size; int /*<<< orphan*/ * buffer; TYPE_2__ caps; struct mmc_data* data; TYPE_1__* pdev; int /*<<< orphan*/  sg; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ATMCI_BLKE ; 
 int ATMCI_BLKLEN (int) ; 
 int ATMCI_DATA_ERROR_FLAGS ; 
 int ATMCI_ENDRX ; 
 int ATMCI_ENDTX ; 
 int /*<<< orphan*/  ATMCI_MR ; 
 int ATMCI_MR_PDCMODE ; 
 int ATMCI_RXBUFF ; 
 int ATMCI_TXBUFE ; 
 int /*<<< orphan*/  EINPROGRESS ; 
 int MMC_DATA_READ ; 
 int MMC_DATA_WRITE ; 
 int /*<<< orphan*/  XFER_RECEIVE ; 
 int /*<<< orphan*/  XFER_TRANSMIT ; 
 int /*<<< orphan*/  atmci_pdc_set_both_buf (struct atmel_mci*,int /*<<< orphan*/ ) ; 
 int atmci_readl (struct atmel_mci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmci_writel (struct atmel_mci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dma_map_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_get_dma_dir (struct mmc_data*) ; 
 int /*<<< orphan*/  sg_copy_to_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  swab32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32
atmci_prepare_data_pdc(struct atmel_mci *host, struct mmc_data *data)
{
	u32 iflags, tmp;
	int i;

	data->error = -EINPROGRESS;

	host->data = data;
	host->sg = data->sg;
	iflags = ATMCI_DATA_ERROR_FLAGS;

	/* Enable pdc mode */
	atmci_writel(host, ATMCI_MR, host->mode_reg | ATMCI_MR_PDCMODE);

	if (data->flags & MMC_DATA_READ)
		iflags |= ATMCI_ENDRX | ATMCI_RXBUFF;
	else
		iflags |= ATMCI_ENDTX | ATMCI_TXBUFE | ATMCI_BLKE;

	/* Set BLKLEN */
	tmp = atmci_readl(host, ATMCI_MR);
	tmp &= 0x0000ffff;
	tmp |= ATMCI_BLKLEN(data->blksz);
	atmci_writel(host, ATMCI_MR, tmp);

	/* Configure PDC */
	host->data_size = data->blocks * data->blksz;
	dma_map_sg(&host->pdev->dev, data->sg, data->sg_len,
		   mmc_get_dma_dir(data));

	if ((!host->caps.has_rwproof)
	    && (host->data->flags & MMC_DATA_WRITE)) {
		sg_copy_to_buffer(host->data->sg, host->data->sg_len,
		                  host->buffer, host->data_size);
		if (host->caps.has_bad_data_ordering)
			for (i = 0; i < host->data_size; i++)
				host->buffer[i] = swab32(host->buffer[i]);
	}

	if (host->data_size)
		atmci_pdc_set_both_buf(host, data->flags & MMC_DATA_READ ?
				       XFER_RECEIVE : XFER_TRANSMIT);
	return iflags;
}