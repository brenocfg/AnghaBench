#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pipe_ctx {TYPE_1__* stream; int /*<<< orphan*/ * clock_source; } ;
struct TYPE_5__ {scalar_t__ signal; } ;

/* Variables and functions */
 scalar_t__ SIGNAL_TYPE_VIRTUAL ; 
 scalar_t__ dc_is_dp_signal (scalar_t__) ; 
 scalar_t__ dc_is_dual_link_signal (scalar_t__) ; 
 scalar_t__ dc_is_hdmi_signal (scalar_t__) ; 
 int /*<<< orphan*/  is_dp_and_hdmi_sharable (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  resource_are_streams_timing_synchronizable (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static bool is_sharable_clk_src(
	const struct pipe_ctx *pipe_with_clk_src,
	const struct pipe_ctx *pipe)
{
	if (pipe_with_clk_src->clock_source == NULL)
		return false;

	if (pipe_with_clk_src->stream->signal == SIGNAL_TYPE_VIRTUAL)
		return false;

	if (dc_is_dp_signal(pipe_with_clk_src->stream->signal) ||
		(dc_is_dp_signal(pipe->stream->signal) &&
		!is_dp_and_hdmi_sharable(pipe_with_clk_src->stream,
				     pipe->stream)))
		return false;

	if (dc_is_hdmi_signal(pipe_with_clk_src->stream->signal)
			&& dc_is_dual_link_signal(pipe->stream->signal))
		return false;

	if (dc_is_hdmi_signal(pipe->stream->signal)
			&& dc_is_dual_link_signal(pipe_with_clk_src->stream->signal))
		return false;

	if (!resource_are_streams_timing_synchronizable(
			pipe_with_clk_src->stream, pipe->stream))
		return false;

	return true;
}