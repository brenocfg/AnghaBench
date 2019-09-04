#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct resource_context {TYPE_1__* pipe_ctx; } ;
struct pipe_ctx {int dummy; } ;
struct clock_source {int dummy; } ;
struct TYPE_2__ {struct clock_source* clock_source; } ;

/* Variables and functions */
 int MAX_PIPES ; 
 scalar_t__ is_sharable_clk_src (TYPE_1__*,struct pipe_ctx*) ; 

struct clock_source *resource_find_used_clk_src_for_sharing(
					struct resource_context *res_ctx,
					struct pipe_ctx *pipe_ctx)
{
	int i;

	for (i = 0; i < MAX_PIPES; i++) {
		if (is_sharable_clk_src(&res_ctx->pipe_ctx[i], pipe_ctx))
			return res_ctx->pipe_ctx[i].clock_source;
	}

	return NULL;
}