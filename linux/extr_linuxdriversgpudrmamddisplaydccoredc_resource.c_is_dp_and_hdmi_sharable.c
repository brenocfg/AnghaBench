#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ c_depth; } ;
struct dc_stream_state {TYPE_4__ clamping; TYPE_3__* ctx; } ;
struct TYPE_7__ {TYPE_2__* dc; } ;
struct TYPE_5__ {scalar_t__ disable_dp_clk_share; } ;
struct TYPE_6__ {TYPE_1__ caps; } ;

/* Variables and functions */
 scalar_t__ COLOR_DEPTH_888 ; 

__attribute__((used)) static bool is_dp_and_hdmi_sharable(
		struct dc_stream_state *stream1,
		struct dc_stream_state *stream2)
{
	if (stream1->ctx->dc->caps.disable_dp_clk_share)
		return false;

	if (stream1->clamping.c_depth != COLOR_DEPTH_888 ||
	    stream2->clamping.c_depth != COLOR_DEPTH_888)
	return false;

	return true;

}