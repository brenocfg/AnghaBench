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
struct iio_dma_buffer_queue {int /*<<< orphan*/  buffer; } ;
struct dmaengine_buffer {int /*<<< orphan*/  active; int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmaengine_terminate_sync (int /*<<< orphan*/ ) ; 
 struct dmaengine_buffer* iio_buffer_to_dmaengine_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_dma_buffer_block_list_abort (struct iio_dma_buffer_queue*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iio_dmaengine_buffer_abort(struct iio_dma_buffer_queue *queue)
{
	struct dmaengine_buffer *dmaengine_buffer =
		iio_buffer_to_dmaengine_buffer(&queue->buffer);

	dmaengine_terminate_sync(dmaengine_buffer->chan);
	iio_dma_buffer_block_list_abort(queue, &dmaengine_buffer->active);
}