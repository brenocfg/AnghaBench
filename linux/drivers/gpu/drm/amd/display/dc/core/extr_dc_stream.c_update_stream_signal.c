#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int pix_clk_100hz; } ;
struct dc_stream_state {scalar_t__ signal; TYPE_4__ timing; TYPE_3__* ctx; TYPE_5__* link; } ;
struct dc_sink {scalar_t__ sink_signal; } ;
struct TYPE_10__ {scalar_t__ connector_signal; } ;
struct TYPE_8__ {TYPE_2__* dc; } ;
struct TYPE_6__ {scalar_t__ dual_link_dvi; } ;
struct TYPE_7__ {TYPE_1__ caps; } ;

/* Variables and functions */
 scalar_t__ SIGNAL_TYPE_DVI_DUAL_LINK ; 
 scalar_t__ SIGNAL_TYPE_DVI_SINGLE_LINK ; 
 scalar_t__ SIGNAL_TYPE_NONE ; 
 int TMDS_MAX_PIXEL_CLOCK ; 
 scalar_t__ dc_is_dvi_signal (scalar_t__) ; 

void update_stream_signal(struct dc_stream_state *stream, struct dc_sink *sink)
{
	if (sink->sink_signal == SIGNAL_TYPE_NONE)
		stream->signal = stream->link->connector_signal;
	else
		stream->signal = sink->sink_signal;

	if (dc_is_dvi_signal(stream->signal)) {
		if (stream->ctx->dc->caps.dual_link_dvi &&
			(stream->timing.pix_clk_100hz / 10) > TMDS_MAX_PIXEL_CLOCK &&
			sink->sink_signal != SIGNAL_TYPE_DVI_SINGLE_LINK)
			stream->signal = SIGNAL_TYPE_DVI_DUAL_LINK;
		else
			stream->signal = SIGNAL_TYPE_DVI_SINGLE_LINK;
	}
}