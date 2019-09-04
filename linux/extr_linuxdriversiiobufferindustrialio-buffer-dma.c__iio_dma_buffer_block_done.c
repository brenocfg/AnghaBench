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
struct iio_dma_buffer_queue {int /*<<< orphan*/  outgoing; } ;
struct iio_dma_buffer_block {scalar_t__ state; int /*<<< orphan*/  head; struct iio_dma_buffer_queue* queue; } ;

/* Variables and functions */
 scalar_t__ IIO_BLOCK_STATE_DEAD ; 
 scalar_t__ IIO_BLOCK_STATE_DONE ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _iio_dma_buffer_block_done(struct iio_dma_buffer_block *block)
{
	struct iio_dma_buffer_queue *queue = block->queue;

	/*
	 * The buffer has already been freed by the application, just drop the
	 * reference.
	 */
	if (block->state != IIO_BLOCK_STATE_DEAD) {
		block->state = IIO_BLOCK_STATE_DONE;
		list_add_tail(&block->head, &queue->outgoing);
	}
}