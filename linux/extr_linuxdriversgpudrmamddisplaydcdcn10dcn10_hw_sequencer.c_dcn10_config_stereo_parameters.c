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
struct TYPE_9__ {int /*<<< orphan*/  RIGHT_EYE_3D_POLARITY; } ;
struct TYPE_10__ {int timing_3d_format; TYPE_4__ flags; } ;
struct dc_stream_state {int view_format; TYPE_5__ timing; TYPE_3__* sink; } ;
struct crtc_stereo_flags {int PROGRAM_STEREO; int PROGRAM_POLARITY; int DISABLE_STEREO_DP_SYNC; int FRAME_PACKED; int /*<<< orphan*/  RIGHT_EYE_POLARITY; } ;
typedef  enum view_3d_format { ____Placeholder_view_3d_format } view_3d_format ;
typedef  enum display_dongle_type { ____Placeholder_display_dongle_type } display_dongle_type ;
typedef  enum dc_timing_3d_format { ____Placeholder_dc_timing_3d_format } dc_timing_3d_format ;
struct TYPE_8__ {TYPE_2__* link; } ;
struct TYPE_7__ {TYPE_1__* ddc; } ;
struct TYPE_6__ {int dongle_type; } ;

/* Variables and functions */
 int DISPLAY_DONGLE_DP_DVI_CONVERTER ; 
 int DISPLAY_DONGLE_DP_HDMI_CONVERTER ; 
 int DISPLAY_DONGLE_DP_VGA_CONVERTER ; 
 int TIMING_3D_FORMAT_DP_HDMI_INBAND_FA ; 
 int TIMING_3D_FORMAT_HW_FRAME_PACKING ; 
 int TIMING_3D_FORMAT_INBAND_FA ; 
 int TIMING_3D_FORMAT_NONE ; 
 int TIMING_3D_FORMAT_SIDEBAND_FA ; 
 int TIMING_3D_FORMAT_SIDE_BY_SIDE ; 
 int TIMING_3D_FORMAT_TOP_AND_BOTTOM ; 
 int VIEW_3D_FORMAT_FRAME_SEQUENTIAL ; 

__attribute__((used)) static void dcn10_config_stereo_parameters(
		struct dc_stream_state *stream, struct crtc_stereo_flags *flags)
{
	enum view_3d_format view_format = stream->view_format;
	enum dc_timing_3d_format timing_3d_format =\
			stream->timing.timing_3d_format;
	bool non_stereo_timing = false;

	if (timing_3d_format == TIMING_3D_FORMAT_NONE ||
		timing_3d_format == TIMING_3D_FORMAT_SIDE_BY_SIDE ||
		timing_3d_format == TIMING_3D_FORMAT_TOP_AND_BOTTOM)
		non_stereo_timing = true;

	if (non_stereo_timing == false &&
		view_format == VIEW_3D_FORMAT_FRAME_SEQUENTIAL) {

		flags->PROGRAM_STEREO         = 1;
		flags->PROGRAM_POLARITY       = 1;
		if (timing_3d_format == TIMING_3D_FORMAT_INBAND_FA ||
			timing_3d_format == TIMING_3D_FORMAT_DP_HDMI_INBAND_FA ||
			timing_3d_format == TIMING_3D_FORMAT_SIDEBAND_FA) {
			enum display_dongle_type dongle = \
					stream->sink->link->ddc->dongle_type;
			if (dongle == DISPLAY_DONGLE_DP_VGA_CONVERTER ||
				dongle == DISPLAY_DONGLE_DP_DVI_CONVERTER ||
				dongle == DISPLAY_DONGLE_DP_HDMI_CONVERTER)
				flags->DISABLE_STEREO_DP_SYNC = 1;
		}
		flags->RIGHT_EYE_POLARITY =\
				stream->timing.flags.RIGHT_EYE_3D_POLARITY;
		if (timing_3d_format == TIMING_3D_FORMAT_HW_FRAME_PACKING)
			flags->FRAME_PACKED = 1;
	}

	return;
}