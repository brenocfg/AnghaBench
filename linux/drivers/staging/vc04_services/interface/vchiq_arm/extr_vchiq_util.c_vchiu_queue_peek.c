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
struct vchiu_queue {int write; int read; int size; struct vchiq_header** storage; int /*<<< orphan*/  push; } ;
struct vchiq_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  flush_signals (int /*<<< orphan*/ ) ; 
 scalar_t__ wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

struct vchiq_header *vchiu_queue_peek(struct vchiu_queue *queue)
{
	while (queue->write == queue->read) {
		if (wait_for_completion_interruptible(&queue->push))
			flush_signals(current);
	}

	complete(&queue->push); // We haven't removed anything from the queue.

	return queue->storage[queue->read & (queue->size - 1)];
}