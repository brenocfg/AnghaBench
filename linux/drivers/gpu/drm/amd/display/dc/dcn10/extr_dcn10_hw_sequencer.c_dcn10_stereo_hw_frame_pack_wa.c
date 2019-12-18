#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct dc_state {size_t stream_count; TYPE_2__** streams; } ;
struct dc {TYPE_3__* res_pool; } ;
struct TYPE_6__ {int /*<<< orphan*/  hubbub; } ;
struct TYPE_4__ {scalar_t__ timing_3d_format; } ;
struct TYPE_5__ {TYPE_1__ timing; } ;

/* Variables and functions */
 scalar_t__ TIMING_3D_FORMAT_HW_FRAME_PACKING ; 
 int /*<<< orphan*/  hubbub1_allow_self_refresh_control (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dcn10_stereo_hw_frame_pack_wa(struct dc *dc, struct dc_state *context)
{
	uint8_t i;

	for (i = 0; i < context->stream_count; i++) {
		if (context->streams[i]->timing.timing_3d_format
				== TIMING_3D_FORMAT_HW_FRAME_PACKING) {
			/*
			 * Disable stutter
			 */
			hubbub1_allow_self_refresh_control(dc->res_pool->hubbub, false);
			break;
		}
	}
}