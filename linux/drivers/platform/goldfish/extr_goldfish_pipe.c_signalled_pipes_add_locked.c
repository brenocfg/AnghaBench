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
typedef  size_t u32 ;
struct goldfish_pipe_dev {size_t pipes_capacity; struct goldfish_pipe* first_signalled_pipe; struct goldfish_pipe** pipes; } ;
struct goldfish_pipe {size_t signalled_flags; struct goldfish_pipe* prev_signalled; struct goldfish_pipe* next_signalled; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 

__attribute__((used)) static void signalled_pipes_add_locked(struct goldfish_pipe_dev *dev,
				       u32 id, u32 flags)
{
	struct goldfish_pipe *pipe;

	if (WARN_ON(id >= dev->pipes_capacity))
		return;

	pipe = dev->pipes[id];
	if (!pipe)
		return;
	pipe->signalled_flags |= flags;

	if (pipe->prev_signalled || pipe->next_signalled ||
		dev->first_signalled_pipe == pipe)
		return;	/* already in the list */
	pipe->next_signalled = dev->first_signalled_pipe;
	if (dev->first_signalled_pipe)
		dev->first_signalled_pipe->prev_signalled = pipe;
	dev->first_signalled_pipe = pipe;
}