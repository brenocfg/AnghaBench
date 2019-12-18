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
struct dc_state {int stream_count; TYPE_4__** streams; TYPE_1__* stream_status; } ;
struct TYPE_6__ {int width; int height; } ;
struct dc_plane_state {scalar_t__ format; TYPE_2__ src_rect; } ;
struct TYPE_7__ {scalar_t__ pixel_encoding; } ;
struct TYPE_8__ {TYPE_3__ timing; } ;
struct TYPE_5__ {int plane_count; struct dc_plane_state** plane_states; } ;

/* Variables and functions */
 scalar_t__ PIXEL_ENCODING_RGB ; 
 scalar_t__ SURFACE_PIXEL_FORMAT_VIDEO_BEGIN ; 

__attribute__((used)) static bool dce110_validate_surface_sets(
		struct dc_state *context)
{
	int i, j;

	for (i = 0; i < context->stream_count; i++) {
		if (context->stream_status[i].plane_count == 0)
			continue;

		if (context->stream_status[i].plane_count > 2)
			return false;

		for (j = 0; j < context->stream_status[i].plane_count; j++) {
			struct dc_plane_state *plane =
				context->stream_status[i].plane_states[j];

			/* underlay validation */
			if (plane->format >= SURFACE_PIXEL_FORMAT_VIDEO_BEGIN) {

				if ((plane->src_rect.width > 1920 ||
					plane->src_rect.height > 1080))
					return false;

				/* we don't have the logic to support underlay
				 * only yet so block the use case where we get
				 * NV12 plane as top layer
				 */
				if (j == 0)
					return false;

				/* irrespective of plane format,
				 * stream should be RGB encoded
				 */
				if (context->streams[i]->timing.pixel_encoding
						!= PIXEL_ENCODING_RGB)
					return false;

			}

		}
	}

	return true;
}