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
struct pipe_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dce110_disable_stream (struct pipe_ctx*) ; 

void dcn20_disable_stream(struct pipe_ctx *pipe_ctx)
{
	dce110_disable_stream(pipe_ctx);
}