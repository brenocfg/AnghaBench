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
struct iio_dma_buffer_queue {TYPE_1__* ops; } ;
struct iio_dma_buffer_block {int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int (* submit ) (struct iio_dma_buffer_queue*,struct iio_dma_buffer_block*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IIO_BLOCK_STATE_ACTIVE ; 
 int /*<<< orphan*/  iio_buffer_block_get (struct iio_dma_buffer_block*) ; 
 int /*<<< orphan*/  iio_buffer_block_put (struct iio_dma_buffer_block*) ; 
 int stub1 (struct iio_dma_buffer_queue*,struct iio_dma_buffer_block*) ; 

__attribute__((used)) static void iio_dma_buffer_submit_block(struct iio_dma_buffer_queue *queue,
	struct iio_dma_buffer_block *block)
{
	int ret;

	/*
	 * If the hardware has already been removed we put the block into
	 * limbo. It will neither be on the incoming nor outgoing list, nor will
	 * it ever complete. It will just wait to be freed eventually.
	 */
	if (!queue->ops)
		return;

	block->state = IIO_BLOCK_STATE_ACTIVE;
	iio_buffer_block_get(block);
	ret = queue->ops->submit(queue, block);
	if (ret) {
		/*
		 * This is a bit of a problem and there is not much we can do
		 * other then wait for the buffer to be disabled and re-enabled
		 * and try again. But it should not really happen unless we run
		 * out of memory or something similar.
		 *
		 * TODO: Implement support in the IIO core to allow buffers to
		 * notify consumers that something went wrong and the buffer
		 * should be disabled.
		 */
		iio_buffer_block_put(block);
	}
}