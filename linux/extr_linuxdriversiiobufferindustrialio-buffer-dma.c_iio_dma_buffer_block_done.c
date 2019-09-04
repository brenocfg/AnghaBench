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
struct TYPE_2__ {int /*<<< orphan*/  pollq; } ;
struct iio_dma_buffer_queue {TYPE_1__ buffer; int /*<<< orphan*/  list_lock; } ;
struct iio_dma_buffer_block {struct iio_dma_buffer_queue* queue; } ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  _iio_dma_buffer_block_done (struct iio_dma_buffer_block*) ; 
 int /*<<< orphan*/  iio_buffer_block_put_atomic (struct iio_dma_buffer_block*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible_poll (int /*<<< orphan*/ *,int) ; 

void iio_dma_buffer_block_done(struct iio_dma_buffer_block *block)
{
	struct iio_dma_buffer_queue *queue = block->queue;
	unsigned long flags;

	spin_lock_irqsave(&queue->list_lock, flags);
	_iio_dma_buffer_block_done(block);
	spin_unlock_irqrestore(&queue->list_lock, flags);

	iio_buffer_block_put_atomic(block);
	wake_up_interruptible_poll(&queue->buffer.pollq, EPOLLIN | EPOLLRDNORM);
}