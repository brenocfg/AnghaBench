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
struct iio_dma_buffer_queue {int /*<<< orphan*/  incoming; scalar_t__ active; } ;
struct iio_dma_buffer_block {scalar_t__ state; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 scalar_t__ IIO_BLOCK_STATE_DEAD ; 
 scalar_t__ IIO_BLOCK_STATE_QUEUED ; 
 int /*<<< orphan*/  iio_buffer_block_put (struct iio_dma_buffer_block*) ; 
 int /*<<< orphan*/  iio_dma_buffer_submit_block (struct iio_dma_buffer_queue*,struct iio_dma_buffer_block*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iio_dma_buffer_enqueue(struct iio_dma_buffer_queue *queue,
	struct iio_dma_buffer_block *block)
{
	if (block->state == IIO_BLOCK_STATE_DEAD) {
		iio_buffer_block_put(block);
	} else if (queue->active) {
		iio_dma_buffer_submit_block(queue, block);
	} else {
		block->state = IIO_BLOCK_STATE_QUEUED;
		list_add_tail(&block->head, &queue->incoming);
	}
}