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
struct xvip_dma {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __xvip_pipeline_cleanup (struct xvip_pipeline*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int xvip_pipeline_validate (struct xvip_pipeline*,struct xvip_dma*) ; 

__attribute__((used)) static int xvip_pipeline_prepare(struct xvip_pipeline *pipe,
				 struct xvip_dma *dma)
{
	int ret;

	mutex_lock(&pipe->lock);

	/* If we're the first user validate and initialize the pipeline. */
	if (pipe->use_count == 0) {
		ret = xvip_pipeline_validate(pipe, dma);
		if (ret < 0) {
			__xvip_pipeline_cleanup(pipe);
			goto done;
		}
	}

	pipe->use_count++;
	ret = 0;

done:
	mutex_unlock(&pipe->lock);
	return ret;
}