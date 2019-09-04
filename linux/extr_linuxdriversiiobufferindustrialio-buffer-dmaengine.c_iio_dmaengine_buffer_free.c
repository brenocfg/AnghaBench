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
struct iio_buffer {int dummy; } ;
struct dmaengine_buffer {int /*<<< orphan*/  chan; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_buffer_put (struct iio_buffer*) ; 
 struct dmaengine_buffer* iio_buffer_to_dmaengine_buffer (struct iio_buffer*) ; 
 int /*<<< orphan*/  iio_dma_buffer_exit (int /*<<< orphan*/ *) ; 

void iio_dmaengine_buffer_free(struct iio_buffer *buffer)
{
	struct dmaengine_buffer *dmaengine_buffer =
		iio_buffer_to_dmaengine_buffer(buffer);

	iio_dma_buffer_exit(&dmaengine_buffer->queue);
	dma_release_channel(dmaengine_buffer->chan);

	iio_buffer_put(buffer);
}