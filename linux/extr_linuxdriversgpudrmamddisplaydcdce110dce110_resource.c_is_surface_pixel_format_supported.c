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
struct pipe_ctx {unsigned int pipe_idx; TYPE_1__* plane_state; } ;
struct TYPE_2__ {scalar_t__ format; } ;

/* Variables and functions */
 scalar_t__ SURFACE_PIXEL_FORMAT_VIDEO_BEGIN ; 

__attribute__((used)) static bool is_surface_pixel_format_supported(struct pipe_ctx *pipe_ctx, unsigned int underlay_idx)
{
	if (pipe_ctx->pipe_idx != underlay_idx)
		return true;
	if (!pipe_ctx->plane_state)
		return false;
	if (pipe_ctx->plane_state->format < SURFACE_PIXEL_FORMAT_VIDEO_BEGIN)
		return false;
	return true;
}