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
struct xvip_pipeline {int stream_count; int num_dmas; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int xvip_pipeline_start_stop (struct xvip_pipeline*,int) ; 

__attribute__((used)) static int xvip_pipeline_set_stream(struct xvip_pipeline *pipe, bool on)
{
	int ret = 0;

	mutex_lock(&pipe->lock);

	if (on) {
		if (pipe->stream_count == pipe->num_dmas - 1) {
			ret = xvip_pipeline_start_stop(pipe, true);
			if (ret < 0)
				goto done;
		}
		pipe->stream_count++;
	} else {
		if (--pipe->stream_count == 0)
			xvip_pipeline_start_stop(pipe, false);
	}

done:
	mutex_unlock(&pipe->lock);
	return ret;
}