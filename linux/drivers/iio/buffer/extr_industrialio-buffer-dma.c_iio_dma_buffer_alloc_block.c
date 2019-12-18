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
struct iio_dma_buffer_queue {int /*<<< orphan*/  buffer; int /*<<< orphan*/  dev; } ;
struct iio_dma_buffer_block {size_t size; int /*<<< orphan*/  kref; int /*<<< orphan*/  head; struct iio_dma_buffer_queue* queue; int /*<<< orphan*/  state; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  phys_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IIO_BLOCK_STATE_DEQUEUED ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PAGE_ALIGN (size_t) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_buffer_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct iio_dma_buffer_block*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct iio_dma_buffer_block* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct iio_dma_buffer_block *iio_dma_buffer_alloc_block(
	struct iio_dma_buffer_queue *queue, size_t size)
{
	struct iio_dma_buffer_block *block;

	block = kzalloc(sizeof(*block), GFP_KERNEL);
	if (!block)
		return NULL;

	block->vaddr = dma_alloc_coherent(queue->dev, PAGE_ALIGN(size),
		&block->phys_addr, GFP_KERNEL);
	if (!block->vaddr) {
		kfree(block);
		return NULL;
	}

	block->size = size;
	block->state = IIO_BLOCK_STATE_DEQUEUED;
	block->queue = queue;
	INIT_LIST_HEAD(&block->head);
	kref_init(&block->kref);

	iio_buffer_get(&queue->buffer);

	return block;
}