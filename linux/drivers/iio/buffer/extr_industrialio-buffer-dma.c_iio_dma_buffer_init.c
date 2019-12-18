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
struct TYPE_2__ {int length; int watermark; } ;
struct iio_dma_buffer_queue {int /*<<< orphan*/  list_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  outgoing; int /*<<< orphan*/  incoming; struct iio_dma_buffer_ops const* ops; struct device* dev; TYPE_1__ buffer; } ;
struct iio_dma_buffer_ops {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  iio_buffer_init (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int iio_dma_buffer_init(struct iio_dma_buffer_queue *queue,
	struct device *dev, const struct iio_dma_buffer_ops *ops)
{
	iio_buffer_init(&queue->buffer);
	queue->buffer.length = PAGE_SIZE;
	queue->buffer.watermark = queue->buffer.length / 2;
	queue->dev = dev;
	queue->ops = ops;

	INIT_LIST_HEAD(&queue->incoming);
	INIT_LIST_HEAD(&queue->outgoing);

	mutex_init(&queue->lock);
	spin_lock_init(&queue->list_lock);

	return 0;
}