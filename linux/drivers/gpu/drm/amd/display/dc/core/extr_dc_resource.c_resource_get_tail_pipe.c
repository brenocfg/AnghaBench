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

/* Variables and functions */

__attribute__((used)) static struct pipe_ctx *resource_get_tail_pipe(
		struct resource_context *res_ctx,
		struct pipe_ctx *head_pipe)
{
	struct pipe_ctx *tail_pipe;

	tail_pipe = head_pipe->bottom_pipe;

	while (tail_pipe) {
		head_pipe = tail_pipe;
		tail_pipe = tail_pipe->bottom_pipe;
	}

	return head_pipe;
}