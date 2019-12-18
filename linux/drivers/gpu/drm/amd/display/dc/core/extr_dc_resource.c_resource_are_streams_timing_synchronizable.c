#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ c_depth; } ;
struct TYPE_3__ {scalar_t__ h_total; scalar_t__ v_total; scalar_t__ h_addressable; scalar_t__ v_addressable; scalar_t__ pix_clk_100hz; } ;
struct dc_stream_state {scalar_t__ phy_pix_clk; scalar_t__ view_format; scalar_t__ ignore_msa_timing_param; int /*<<< orphan*/  signal; TYPE_2__ clamping; TYPE_1__ timing; } ;

/* Variables and functions */
 int /*<<< orphan*/  dc_is_dp_signal (int /*<<< orphan*/ ) ; 

bool resource_are_streams_timing_synchronizable(
	struct dc_stream_state *stream1,
	struct dc_stream_state *stream2)
{
	if (stream1->timing.h_total != stream2->timing.h_total)
		return false;

	if (stream1->timing.v_total != stream2->timing.v_total)
		return false;

	if (stream1->timing.h_addressable
				!= stream2->timing.h_addressable)
		return false;

	if (stream1->timing.v_addressable
				!= stream2->timing.v_addressable)
		return false;

	if (stream1->timing.pix_clk_100hz
				!= stream2->timing.pix_clk_100hz)
		return false;

	if (stream1->clamping.c_depth != stream2->clamping.c_depth)
		return false;

	if (stream1->phy_pix_clk != stream2->phy_pix_clk
			&& (!dc_is_dp_signal(stream1->signal)
			|| !dc_is_dp_signal(stream2->signal)))
		return false;

	if (stream1->view_format != stream2->view_format)
		return false;

	if (stream1->ignore_msa_timing_param || stream2->ignore_msa_timing_param)
		return false;

	return true;
}