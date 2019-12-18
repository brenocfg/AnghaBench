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
struct dc_state {int stream_count; TYPE_2__* stream_status; } ;
struct TYPE_4__ {int plane_count; TYPE_1__** plane_states; } ;
struct TYPE_3__ {scalar_t__ format; } ;

/* Variables and functions */
 scalar_t__ SURFACE_PIXEL_FORMAT_VIDEO_BEGIN ; 

__attribute__((used)) static bool dce80_validate_surface_sets(
		struct dc_state *context)
{
	int i;

	for (i = 0; i < context->stream_count; i++) {
		if (context->stream_status[i].plane_count == 0)
			continue;

		if (context->stream_status[i].plane_count > 1)
			return false;

		if (context->stream_status[i].plane_states[0]->format
				>= SURFACE_PIXEL_FORMAT_VIDEO_BEGIN)
			return false;
	}

	return true;
}