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
struct iio_dma_buffer_queue {int /*<<< orphan*/  buffer; } ;
struct iio_dma_buffer_block {int /*<<< orphan*/  head; int /*<<< orphan*/  bytes_used; int /*<<< orphan*/  phys_addr; int /*<<< orphan*/  size; } ;
struct TYPE_2__ {int /*<<< orphan*/  list_lock; } ;
struct dmaengine_buffer {int /*<<< orphan*/  chan; TYPE_1__ queue; int /*<<< orphan*/  active; int /*<<< orphan*/  align; int /*<<< orphan*/  max_size; } ;
struct dma_async_tx_descriptor {struct iio_dma_buffer_block* callback_param; int /*<<< orphan*/  callback; } ;
typedef  int /*<<< orphan*/  dma_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_PREP_INTERRUPT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 
 int dma_submit_error (int /*<<< orphan*/ ) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 struct dmaengine_buffer* iio_buffer_to_dmaengine_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_dmaengine_buffer_block_done ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rounddown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iio_dmaengine_buffer_submit_block(struct iio_dma_buffer_queue *queue,
	struct iio_dma_buffer_block *block)
{
	struct dmaengine_buffer *dmaengine_buffer =
		iio_buffer_to_dmaengine_buffer(&queue->buffer);
	struct dma_async_tx_descriptor *desc;
	dma_cookie_t cookie;

	block->bytes_used = min(block->size, dmaengine_buffer->max_size);
	block->bytes_used = rounddown(block->bytes_used,
			dmaengine_buffer->align);

	desc = dmaengine_prep_slave_single(dmaengine_buffer->chan,
		block->phys_addr, block->bytes_used, DMA_DEV_TO_MEM,
		DMA_PREP_INTERRUPT);
	if (!desc)
		return -ENOMEM;

	desc->callback = iio_dmaengine_buffer_block_done;
	desc->callback_param = block;

	cookie = dmaengine_submit(desc);
	if (dma_submit_error(cookie))
		return dma_submit_error(cookie);

	spin_lock_irq(&dmaengine_buffer->queue.list_lock);
	list_add_tail(&block->head, &dmaengine_buffer->active);
	spin_unlock_irq(&dmaengine_buffer->queue.list_lock);

	dma_async_issue_pending(dmaengine_buffer->chan);

	return 0;
}