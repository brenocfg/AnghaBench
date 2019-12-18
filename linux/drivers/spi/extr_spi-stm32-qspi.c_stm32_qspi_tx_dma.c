#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct stm32_qspi {int /*<<< orphan*/  ctrl; scalar_t__ io_base; int /*<<< orphan*/  dma_completion; struct dma_chan* dma_chtx; struct dma_chan* dma_chrx; } ;
struct TYPE_2__ {scalar_t__ dir; } ;
struct spi_mem_op {TYPE_1__ data; } ;
struct sg_table {int nents; int /*<<< orphan*/  sgl; } ;
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {int /*<<< orphan*/ * callback_param; int /*<<< orphan*/  callback; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  int /*<<< orphan*/  dma_cookie_t ;

/* Variables and functions */
 int CR_DMAEN ; 
 int DMA_DEV_TO_MEM ; 
 int DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_PREP_INTERRUPT ; 
 int ENOMEM ; 
 int ETIMEDOUT ; 
 scalar_t__ QSPI_CR ; 
 scalar_t__ SPI_MEM_DATA_IN ; 
 int STM32_COMP_TIMEOUT_MS ; 
 int /*<<< orphan*/  dma_async_issue_pending (struct dma_chan*) ; 
 int dma_submit_error (int /*<<< orphan*/ ) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_sg (struct dma_chan*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (struct dma_chan*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int spi_controller_dma_map_mem_op_data (int /*<<< orphan*/ ,struct spi_mem_op const*,struct sg_table*) ; 
 int /*<<< orphan*/  spi_controller_dma_unmap_mem_op_data (int /*<<< orphan*/ ,struct spi_mem_op const*,struct sg_table*) ; 
 int /*<<< orphan*/  stm32_qspi_dma_callback ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int stm32_qspi_tx_dma(struct stm32_qspi *qspi,
			     const struct spi_mem_op *op)
{
	struct dma_async_tx_descriptor *desc;
	enum dma_transfer_direction dma_dir;
	struct dma_chan *dma_ch;
	struct sg_table sgt;
	dma_cookie_t cookie;
	u32 cr, t_out;
	int err;

	if (op->data.dir == SPI_MEM_DATA_IN) {
		dma_dir = DMA_DEV_TO_MEM;
		dma_ch = qspi->dma_chrx;
	} else {
		dma_dir = DMA_MEM_TO_DEV;
		dma_ch = qspi->dma_chtx;
	}

	/*
	 * spi_map_buf return -EINVAL if the buffer is not DMA-able
	 * (DMA-able: in vmalloc | kmap | virt_addr_valid)
	 */
	err = spi_controller_dma_map_mem_op_data(qspi->ctrl, op, &sgt);
	if (err)
		return err;

	desc = dmaengine_prep_slave_sg(dma_ch, sgt.sgl, sgt.nents,
				       dma_dir, DMA_PREP_INTERRUPT);
	if (!desc) {
		err = -ENOMEM;
		goto out_unmap;
	}

	cr = readl_relaxed(qspi->io_base + QSPI_CR);

	reinit_completion(&qspi->dma_completion);
	desc->callback = stm32_qspi_dma_callback;
	desc->callback_param = &qspi->dma_completion;
	cookie = dmaengine_submit(desc);
	err = dma_submit_error(cookie);
	if (err)
		goto out;

	dma_async_issue_pending(dma_ch);

	writel_relaxed(cr | CR_DMAEN, qspi->io_base + QSPI_CR);

	t_out = sgt.nents * STM32_COMP_TIMEOUT_MS;
	if (!wait_for_completion_timeout(&qspi->dma_completion,
					 msecs_to_jiffies(t_out)))
		err = -ETIMEDOUT;

	if (err)
		dmaengine_terminate_all(dma_ch);

out:
	writel_relaxed(cr & ~CR_DMAEN, qspi->io_base + QSPI_CR);
out_unmap:
	spi_controller_dma_unmap_mem_op_data(qspi->ctrl, op, &sgt);

	return err;
}