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
struct resource_context {int dummy; } ;
struct pipe_ctx {struct pipe_ctx* bottom_pipe; } ;
struct dc_stream_state {int dummy; } ;

/* Variables and functions */
 struct pipe_ctx* resource_get_head_pipe_for_stream (struct resource_context*,struct dc_stream_state*) ; 

__attribute__((used)) static struct pipe_ctx *resource_get_tail_pipe_for_stream(
		struct resource_context *res_ctx,
		struct dc_stream_state *stream)
{
	struct pipe_ctx *head_pipe, *tail_pipe;
	head_pipe = resource_get_head_pipe_for_stream(res_ctx, stream);

	if (!head_pipe)
		return NULL;

	tail_pipe = head_pipe->bottom_pipe;

	while (tail_pipe) {
		head_pipe = tail_pipe;
		tail_pipe = tail_pipe->bottom_pipe;
	}

	return head_pipe;
}