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
struct vb2_queue {int buf_struct_size; scalar_t__ is_output; int /*<<< orphan*/  dma_dir; scalar_t__ bidirectional; int /*<<< orphan*/  memory; int /*<<< orphan*/  done_wq; int /*<<< orphan*/  mmap_lock; int /*<<< orphan*/  done_lock; int /*<<< orphan*/  done_list; int /*<<< orphan*/  queued_list; int /*<<< orphan*/  supports_requests; scalar_t__ requires_requests; TYPE_1__* ops; int /*<<< orphan*/  io_modes; int /*<<< orphan*/  type; int /*<<< orphan*/  mem_ops; } ;
struct vb2_buffer {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  buf_queue; int /*<<< orphan*/  queue_setup; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VB2_MEMORY_UNKNOWN ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int vb2_core_queue_init(struct vb2_queue *q)
{
	/*
	 * Sanity check
	 */
	if (WARN_ON(!q)			  ||
	    WARN_ON(!q->ops)		  ||
	    WARN_ON(!q->mem_ops)	  ||
	    WARN_ON(!q->type)		  ||
	    WARN_ON(!q->io_modes)	  ||
	    WARN_ON(!q->ops->queue_setup) ||
	    WARN_ON(!q->ops->buf_queue))
		return -EINVAL;

	if (WARN_ON(q->requires_requests && !q->supports_requests))
		return -EINVAL;

	INIT_LIST_HEAD(&q->queued_list);
	INIT_LIST_HEAD(&q->done_list);
	spin_lock_init(&q->done_lock);
	mutex_init(&q->mmap_lock);
	init_waitqueue_head(&q->done_wq);

	q->memory = VB2_MEMORY_UNKNOWN;

	if (q->buf_struct_size == 0)
		q->buf_struct_size = sizeof(struct vb2_buffer);

	if (q->bidirectional)
		q->dma_dir = DMA_BIDIRECTIONAL;
	else
		q->dma_dir = q->is_output ? DMA_TO_DEVICE : DMA_FROM_DEVICE;

	return 0;
}