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
struct goldfish_pipe_dev {int /*<<< orphan*/  lock; struct goldfish_pipe* first_signalled_pipe; } ;
struct goldfish_pipe {int signalled_flags; struct goldfish_pipe* next_signalled; int /*<<< orphan*/ * prev_signalled; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct goldfish_pipe *signalled_pipes_pop_front(
		struct goldfish_pipe_dev *dev, int *wakes)
{
	struct goldfish_pipe *pipe;
	unsigned long flags;

	spin_lock_irqsave(&dev->lock, flags);

	pipe = dev->first_signalled_pipe;
	if (pipe) {
		*wakes = pipe->signalled_flags;
		pipe->signalled_flags = 0;
		/*
		 * This is an optimized version of
		 * signalled_pipes_remove_locked()
		 * - We want to make it as fast as possible to
		 * wake the sleeping pipe operations faster.
		 */
		dev->first_signalled_pipe = pipe->next_signalled;
		if (dev->first_signalled_pipe)
			dev->first_signalled_pipe->prev_signalled = NULL;
		pipe->next_signalled = NULL;
	}

	spin_unlock_irqrestore(&dev->lock, flags);
	return pipe;
}