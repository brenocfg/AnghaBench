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
struct vchiu_queue {int write; int read; int size; int /*<<< orphan*/  push; struct vchiq_header** storage; int /*<<< orphan*/  pop; int /*<<< orphan*/  initialized; } ;
struct vchiq_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  flush_signals (int /*<<< orphan*/ ) ; 
 scalar_t__ wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

void vchiu_queue_push(struct vchiu_queue *queue, struct vchiq_header *header)
{
	if (!queue->initialized)
		return;

	while (queue->write == queue->read + queue->size) {
		if (wait_for_completion_interruptible(&queue->pop))
			flush_signals(current);
	}

	queue->storage[queue->write & (queue->size - 1)] = header;
	queue->write++;

	complete(&queue->push);
}