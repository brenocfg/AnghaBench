#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct v4l2_ctrl {int id; int /*<<< orphan*/  val; } ;
struct cx2341x_handler {TYPE_6__* video_bitrate; TYPE_5__* video_bitrate_peak; TYPE_4__* video_bitrate_mode; TYPE_3__* video_encoding; TYPE_2__* stream_type; TYPE_1__* video_gop_size; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_12__ {int /*<<< orphan*/  val; } ;
struct TYPE_11__ {int /*<<< orphan*/  val; } ;
struct TYPE_10__ {int /*<<< orphan*/  val; } ;
struct TYPE_9__ {int /*<<< orphan*/  val; } ;
struct TYPE_8__ {int /*<<< orphan*/  val; } ;
struct TYPE_7__ {int val; } ;

/* Variables and functions */
#define  V4L2_CID_MPEG_STREAM_TYPE 129 
#define  V4L2_CID_MPEG_VIDEO_B_FRAMES 128 
 int /*<<< orphan*/  V4L2_MPEG_STREAM_TYPE_MPEG1_SS ; 
 int /*<<< orphan*/  V4L2_MPEG_STREAM_TYPE_MPEG1_VCD ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_BITRATE_MODE_CBR ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_BITRATE_MODE_VBR ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_ENCODING_MPEG_1 ; 
 int /*<<< orphan*/  V4L2_MPEG_VIDEO_ENCODING_MPEG_2 ; 
 struct cx2341x_handler* to_cxhdl (struct v4l2_ctrl*) ; 

__attribute__((used)) static int cx2341x_try_ctrl(struct v4l2_ctrl *ctrl)
{
	struct cx2341x_handler *hdl = to_cxhdl(ctrl);
	s32 val = ctrl->val;

	switch (ctrl->id) {
	case V4L2_CID_MPEG_VIDEO_B_FRAMES: {
		/* video gop cluster */
		int b = val + 1;
		int gop = hdl->video_gop_size->val;

		gop = b * ((gop + b - 1) / b);

		/* Max GOP size = 34 */
		while (gop > 34)
			gop -= b;
		hdl->video_gop_size->val = gop;
		break;
	}

	case V4L2_CID_MPEG_STREAM_TYPE:
		/* stream type cluster */
		hdl->video_encoding->val =
		    (hdl->stream_type->val == V4L2_MPEG_STREAM_TYPE_MPEG1_SS ||
		     hdl->stream_type->val == V4L2_MPEG_STREAM_TYPE_MPEG1_VCD) ?
			V4L2_MPEG_VIDEO_ENCODING_MPEG_1 :
			V4L2_MPEG_VIDEO_ENCODING_MPEG_2;
		if (hdl->video_encoding->val == V4L2_MPEG_VIDEO_ENCODING_MPEG_1)
			/* MPEG-1 implies CBR */
			hdl->video_bitrate_mode->val =
				V4L2_MPEG_VIDEO_BITRATE_MODE_CBR;
		/* peak bitrate shall be >= normal bitrate */
		if (hdl->video_bitrate_mode->val == V4L2_MPEG_VIDEO_BITRATE_MODE_VBR &&
		    hdl->video_bitrate_peak->val < hdl->video_bitrate->val)
			hdl->video_bitrate_peak->val = hdl->video_bitrate->val;
		break;
	}
	return 0;
}