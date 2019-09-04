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
struct dmaengine_buffer {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 struct dmaengine_buffer* iio_buffer_to_dmaengine_buffer (struct iio_buffer*) ; 
 int /*<<< orphan*/  iio_dma_buffer_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dmaengine_buffer*) ; 

__attribute__((used)) static void iio_dmaengine_buffer_release(struct iio_buffer *buf)
{
	struct dmaengine_buffer *dmaengine_buffer =
		iio_buffer_to_dmaengine_buffer(buf);

	iio_dma_buffer_release(&dmaengine_buffer->queue);
	kfree(dmaengine_buffer);
}