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
struct TYPE_4__ {size_t block_size; struct iio_dma_buffer_block** blocks; int /*<<< orphan*/ * active_block; } ;
struct TYPE_3__ {int bytes_per_datum; int length; } ;
struct iio_dma_buffer_queue {int /*<<< orphan*/  lock; int /*<<< orphan*/  incoming; TYPE_2__ fileio; int /*<<< orphan*/  list_lock; int /*<<< orphan*/  outgoing; TYPE_1__ buffer; } ;
struct iio_dma_buffer_block {scalar_t__ state; size_t size; int /*<<< orphan*/  head; } ;
struct iio_buffer {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct iio_dma_buffer_block**) ; 
 size_t DIV_ROUND_UP (int,int) ; 
 int ENOMEM ; 
 scalar_t__ IIO_BLOCK_STATE_DEAD ; 
 scalar_t__ IIO_BLOCK_STATE_QUEUED ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ PAGE_ALIGN (size_t) ; 
 int /*<<< orphan*/  iio_buffer_block_put (struct iio_dma_buffer_block*) ; 
 struct iio_dma_buffer_queue* iio_buffer_to_queue (struct iio_buffer*) ; 
 int /*<<< orphan*/  iio_dma_block_reusable (struct iio_dma_buffer_block*) ; 
 struct iio_dma_buffer_block* iio_dma_buffer_alloc_block (struct iio_dma_buffer_queue*,size_t) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int iio_dma_buffer_request_update(struct iio_buffer *buffer)
{
	struct iio_dma_buffer_queue *queue = iio_buffer_to_queue(buffer);
	struct iio_dma_buffer_block *block;
	bool try_reuse = false;
	size_t size;
	int ret = 0;
	int i;

	/*
	 * Split the buffer into two even parts. This is used as a double
	 * buffering scheme with usually one block at a time being used by the
	 * DMA and the other one by the application.
	 */
	size = DIV_ROUND_UP(queue->buffer.bytes_per_datum *
		queue->buffer.length, 2);

	mutex_lock(&queue->lock);

	/* Allocations are page aligned */
	if (PAGE_ALIGN(queue->fileio.block_size) == PAGE_ALIGN(size))
		try_reuse = true;

	queue->fileio.block_size = size;
	queue->fileio.active_block = NULL;

	spin_lock_irq(&queue->list_lock);
	for (i = 0; i < ARRAY_SIZE(queue->fileio.blocks); i++) {
		block = queue->fileio.blocks[i];

		/* If we can't re-use it free it */
		if (block && (!iio_dma_block_reusable(block) || !try_reuse))
			block->state = IIO_BLOCK_STATE_DEAD;
	}

	/*
	 * At this point all blocks are either owned by the core or marked as
	 * dead. This means we can reset the lists without having to fear
	 * corrution.
	 */
	INIT_LIST_HEAD(&queue->outgoing);
	spin_unlock_irq(&queue->list_lock);

	INIT_LIST_HEAD(&queue->incoming);

	for (i = 0; i < ARRAY_SIZE(queue->fileio.blocks); i++) {
		if (queue->fileio.blocks[i]) {
			block = queue->fileio.blocks[i];
			if (block->state == IIO_BLOCK_STATE_DEAD) {
				/* Could not reuse it */
				iio_buffer_block_put(block);
				block = NULL;
			} else {
				block->size = size;
			}
		} else {
			block = NULL;
		}

		if (!block) {
			block = iio_dma_buffer_alloc_block(queue, size);
			if (!block) {
				ret = -ENOMEM;
				goto out_unlock;
			}
			queue->fileio.blocks[i] = block;
		}

		block->state = IIO_BLOCK_STATE_QUEUED;
		list_add_tail(&block->head, &queue->incoming);
	}

out_unlock:
	mutex_unlock(&queue->lock);

	return ret;
}