#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct v4l2_ext_control {int id; int /*<<< orphan*/  value; } ;
struct cx2341x_mpeg_params {int /*<<< orphan*/  stream_insert_nav_packets; int /*<<< orphan*/  video_chroma_median_filter_bottom; int /*<<< orphan*/  video_chroma_median_filter_top; int /*<<< orphan*/  video_luma_median_filter_bottom; int /*<<< orphan*/  video_luma_median_filter_top; int /*<<< orphan*/  video_median_filter_type; int /*<<< orphan*/  video_temporal_filter; int /*<<< orphan*/  video_temporal_filter_mode; int /*<<< orphan*/  video_chroma_spatial_filter_type; int /*<<< orphan*/  video_luma_spatial_filter_type; int /*<<< orphan*/  video_spatial_filter; int /*<<< orphan*/  video_spatial_filter_mode; int /*<<< orphan*/  stream_vbi_fmt; int /*<<< orphan*/  stream_type; int /*<<< orphan*/  video_mute_yuv; int /*<<< orphan*/  video_mute; int /*<<< orphan*/  video_temporal_decimation; int /*<<< orphan*/  video_bitrate_peak; int /*<<< orphan*/  video_bitrate; int /*<<< orphan*/  video_bitrate_mode; int /*<<< orphan*/  video_gop_closure; int /*<<< orphan*/  video_gop_size; int /*<<< orphan*/  video_b_frames; int /*<<< orphan*/  video_aspect; int /*<<< orphan*/  video_encoding; int /*<<< orphan*/  audio_mute; int /*<<< orphan*/  audio_crc; int /*<<< orphan*/  audio_emphasis; int /*<<< orphan*/  audio_mode_extension; int /*<<< orphan*/  audio_mode; int /*<<< orphan*/  audio_ac3_bitrate; int /*<<< orphan*/  audio_l2_bitrate; int /*<<< orphan*/  audio_encoding; int /*<<< orphan*/  audio_sampling_freq; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_MPEG_AUDIO_AC3_BITRATE 161 
#define  V4L2_CID_MPEG_AUDIO_CRC 160 
#define  V4L2_CID_MPEG_AUDIO_EMPHASIS 159 
#define  V4L2_CID_MPEG_AUDIO_ENCODING 158 
#define  V4L2_CID_MPEG_AUDIO_L2_BITRATE 157 
#define  V4L2_CID_MPEG_AUDIO_MODE 156 
#define  V4L2_CID_MPEG_AUDIO_MODE_EXTENSION 155 
#define  V4L2_CID_MPEG_AUDIO_MUTE 154 
#define  V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ 153 
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

__attribute__((used)) static int cx2341x_get_ctrl(const struct cx2341x_mpeg_params *params,
		struct v4l2_ext_control *ctrl)
{
	switch (ctrl->id) {
	case V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ:
		ctrl->value = params->audio_sampling_freq;
		break;
	case V4L2_CID_MPEG_AUDIO_ENCODING:
		ctrl->value = params->audio_encoding;
		break;
	case V4L2_CID_MPEG_AUDIO_L2_BITRATE:
		ctrl->value = params->audio_l2_bitrate;
		break;
	case V4L2_CID_MPEG_AUDIO_AC3_BITRATE:
		ctrl->value = params->audio_ac3_bitrate;
		break;
	case V4L2_CID_MPEG_AUDIO_MODE:
		ctrl->value = params->audio_mode;
		break;
	case V4L2_CID_MPEG_AUDIO_MODE_EXTENSION:
		ctrl->value = params->audio_mode_extension;
		break;
	case V4L2_CID_MPEG_AUDIO_EMPHASIS:
		ctrl->value = params->audio_emphasis;
		break;
	case V4L2_CID_MPEG_AUDIO_CRC:
		ctrl->value = params->audio_crc;
		break;
	case V4L2_CID_MPEG_AUDIO_MUTE:
		ctrl->value = params->audio_mute;
		break;
	case V4L2_CID_MPEG_VIDEO_ENCODING:
		ctrl->value = params->video_encoding;
		break;
	case V4L2_CID_MPEG_VIDEO_ASPECT:
		ctrl->value = params->video_aspect;
		break;
	case V4L2_CID_MPEG_VIDEO_B_FRAMES:
		ctrl->value = params->video_b_frames;
		break;
	case V4L2_CID_MPEG_VIDEO_GOP_SIZE:
		ctrl->value = params->video_gop_size;
		break;
	case V4L2_CID_MPEG_VIDEO_GOP_CLOSURE:
		ctrl->value = params->video_gop_closure;
		break;
	case V4L2_CID_MPEG_VIDEO_BITRATE_MODE:
		ctrl->value = params->video_bitrate_mode;
		break;
	case V4L2_CID_MPEG_VIDEO_BITRATE:
		ctrl->value = params->video_bitrate;
		break;
	case V4L2_CID_MPEG_VIDEO_BITRATE_PEAK:
		ctrl->value = params->video_bitrate_peak;
		break;
	case V4L2_CID_MPEG_VIDEO_TEMPORAL_DECIMATION:
		ctrl->value = params->video_temporal_decimation;
		break;
	case V4L2_CID_MPEG_VIDEO_MUTE:
		ctrl->value = params->video_mute;
		break;
	case V4L2_CID_MPEG_VIDEO_MUTE_YUV:
		ctrl->value = params->video_mute_yuv;
		break;
	case V4L2_CID_MPEG_STREAM_TYPE:
		ctrl->value = params->stream_type;
		break;
	case V4L2_CID_MPEG_STREAM_VBI_FMT:
		ctrl->value = params->stream_vbi_fmt;
		break;
	case V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE:
		ctrl->value = params->video_spatial_filter_mode;
		break;
	case V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER:
		ctrl->value = params->video_spatial_filter;
		break;
	case V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE:
		ctrl->value = params->video_luma_spatial_filter_type;
		break;
	case V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE:
		ctrl->value = params->video_chroma_spatial_filter_type;
		break;
	case V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE:
		ctrl->value = params->video_temporal_filter_mode;
		break;
	case V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER:
		ctrl->value = params->video_temporal_filter;
		break;
	case V4L2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE:
		ctrl->value = params->video_median_filter_type;
		break;
	case V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_TOP:
		ctrl->value = params->video_luma_median_filter_top;
		break;
	case V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_BOTTOM:
		ctrl->value = params->video_luma_median_filter_bottom;
		break;
	case V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_TOP:
		ctrl->value = params->video_chroma_median_filter_top;
		break;
	case V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_BOTTOM:
		ctrl->value = params->video_chroma_median_filter_bottom;
		break;
	case V4L2_CID_MPEG_CX2341X_STREAM_INSERT_NAV_PACKETS:
		ctrl->value = params->stream_insert_nav_packets;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}