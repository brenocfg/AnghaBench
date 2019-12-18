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
struct lima_sched_pipe {int /*<<< orphan*/  base; int /*<<< orphan*/  error_work; int /*<<< orphan*/  fence_lock; int /*<<< orphan*/  fence_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_context_alloc (int) ; 
 int drm_sched_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  lima_sched_error_work ; 
 int /*<<< orphan*/  lima_sched_ops ; 
 int lima_sched_timeout_ms ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int lima_sched_pipe_init(struct lima_sched_pipe *pipe, const char *name)
{
	unsigned int timeout = lima_sched_timeout_ms > 0 ?
			       lima_sched_timeout_ms : 500;

	pipe->fence_context = dma_fence_context_alloc(1);
	spin_lock_init(&pipe->fence_lock);

	INIT_WORK(&pipe->error_work, lima_sched_error_work);

	return drm_sched_init(&pipe->base, &lima_sched_ops, 1, 0,
			      msecs_to_jiffies(timeout), name);
}