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
struct pipe_ctx {int /*<<< orphan*/  stream; scalar_t__ top_pipe; } ;

/* Variables and functions */
 int MAX_PIPES ; 
 int /*<<< orphan*/  resource_are_streams_timing_synchronizable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool all_displays_in_sync(const struct pipe_ctx pipe[],
				 int pipe_count)
{
	const struct pipe_ctx *active_pipes[MAX_PIPES];
	int i, num_active_pipes = 0;

	for (i = 0; i < pipe_count; i++) {
		if (!pipe[i].stream || pipe[i].top_pipe)
			continue;

		active_pipes[num_active_pipes++] = &pipe[i];
	}

	if (!num_active_pipes)
		return false;

	for (i = 1; i < num_active_pipes; ++i) {
		if (!resource_are_streams_timing_synchronizable(
			    active_pipes[0]->stream, active_pipes[i]->stream)) {
			return false;
		}
	}

	return true;
}