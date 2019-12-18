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
struct spi_qup {int dummy; } ;
struct spi_master {struct dma_chan* dma_rx; struct dma_chan* dma_tx; } ;
struct scatterlist {int dummy; } ;
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {struct spi_qup* callback_param; int /*<<< orphan*/  callback; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  int /*<<< orphan*/  dma_cookie_t ;
typedef  int /*<<< orphan*/  dma_async_tx_callback ;

/* Variables and functions */
 int DMA_MEM_TO_DEV ; 
 unsigned long DMA_PREP_FENCE ; 
 unsigned long DMA_PREP_INTERRUPT ; 
 int EINVAL ; 
 scalar_t__ IS_ERR_OR_NULL (struct dma_async_tx_descriptor*) ; 
 int PTR_ERR (struct dma_async_tx_descriptor*) ; 
 int dma_submit_error (int /*<<< orphan*/ ) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_sg (struct dma_chan*,struct scatterlist*,unsigned int,int,unsigned long) ; 
 int /*<<< orphan*/  dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 struct spi_qup* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int spi_qup_prep_sg(struct spi_master *master, struct scatterlist *sgl,
			   unsigned int nents, enum dma_transfer_direction dir,
			   dma_async_tx_callback callback)
{
	struct spi_qup *qup = spi_master_get_devdata(master);
	unsigned long flags = DMA_PREP_INTERRUPT | DMA_PREP_FENCE;
	struct dma_async_tx_descriptor *desc;
	struct dma_chan *chan;
	dma_cookie_t cookie;

	if (dir == DMA_MEM_TO_DEV)
		chan = master->dma_tx;
	else
		chan = master->dma_rx;

	desc = dmaengine_prep_slave_sg(chan, sgl, nents, dir, flags);
	if (IS_ERR_OR_NULL(desc))
		return desc ? PTR_ERR(desc) : -EINVAL;

	desc->callback = callback;
	desc->callback_param = qup;

	cookie = dmaengine_submit(desc);

	return dma_submit_error(cookie);
}