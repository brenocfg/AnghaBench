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
struct scatterlist {int dummy; } ;
struct mxs_ssp {int /*<<< orphan*/  dma_dir; int /*<<< orphan*/  slave_dirn; int /*<<< orphan*/  dmach; scalar_t__ ssp_pio_words; } ;
struct mxs_mmc_host {int /*<<< orphan*/  mmc; struct mmc_data* data; struct mxs_ssp ssp; } ;
struct mmc_data {unsigned int sg_len; struct scatterlist* sg; } ;
struct dma_async_tx_descriptor {struct mxs_mmc_host* callback_param; int /*<<< orphan*/  callback; } ;

/* Variables and functions */
 unsigned int SSP_PIO_NUM ; 
 int /*<<< orphan*/  dma_map_sg (int /*<<< orphan*/ ,struct scatterlist*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,struct scatterlist*,unsigned int,int /*<<< orphan*/ ) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_sg (int /*<<< orphan*/ ,struct scatterlist*,unsigned int,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxs_mmc_dma_irq_callback ; 

__attribute__((used)) static struct dma_async_tx_descriptor *mxs_mmc_prep_dma(
	struct mxs_mmc_host *host, unsigned long flags)
{
	struct mxs_ssp *ssp = &host->ssp;
	struct dma_async_tx_descriptor *desc;
	struct mmc_data *data = host->data;
	struct scatterlist * sgl;
	unsigned int sg_len;

	if (data) {
		/* data */
		dma_map_sg(mmc_dev(host->mmc), data->sg,
			   data->sg_len, ssp->dma_dir);
		sgl = data->sg;
		sg_len = data->sg_len;
	} else {
		/* pio */
		sgl = (struct scatterlist *) ssp->ssp_pio_words;
		sg_len = SSP_PIO_NUM;
	}

	desc = dmaengine_prep_slave_sg(ssp->dmach,
				sgl, sg_len, ssp->slave_dirn, flags);
	if (desc) {
		desc->callback = mxs_mmc_dma_irq_callback;
		desc->callback_param = host;
	} else {
		if (data)
			dma_unmap_sg(mmc_dev(host->mmc), data->sg,
				     data->sg_len, ssp->dma_dir);
	}

	return desc;
}