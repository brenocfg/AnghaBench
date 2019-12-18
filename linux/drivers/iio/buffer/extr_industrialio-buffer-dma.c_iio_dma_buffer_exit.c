#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * active_block; TYPE_2__** blocks; } ;
struct iio_dma_buffer_queue {int /*<<< orphan*/  lock; int /*<<< orphan*/ * ops; TYPE_1__ fileio; int /*<<< orphan*/  incoming; int /*<<< orphan*/  list_lock; int /*<<< orphan*/  outgoing; } ;
struct TYPE_5__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_2__**) ; 
 int /*<<< orphan*/  IIO_BLOCK_STATE_DEAD ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_buffer_block_put (TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void iio_dma_buffer_exit(struct iio_dma_buffer_queue *queue)
{
	unsigned int i;

	mutex_lock(&queue->lock);

	spin_lock_irq(&queue->list_lock);
	for (i = 0; i < ARRAY_SIZE(queue->fileio.blocks); i++) {
		if (!queue->fileio.blocks[i])
			continue;
		queue->fileio.blocks[i]->state = IIO_BLOCK_STATE_DEAD;
	}
	INIT_LIST_HEAD(&queue->outgoing);
	spin_unlock_irq(&queue->list_lock);

	INIT_LIST_HEAD(&queue->incoming);

	for (i = 0; i < ARRAY_SIZE(queue->fileio.blocks); i++) {
		if (!queue->fileio.blocks[i])
			continue;
		iio_buffer_block_put(queue->fileio.blocks[i]);
		queue->fileio.blocks[i] = NULL;
	}
	queue->fileio.active_block = NULL;
	queue->ops = NULL;

	mutex_unlock(&queue->lock);
}