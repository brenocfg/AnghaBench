#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_queryctrl {int id; int /*<<< orphan*/  flags; } ;
struct cx2341x_mpeg_params {int capabilities; int audio_encoding; int video_encoding; int video_bitrate_mode; int video_spatial_filter_mode; int video_temporal_filter_mode; int video_median_filter_type; int /*<<< orphan*/  is_50hz; int /*<<< orphan*/  audio_mode; } ;
struct TYPE_2__ {int audio_encoding; int audio_l2_bitrate; int audio_ac3_bitrate; int /*<<< orphan*/  stream_insert_nav_packets; int /*<<< orphan*/  video_chroma_median_filter_bottom; int /*<<< orphan*/  video_chroma_median_filter_top; int /*<<< orphan*/  video_luma_median_filter_bottom; int /*<<< orphan*/  video_luma_median_filter_top; int /*<<< orphan*/  video_median_filter_type; int /*<<< orphan*/  video_temporal_filter; int /*<<< orphan*/  video_temporal_filter_mode; int /*<<< orphan*/  video_chroma_spatial_filter_type; int /*<<< orphan*/  video_luma_spatial_filter_type; int /*<<< orphan*/  video_spatial_filter; int /*<<< orphan*/  video_spatial_filter_mode; int /*<<< orphan*/  stream_vbi_fmt; } ;

/* Variables and functions */
 int CX2341X_CAP_HAS_AC3 ; 
 int CX2341X_CAP_HAS_SLICED_VBI ; 
 int EINVAL ; 
#define  V4L2_CID_MPEG_AUDIO_AC3_BITRATE 162 
#define  V4L2_CID_MPEG_AUDIO_CRC 161 
#define  V4L2_CID_MPEG_AUDIO_EMPHASIS 160 
#define  V4L2_CID_MPEG_AUDIO_ENCODING 159 
#define  V4L2_CID_MPEG_AUDIO_L2_BITRATE 158 
#define  V4L2_CID_MPEG_AUDIO_MODE 157 
#define  V4L2_CID_MPEG_AUDIO_MODE_EXTENSION 156 
#define  V4L2_CID_MPEG_AUDIO_MUTE 155 
#define  V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ 154 
#define  V4L2_CID_MPEG_CLASS 153 
#define  V4L2_CID_MPEG_CX2341X_STREAM_INSERT_NAV_PACKETS 152 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_BOTTOM 151 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_TOP 150 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE 149 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_BOTTOM 148 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_TOP 147 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE 146 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE 145 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER 144 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE 143 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER 142 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE 141 
#define  V4L2_CID_MPEG_STREAM_TYPE 140 
#define  V4L2_CID_MPEG_STREAM_VBI_FMT 139 
#define  V4L2_CID_MPEG_VIDEO_ASPECT 138 
#define  V4L2_CID_MPEG_VIDEO_BITRATE 137 
#define  V4L2_CID_MPEG_VIDEO_BITRATE_MODE 136 
#define  V4L2_CID_MPEG_VIDEO_BITRATE_PEAK 135 
#define  V4L2_CID_MPEG_VIDEO_B_FRAMES 134 
#define  V4L2_CID_MPEG_VIDEO_ENCODING 133 
#define  V4L2_CID_MPEG_VIDEO_GOP_CLOSURE 132 
#define  V4L2_CID_MPEG_VIDEO_GOP_SIZE 131 
#define  V4L2_CID_MPEG_VIDEO_MUTE 130 
#define  V4L2_CID_MPEG_VIDEO_MUTE_YUV 129 
#define  V4L2_CID_MPEG_VIDEO_TEMPORAL_DECIMATION 128 
 int /*<<< orphan*/  V4L2_CTRL_FLAG_DISABLED ; 
 int /*<<< orphan*/  V4L2_CTRL_FLAG_INACTIVE ; 
 int /*<<< orphan*/  V4L2_CTRL_FLAG_READ_ONLY ; 
 int /*<<< orphan*/  V4L2_CTRL_FLAG_SLIDER ; 
 int V4L2_MPEG_AUDIO_AC3_BITRATE_448K ; 
 int V4L2_MPEG_AUDIO_AC3_BITRATE_48K ; 
 int V4L2_MPEG_AUDIO_CRC_CRC16 ; 
 int V4L2_MPEG_AUDIO_CRC_NONE ; 
 int V4L2_MPEG_AUDIO_EMPHASIS_CCITT_J17 ; 
 int V4L2_MPEG_AUDIO_EMPHASIS_NONE ; 
 int V4L2_MPEG_AUDIO_ENCODING_AC3 ; 
 int V4L2_MPEG_AUDIO_ENCODING_LAYER_2 ; 
 int V4L2_MPEG_AUDIO_L2_BITRATE_192K ; 
 int V4L2_MPEG_AUDIO_L2_BITRATE_384K ; 
 int V4L2_MPEG_AUDIO_MODE_EXTENSION_BOUND_16 ; 
 int V4L2_MPEG_AUDIO_MODE_EXTENSION_BOUND_4 ; 
 int /*<<< orphan*/  V4L2_MPEG_AUDIO_MODE_JOINT_STEREO ; 
 int V4L2_MPEG_AUDIO_MODE_MONO ; 
 int V4L2_MPEG_AUDIO_MODE_STEREO ; 
 int V4L2_MPEG_AUDIO_SAMPLING_FREQ_32000 ; 
 int V4L2_MPEG_AUDIO_SAMPLING_FREQ_44100 ; 
 int V4L2_MPEG_AUDIO_SAMPLING_FREQ_48000 ; 
 int V4L2_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE_1D_HOR ; 
 int V4L2_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE_OFF ; 
 int V4L2_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE_2D_SYM_NON_SEPARABLE ; 
 int V4L2_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE_OFF ; 
 int V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_DIAG ; 
 int V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_OFF ; 
 int V4L2_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE_AUTO ; 
 int V4L2_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE_MANUAL ; 
 int V4L2_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE_AUTO ; 
 int V4L2_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE_MANUAL ; 
 int V4L2_MPEG_STREAM_TYPE_MPEG2_PS ; 
 int V4L2_MPEG_STREAM_TYPE_MPEG2_SVCD ; 
 int V4L2_MPEG_STREAM_VBI_FMT_IVTV ; 
 int V4L2_MPEG_STREAM_VBI_FMT_NONE ; 
 int V4L2_MPEG_VIDEO_ASPECT_1x1 ; 
 int V4L2_MPEG_VIDEO_ASPECT_221x100 ; 
 int V4L2_MPEG_VIDEO_ASPECT_4x3 ; 
 int V4L2_MPEG_VIDEO_BITRATE_MODE_CBR ; 
 int V4L2_MPEG_VIDEO_BITRATE_MODE_VBR ; 
 int V4L2_MPEG_VIDEO_ENCODING_MPEG_1 ; 
 int V4L2_MPEG_VIDEO_ENCODING_MPEG_2 ; 
 int cx2341x_ctrl_query_fill (struct v4l2_queryctrl*,int,int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ default_params ; 
 int v4l2_ctrl_query_fill (struct v4l2_queryctrl*,int,int,int,int) ; 

int cx2341x_ctrl_query(const struct cx2341x_mpeg_params *params,
		       struct v4l2_queryctrl *qctrl)
{
	int err;

	switch (qctrl->id) {
	case V4L2_CID_MPEG_CLASS:
		return v4l2_ctrl_query_fill(qctrl, 0, 0, 0, 0);
	case V4L2_CID_MPEG_STREAM_TYPE:
		return v4l2_ctrl_query_fill(qctrl,
				V4L2_MPEG_STREAM_TYPE_MPEG2_PS,
				V4L2_MPEG_STREAM_TYPE_MPEG2_SVCD, 1,
				V4L2_MPEG_STREAM_TYPE_MPEG2_PS);

	case V4L2_CID_MPEG_STREAM_VBI_FMT:
		if (params->capabilities & CX2341X_CAP_HAS_SLICED_VBI)
			return v4l2_ctrl_query_fill(qctrl,
					V4L2_MPEG_STREAM_VBI_FMT_NONE,
					V4L2_MPEG_STREAM_VBI_FMT_IVTV, 1,
					V4L2_MPEG_STREAM_VBI_FMT_NONE);
		return cx2341x_ctrl_query_fill(qctrl,
				V4L2_MPEG_STREAM_VBI_FMT_NONE,
				V4L2_MPEG_STREAM_VBI_FMT_NONE, 1,
				default_params.stream_vbi_fmt);

	case V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ:
		return v4l2_ctrl_query_fill(qctrl,
				V4L2_MPEG_AUDIO_SAMPLING_FREQ_44100,
				V4L2_MPEG_AUDIO_SAMPLING_FREQ_32000, 1,
				V4L2_MPEG_AUDIO_SAMPLING_FREQ_48000);

	case V4L2_CID_MPEG_AUDIO_ENCODING:
		if (params->capabilities & CX2341X_CAP_HAS_AC3) {
			/*
			 * The state of L2 & AC3 bitrate controls can change
			 * when this control changes, but v4l2_ctrl_query_fill()
			 * already sets V4L2_CTRL_FLAG_UPDATE for
			 * V4L2_CID_MPEG_AUDIO_ENCODING, so we don't here.
			 */
			return v4l2_ctrl_query_fill(qctrl,
					V4L2_MPEG_AUDIO_ENCODING_LAYER_2,
					V4L2_MPEG_AUDIO_ENCODING_AC3, 1,
					default_params.audio_encoding);
		}

		return v4l2_ctrl_query_fill(qctrl,
				V4L2_MPEG_AUDIO_ENCODING_LAYER_2,
				V4L2_MPEG_AUDIO_ENCODING_LAYER_2, 1,
				default_params.audio_encoding);

	case V4L2_CID_MPEG_AUDIO_L2_BITRATE:
		err = v4l2_ctrl_query_fill(qctrl,
				V4L2_MPEG_AUDIO_L2_BITRATE_192K,
				V4L2_MPEG_AUDIO_L2_BITRATE_384K, 1,
				default_params.audio_l2_bitrate);
		if (err)
			return err;
		if (params->capabilities & CX2341X_CAP_HAS_AC3 &&
		    params->audio_encoding != V4L2_MPEG_AUDIO_ENCODING_LAYER_2)
			qctrl->flags |= V4L2_CTRL_FLAG_INACTIVE;
		return 0;

	case V4L2_CID_MPEG_AUDIO_MODE:
		return v4l2_ctrl_query_fill(qctrl,
				V4L2_MPEG_AUDIO_MODE_STEREO,
				V4L2_MPEG_AUDIO_MODE_MONO, 1,
				V4L2_MPEG_AUDIO_MODE_STEREO);

	case V4L2_CID_MPEG_AUDIO_MODE_EXTENSION:
		err = v4l2_ctrl_query_fill(qctrl,
				V4L2_MPEG_AUDIO_MODE_EXTENSION_BOUND_4,
				V4L2_MPEG_AUDIO_MODE_EXTENSION_BOUND_16, 1,
				V4L2_MPEG_AUDIO_MODE_EXTENSION_BOUND_4);
		if (err == 0 &&
		    params->audio_mode != V4L2_MPEG_AUDIO_MODE_JOINT_STEREO)
			qctrl->flags |= V4L2_CTRL_FLAG_INACTIVE;
		return err;

	case V4L2_CID_MPEG_AUDIO_EMPHASIS:
		return v4l2_ctrl_query_fill(qctrl,
				V4L2_MPEG_AUDIO_EMPHASIS_NONE,
				V4L2_MPEG_AUDIO_EMPHASIS_CCITT_J17, 1,
				V4L2_MPEG_AUDIO_EMPHASIS_NONE);

	case V4L2_CID_MPEG_AUDIO_CRC:
		return v4l2_ctrl_query_fill(qctrl,
				V4L2_MPEG_AUDIO_CRC_NONE,
				V4L2_MPEG_AUDIO_CRC_CRC16, 1,
				V4L2_MPEG_AUDIO_CRC_NONE);

	case V4L2_CID_MPEG_AUDIO_MUTE:
		return v4l2_ctrl_query_fill(qctrl, 0, 1, 1, 0);

	case V4L2_CID_MPEG_AUDIO_AC3_BITRATE:
		err = v4l2_ctrl_query_fill(qctrl,
				V4L2_MPEG_AUDIO_AC3_BITRATE_48K,
				V4L2_MPEG_AUDIO_AC3_BITRATE_448K, 1,
				default_params.audio_ac3_bitrate);
		if (err)
			return err;
		if (params->capabilities & CX2341X_CAP_HAS_AC3) {
			if (params->audio_encoding !=
						   V4L2_MPEG_AUDIO_ENCODING_AC3)
				qctrl->flags |= V4L2_CTRL_FLAG_INACTIVE;
		} else
			qctrl->flags |= V4L2_CTRL_FLAG_DISABLED;
		return 0;

	case V4L2_CID_MPEG_VIDEO_ENCODING:
		/* this setting is read-only for the cx2341x since the
		   V4L2_CID_MPEG_STREAM_TYPE really determines the
		   MPEG-1/2 setting */
		err = v4l2_ctrl_query_fill(qctrl,
					   V4L2_MPEG_VIDEO_ENCODING_MPEG_1,
					   V4L2_MPEG_VIDEO_ENCODING_MPEG_2, 1,
					   V4L2_MPEG_VIDEO_ENCODING_MPEG_2);
		if (err == 0)
			qctrl->flags |= V4L2_CTRL_FLAG_READ_ONLY;
		return err;

	case V4L2_CID_MPEG_VIDEO_ASPECT:
		return v4l2_ctrl_query_fill(qctrl,
				V4L2_MPEG_VIDEO_ASPECT_1x1,
				V4L2_MPEG_VIDEO_ASPECT_221x100, 1,
				V4L2_MPEG_VIDEO_ASPECT_4x3);

	case V4L2_CID_MPEG_VIDEO_B_FRAMES:
		return v4l2_ctrl_query_fill(qctrl, 0, 33, 1, 2);

	case V4L2_CID_MPEG_VIDEO_GOP_SIZE:
		return v4l2_ctrl_query_fill(qctrl, 1, 34, 1,
				params->is_50hz ? 12 : 15);

	case V4L2_CID_MPEG_VIDEO_GOP_CLOSURE:
		return v4l2_ctrl_query_fill(qctrl, 0, 1, 1, 1);

	case V4L2_CID_MPEG_VIDEO_BITRATE_MODE:
		err = v4l2_ctrl_query_fill(qctrl,
				V4L2_MPEG_VIDEO_BITRATE_MODE_VBR,
				V4L2_MPEG_VIDEO_BITRATE_MODE_CBR, 1,
				V4L2_MPEG_VIDEO_BITRATE_MODE_VBR);
		if (err == 0 &&
		    params->video_encoding == V4L2_MPEG_VIDEO_ENCODING_MPEG_1)
			qctrl->flags |= V4L2_CTRL_FLAG_INACTIVE;
		return err;

	case V4L2_CID_MPEG_VIDEO_BITRATE:
		return v4l2_ctrl_query_fill(qctrl, 0, 27000000, 1, 6000000);

	case V4L2_CID_MPEG_VIDEO_BITRATE_PEAK:
		err = v4l2_ctrl_query_fill(qctrl, 0, 27000000, 1, 8000000);
		if (err == 0 &&
		    params->video_bitrate_mode ==
				V4L2_MPEG_VIDEO_BITRATE_MODE_CBR)
			qctrl->flags |= V4L2_CTRL_FLAG_INACTIVE;
		return err;

	case V4L2_CID_MPEG_VIDEO_TEMPORAL_DECIMATION:
		return v4l2_ctrl_query_fill(qctrl, 0, 255, 1, 0);

	case V4L2_CID_MPEG_VIDEO_MUTE:
		return v4l2_ctrl_query_fill(qctrl, 0, 1, 1, 0);

	case V4L2_CID_MPEG_VIDEO_MUTE_YUV:  /* Init YUV (really YCbCr) to black */
		return v4l2_ctrl_query_fill(qctrl, 0, 0xffffff, 1, 0x008080);

	/* CX23415/6 specific */
	case V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE:
		return cx2341x_ctrl_query_fill(qctrl,
			V4L2_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE_MANUAL,
			V4L2_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE_AUTO, 1,
			default_params.video_spatial_filter_mode);

	case V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER:
		cx2341x_ctrl_query_fill(qctrl, 0, 15, 1,
				default_params.video_spatial_filter);
		qctrl->flags |= V4L2_CTRL_FLAG_SLIDER;
		if (params->video_spatial_filter_mode ==
			    V4L2_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE_AUTO)
			qctrl->flags |= V4L2_CTRL_FLAG_INACTIVE;
		return 0;

	case V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE:
		cx2341x_ctrl_query_fill(qctrl,
			V4L2_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE_OFF,
			V4L2_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE_2D_SYM_NON_SEPARABLE,
			1,
			default_params.video_luma_spatial_filter_type);
		if (params->video_spatial_filter_mode ==
			    V4L2_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE_AUTO)
			qctrl->flags |= V4L2_CTRL_FLAG_INACTIVE;
		return 0;

	case V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE:
		cx2341x_ctrl_query_fill(qctrl,
		    V4L2_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE_OFF,
		    V4L2_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE_1D_HOR,
		    1,
		    default_params.video_chroma_spatial_filter_type);
		if (params->video_spatial_filter_mode ==
			V4L2_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE_AUTO)
			qctrl->flags |= V4L2_CTRL_FLAG_INACTIVE;
		return 0;

	case V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE:
		return cx2341x_ctrl_query_fill(qctrl,
			V4L2_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE_MANUAL,
			V4L2_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE_AUTO, 1,
			default_params.video_temporal_filter_mode);

	case V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER:
		cx2341x_ctrl_query_fill(qctrl, 0, 31, 1,
				default_params.video_temporal_filter);
		qctrl->flags |= V4L2_CTRL_FLAG_SLIDER;
		if (params->video_temporal_filter_mode ==
			V4L2_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE_AUTO)
			qctrl->flags |= V4L2_CTRL_FLAG_INACTIVE;
		return 0;

	case V4L2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE:
		return cx2341x_ctrl_query_fill(qctrl,
			V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_OFF,
			V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_DIAG, 1,
			default_params.video_median_filter_type);

	case V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_TOP:
		cx2341x_ctrl_query_fill(qctrl, 0, 255, 1,
				default_params.video_luma_median_filter_top);
		qctrl->flags |= V4L2_CTRL_FLAG_SLIDER;
		if (params->video_median_filter_type ==
				V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_OFF)
			qctrl->flags |= V4L2_CTRL_FLAG_INACTIVE;
		return 0;

	case V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_BOTTOM:
		cx2341x_ctrl_query_fill(qctrl, 0, 255, 1,
				default_params.video_luma_median_filter_bottom);
		qctrl->flags |= V4L2_CTRL_FLAG_SLIDER;
		if (params->video_median_filter_type ==
				V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_OFF)
			qctrl->flags |= V4L2_CTRL_FLAG_INACTIVE;
		return 0;

	case V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_TOP:
		cx2341x_ctrl_query_fill(qctrl, 0, 255, 1,
				default_params.video_chroma_median_filter_top);
		qctrl->flags |= V4L2_CTRL_FLAG_SLIDER;
		if (params->video_median_filter_type ==
				V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_OFF)
			qctrl->flags |= V4L2_CTRL_FLAG_INACTIVE;
		return 0;

	case V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_BOTTOM:
		cx2341x_ctrl_query_fill(qctrl, 0, 255, 1,
			default_params.video_chroma_median_filter_bottom);
		qctrl->flags |= V4L2_CTRL_FLAG_SLIDER;
		if (params->video_median_filter_type ==
				V4L2_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE_OFF)
			qctrl->flags |= V4L2_CTRL_FLAG_INACTIVE;
		return 0;

	case V4L2_CID_MPEG_CX2341X_STREAM_INSERT_NAV_PACKETS:
		return cx2341x_ctrl_query_fill(qctrl, 0, 1, 1,
				default_params.stream_insert_nav_packets);

	default:
		return -EINVAL;

	}
}