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
struct xvip_pipeline {scalar_t__ use_count; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __xvip_pipeline_cleanup (struct xvip_pipeline*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xvip_pipeline_cleanup(struct xvip_pipeline *pipe)
{
	mutex_lock(&pipe->lock);

	/* If we're the last user clean up the pipeline. */
	if (--pipe->use_count == 0)
		__xvip_pipeline_cleanup(pipe);

	mutex_unlock(&pipe->lock);
}