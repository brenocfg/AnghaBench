#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  int u32 ;
struct v4l2_ctrl {size_t val; int id; } ;
struct cx2341x_handler {int audio_properties; TYPE_13__* video_chroma_median_filter_top; TYPE_13__* video_chroma_median_filter_bottom; TYPE_13__* video_luma_median_filter_top; TYPE_13__* video_luma_median_filter_bottom; TYPE_13__* video_temporal_filter; TYPE_13__* video_spatial_filter; TYPE_13__* video_chroma_spatial_filter_type; TYPE_13__* video_luma_spatial_filter_type; TYPE_5__* video_median_filter_type; TYPE_4__* video_temporal_filter_mode; TYPE_3__* video_spatial_filter_mode; TYPE_2__* video_mute_yuv; TYPE_1__* video_mute; TYPE_14__* video_encoding; TYPE_9__* ops; TYPE_13__* video_bitrate_mode; TYPE_13__* video_bitrate_peak; TYPE_12__* video_bitrate; TYPE_11__* video_b_frames; TYPE_10__* video_gop_size; TYPE_14__* audio_mode; TYPE_14__* audio_sampling_freq; TYPE_13__* audio_mode_extension; TYPE_13__* audio_l2_bitrate; TYPE_13__* audio_ac3_bitrate; TYPE_8__* audio_encoding; TYPE_7__* audio_emphasis; TYPE_6__* audio_crc; } ;
typedef  size_t s32 ;
struct TYPE_28__ {int (* s_stream_vbi_fmt ) (struct cx2341x_handler*,size_t) ;int (* s_audio_sampling_freq ) (struct cx2341x_handler*,int) ;int (* s_audio_mode ) (struct cx2341x_handler*,int) ;int (* s_video_encoding ) (struct cx2341x_handler*,int) ;} ;
struct TYPE_27__ {int /*<<< orphan*/  val; } ;
struct TYPE_26__ {int val; } ;
struct TYPE_25__ {int val; } ;
struct TYPE_24__ {int /*<<< orphan*/  val; } ;
struct TYPE_23__ {int val; } ;
struct TYPE_22__ {int val; } ;
struct TYPE_21__ {int val; } ;
struct TYPE_20__ {int val; } ;
struct TYPE_19__ {int val; } ;
struct TYPE_18__ {int val; } ;
struct TYPE_17__ {int /*<<< orphan*/  val; } ;
struct TYPE_16__ {int /*<<< orphan*/  val; } ;
struct TYPE_15__ {int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int CX2341X_AUDIO_ENCODING_METHOD_AC3 ; 
 int /*<<< orphan*/  CX2341X_ENC_MISC ; 
 int /*<<< orphan*/  CX2341X_ENC_MUTE_AUDIO ; 
 int /*<<< orphan*/  CX2341X_ENC_MUTE_VIDEO ; 
 int /*<<< orphan*/  CX2341X_ENC_SET_ASPECT_RATIO ; 
 int /*<<< orphan*/  CX2341X_ENC_SET_AUDIO_PROPERTIES ; 
 int /*<<< orphan*/  CX2341X_ENC_SET_BIT_RATE ; 
 int /*<<< orphan*/  CX2341X_ENC_SET_CORING_LEVELS ; 
 int /*<<< orphan*/  CX2341X_ENC_SET_DNR_FILTER_MODE ; 
 int /*<<< orphan*/  CX2341X_ENC_SET_DNR_FILTER_PROPS ; 
 int /*<<< orphan*/  CX2341X_ENC_SET_FRAME_DROP_RATE ; 
 int /*<<< orphan*/  CX2341X_ENC_SET_GOP_CLOSURE ; 
 int /*<<< orphan*/  CX2341X_ENC_SET_GOP_PROPERTIES ; 
 int /*<<< orphan*/  CX2341X_ENC_SET_SPATIAL_FILTER_TYPE ; 
 int /*<<< orphan*/  CX2341X_ENC_SET_STREAM_TYPE ; 
 int EINVAL ; 
#define  V4L2_CID_MPEG_AUDIO_MUTE 141 
#define  V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ 140 
#define  V4L2_CID_MPEG_CX2341X_STREAM_INSERT_NAV_PACKETS 139 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_TOP 138 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE 137 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER 136 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE 135 
#define  V4L2_CID_MPEG_STREAM_TYPE 134 
#define  V4L2_CID_MPEG_STREAM_VBI_FMT 133 
#define  V4L2_CID_MPEG_VIDEO_ASPECT 132 
#define  V4L2_CID_MPEG_VIDEO_B_FRAMES 131 
#define  V4L2_CID_MPEG_VIDEO_GOP_CLOSURE 130 
#define  V4L2_CID_MPEG_VIDEO_MUTE 129 
#define  V4L2_CID_MPEG_VIDEO_TEMPORAL_DECIMATION 128 
 int V4L2_MPEG_AUDIO_EMPHASIS_CCITT_J17 ; 
 int /*<<< orphan*/  V4L2_MPEG_AUDIO_ENCODING_AC3 ; 
 int /*<<< orphan*/  V4L2_MPEG_AUDIO_ENCODING_LAYER_2 ; 
 int V4L2_MPEG_AUDIO_MODE_JOINT_STEREO ; 
 int /*<<< orphan*/  V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_OFF ; 
 int V4L2_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE_AUTO ; 
 int V4L2_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE_AUTO ; 
 int V4L2_MPEG_VIDEO_BITRATE_MODE_CBR ; 
 int V4L2_MPEG_VIDEO_ENCODING_MPEG_1 ; 
 int cx2341x_hdl_api (struct cx2341x_handler*,int /*<<< orphan*/ ,int,int const,...) ; 
 int /*<<< orphan*/  cx2341x_neq (TYPE_14__*) ; 
 int stub1 (struct cx2341x_handler*,size_t) ; 
 int stub2 (struct cx2341x_handler*,int) ; 
 int stub3 (struct cx2341x_handler*,int) ; 
 int stub4 (struct cx2341x_handler*,int) ; 
 struct cx2341x_handler* to_cxhdl (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  v4l2_ctrl_activate (TYPE_13__*,int) ; 

__attribute__((used)) static int cx2341x_s_ctrl(struct v4l2_ctrl *ctrl)
{
	static const int mpeg_stream_type[] = {
		0,	/* MPEG-2 PS */
		1,	/* MPEG-2 TS */
		2,	/* MPEG-1 SS */
		14,	/* DVD */
		11,	/* VCD */
		12,	/* SVCD */
	};
	struct cx2341x_handler *hdl = to_cxhdl(ctrl);
	s32 val = ctrl->val;
	u32 props;
	int err;

	switch (ctrl->id) {
	case V4L2_CID_MPEG_STREAM_VBI_FMT:
		if (hdl->ops && hdl->ops->s_stream_vbi_fmt)
			return hdl->ops->s_stream_vbi_fmt(hdl, val);
		return 0;

	case V4L2_CID_MPEG_VIDEO_ASPECT:
		return cx2341x_hdl_api(hdl,
			CX2341X_ENC_SET_ASPECT_RATIO, 1, val + 1);

	case V4L2_CID_MPEG_VIDEO_GOP_CLOSURE:
		return cx2341x_hdl_api(hdl, CX2341X_ENC_SET_GOP_CLOSURE, 1, val);

	case V4L2_CID_MPEG_AUDIO_MUTE:
		return cx2341x_hdl_api(hdl, CX2341X_ENC_MUTE_AUDIO, 1, val);

	case V4L2_CID_MPEG_VIDEO_TEMPORAL_DECIMATION:
		return cx2341x_hdl_api(hdl,
			CX2341X_ENC_SET_FRAME_DROP_RATE, 1, val);

	case V4L2_CID_MPEG_CX2341X_STREAM_INSERT_NAV_PACKETS:
		return cx2341x_hdl_api(hdl, CX2341X_ENC_MISC, 2, 7, val);

	case V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ:
		/* audio properties cluster */
		props = (hdl->audio_sampling_freq->val << 0) |
			(hdl->audio_mode->val << 8) |
			(hdl->audio_mode_extension->val << 10) |
			(hdl->audio_crc->val << 14);
		if (hdl->audio_emphasis->val == V4L2_MPEG_AUDIO_EMPHASIS_CCITT_J17)
			props |= 3 << 12;
		else
			props |= hdl->audio_emphasis->val << 12;

		if (hdl->audio_encoding->val == V4L2_MPEG_AUDIO_ENCODING_AC3) {
			props |=
#if 1
				/* Not sure if this MPEG Layer II setting is required */
				((3 - V4L2_MPEG_AUDIO_ENCODING_LAYER_2) << 2) |
#endif
				(hdl->audio_ac3_bitrate->val << 4) |
				(CX2341X_AUDIO_ENCODING_METHOD_AC3 << 28);
		} else {
			/* Assuming MPEG Layer II */
			props |=
				((3 - hdl->audio_encoding->val) << 2) |
				((1 + hdl->audio_l2_bitrate->val) << 4);
		}
		err = cx2341x_hdl_api(hdl,
				CX2341X_ENC_SET_AUDIO_PROPERTIES, 1, props);
		if (err)
			return err;

		hdl->audio_properties = props;
		if (hdl->audio_ac3_bitrate) {
			int is_ac3 = hdl->audio_encoding->val ==
						V4L2_MPEG_AUDIO_ENCODING_AC3;

			v4l2_ctrl_activate(hdl->audio_ac3_bitrate, is_ac3);
			v4l2_ctrl_activate(hdl->audio_l2_bitrate, !is_ac3);
		}
		v4l2_ctrl_activate(hdl->audio_mode_extension,
			hdl->audio_mode->val == V4L2_MPEG_AUDIO_MODE_JOINT_STEREO);
		if (cx2341x_neq(hdl->audio_sampling_freq) &&
		    hdl->ops && hdl->ops->s_audio_sampling_freq)
			return hdl->ops->s_audio_sampling_freq(hdl, hdl->audio_sampling_freq->val);
		if (cx2341x_neq(hdl->audio_mode) &&
		    hdl->ops && hdl->ops->s_audio_mode)
			return hdl->ops->s_audio_mode(hdl, hdl->audio_mode->val);
		return 0;

	case V4L2_CID_MPEG_VIDEO_B_FRAMES:
		/* video gop cluster */
		return cx2341x_hdl_api(hdl, CX2341X_ENC_SET_GOP_PROPERTIES, 2,
				hdl->video_gop_size->val,
				hdl->video_b_frames->val + 1);

	case V4L2_CID_MPEG_STREAM_TYPE:
		/* stream type cluster */
		err = cx2341x_hdl_api(hdl,
			CX2341X_ENC_SET_STREAM_TYPE, 1, mpeg_stream_type[val]);
		if (err)
			return err;

		err = cx2341x_hdl_api(hdl, CX2341X_ENC_SET_BIT_RATE, 5,
				hdl->video_bitrate_mode->val,
				hdl->video_bitrate->val,
				hdl->video_bitrate_peak->val / 400, 0, 0);
		if (err)
			return err;

		v4l2_ctrl_activate(hdl->video_bitrate_mode,
			hdl->video_encoding->val != V4L2_MPEG_VIDEO_ENCODING_MPEG_1);
		v4l2_ctrl_activate(hdl->video_bitrate_peak,
			hdl->video_bitrate_mode->val != V4L2_MPEG_VIDEO_BITRATE_MODE_CBR);
		if (cx2341x_neq(hdl->video_encoding) &&
		    hdl->ops && hdl->ops->s_video_encoding)
			return hdl->ops->s_video_encoding(hdl, hdl->video_encoding->val);
		return 0;

	case V4L2_CID_MPEG_VIDEO_MUTE:
		/* video mute cluster */
		return cx2341x_hdl_api(hdl, CX2341X_ENC_MUTE_VIDEO, 1,
				hdl->video_mute->val |
					(hdl->video_mute_yuv->val << 8));

	case V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE: {
		int active_filter;

		/* video filter mode */
		err = cx2341x_hdl_api(hdl, CX2341X_ENC_SET_DNR_FILTER_MODE, 2,
				hdl->video_spatial_filter_mode->val |
					(hdl->video_temporal_filter_mode->val << 1),
				hdl->video_median_filter_type->val);
		if (err)
			return err;

		active_filter = hdl->video_spatial_filter_mode->val !=
				V4L2_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE_AUTO;
		v4l2_ctrl_activate(hdl->video_spatial_filter, active_filter);
		v4l2_ctrl_activate(hdl->video_luma_spatial_filter_type, active_filter);
		v4l2_ctrl_activate(hdl->video_chroma_spatial_filter_type, active_filter);
		active_filter = hdl->video_temporal_filter_mode->val !=
				V4L2_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE_AUTO;
		v4l2_ctrl_activate(hdl->video_temporal_filter, active_filter);
		active_filter = hdl->video_median_filter_type->val !=
				V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_OFF;
		v4l2_ctrl_activate(hdl->video_luma_median_filter_bottom, active_filter);
		v4l2_ctrl_activate(hdl->video_luma_median_filter_top, active_filter);
		v4l2_ctrl_activate(hdl->video_chroma_median_filter_bottom, active_filter);
		v4l2_ctrl_activate(hdl->video_chroma_median_filter_top, active_filter);
		return 0;
	}

	case V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE:
		/* video filter type cluster */
		return cx2341x_hdl_api(hdl,
				CX2341X_ENC_SET_SPATIAL_FILTER_TYPE, 2,
				hdl->video_luma_spatial_filter_type->val,
				hdl->video_chroma_spatial_filter_type->val);

	case V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER:
		/* video filter cluster */
		return cx2341x_hdl_api(hdl, CX2341X_ENC_SET_DNR_FILTER_PROPS, 2,
				hdl->video_spatial_filter->val,
				hdl->video_temporal_filter->val);

	case V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_TOP:
		/* video median cluster */
		return cx2341x_hdl_api(hdl, CX2341X_ENC_SET_CORING_LEVELS, 4,
				hdl->video_luma_median_filter_bottom->val,
				hdl->video_luma_median_filter_top->val,
				hdl->video_chroma_median_filter_bottom->val,
				hdl->video_chroma_median_filter_top->val);
	}
	return -EINVAL;
}