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
struct iio_dma_buffer_queue {int active; int /*<<< orphan*/  lock; TYPE_1__* ops; } ;
struct iio_dev {int dummy; } ;
struct iio_buffer {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* abort ) (struct iio_dma_buffer_queue*) ;} ;

/* Variables and functions */
 struct iio_dma_buffer_queue* iio_buffer_to_queue (struct iio_buffer*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct iio_dma_buffer_queue*) ; 

int iio_dma_buffer_disable(struct iio_buffer *buffer,
	struct iio_dev *indio_dev)
{
	struct iio_dma_buffer_queue *queue = iio_buffer_to_queue(buffer);

	mutex_lock(&queue->lock);
	queue->active = false;

	if (queue->ops && queue->ops->abort)
		queue->ops->abort(queue);
	mutex_unlock(&queue->lock);

	return 0;
}