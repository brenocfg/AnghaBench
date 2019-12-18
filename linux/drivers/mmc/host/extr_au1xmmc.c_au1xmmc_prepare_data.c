#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct scatterlist {int length; } ;
struct mmc_data {int blocks; int blksz; int flags; int /*<<< orphan*/  sg_len; struct scatterlist* sg; } ;
struct TYPE_6__ {int len; int /*<<< orphan*/  dir; } ;
struct TYPE_5__ {int len; scalar_t__ offset; scalar_t__ index; } ;
struct au1xmmc_host {int flags; TYPE_3__ dma; int /*<<< orphan*/  mmc; TYPE_2__ pio; TYPE_1__* mrq; } ;
struct TYPE_4__ {scalar_t__ stop; } ;

/* Variables and functions */
 scalar_t__ DDMA_FLAGS_IE ; 
 scalar_t__ DDMA_FLAGS_NOIE ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 scalar_t__ DMA_CHANNEL (struct au1xmmc_host*) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HOST_BLKSIZE (struct au1xmmc_host*) ; 
 int HOST_F_DBDMA ; 
 int HOST_F_DMA ; 
 int HOST_F_RECV ; 
 int HOST_F_STOP ; 
 int HOST_F_XMIT ; 
 int /*<<< orphan*/  IRQ_ON (struct au1xmmc_host*,int /*<<< orphan*/ ) ; 
 int MMC_DATA_READ ; 
 int /*<<< orphan*/  SD_CONFIG_NE ; 
 int /*<<< orphan*/  SD_CONFIG_TH ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 scalar_t__ au1xxx_dbdma_put_dest (scalar_t__,int /*<<< orphan*/ ,int,scalar_t__) ; 
 scalar_t__ au1xxx_dbdma_put_source (scalar_t__,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  au1xxx_dbdma_stop (scalar_t__) ; 
 int dma_map_sg (int /*<<< orphan*/ ,struct scatterlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,struct scatterlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_phys (struct scatterlist*) ; 

__attribute__((used)) static int au1xmmc_prepare_data(struct au1xmmc_host *host,
				struct mmc_data *data)
{
	int datalen = data->blocks * data->blksz;

	if (data->flags & MMC_DATA_READ)
		host->flags |= HOST_F_RECV;
	else
		host->flags |= HOST_F_XMIT;

	if (host->mrq->stop)
		host->flags |= HOST_F_STOP;

	host->dma.dir = DMA_BIDIRECTIONAL;

	host->dma.len = dma_map_sg(mmc_dev(host->mmc), data->sg,
				   data->sg_len, host->dma.dir);

	if (host->dma.len == 0)
		return -ETIMEDOUT;

	__raw_writel(data->blksz - 1, HOST_BLKSIZE(host));

	if (host->flags & (HOST_F_DMA | HOST_F_DBDMA)) {
		int i;
		u32 channel = DMA_CHANNEL(host);

		au1xxx_dbdma_stop(channel);

		for (i = 0; i < host->dma.len; i++) {
			u32 ret = 0, flags = DDMA_FLAGS_NOIE;
			struct scatterlist *sg = &data->sg[i];
			int sg_len = sg->length;

			int len = (datalen > sg_len) ? sg_len : datalen;

			if (i == host->dma.len - 1)
				flags = DDMA_FLAGS_IE;

			if (host->flags & HOST_F_XMIT) {
				ret = au1xxx_dbdma_put_source(channel,
					sg_phys(sg), len, flags);
			} else {
				ret = au1xxx_dbdma_put_dest(channel,
					sg_phys(sg), len, flags);
			}

			if (!ret)
				goto dataerr;

			datalen -= len;
		}
	} else {
		host->pio.index = 0;
		host->pio.offset = 0;
		host->pio.len = datalen;

		if (host->flags & HOST_F_XMIT)
			IRQ_ON(host, SD_CONFIG_TH);
		else
			IRQ_ON(host, SD_CONFIG_NE);
			/* IRQ_ON(host, SD_CONFIG_RA | SD_CONFIG_RF); */
	}

	return 0;

dataerr:
	dma_unmap_sg(mmc_dev(host->mmc), data->sg, data->sg_len,
			host->dma.dir);
	return -ETIMEDOUT;
}