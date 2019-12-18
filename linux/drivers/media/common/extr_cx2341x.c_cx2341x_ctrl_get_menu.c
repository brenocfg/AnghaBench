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
typedef  int u32 ;
struct cx2341x_mpeg_params {int capabilities; } ;

/* Variables and functions */
 int CX2341X_CAP_HAS_AC3 ; 
 int CX2341X_CAP_HAS_TS ; 
#define  V4L2_CID_MPEG_AUDIO_ENCODING 136 
#define  V4L2_CID_MPEG_AUDIO_L1_BITRATE 135 
#define  V4L2_CID_MPEG_AUDIO_L3_BITRATE 134 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE 133 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE 132 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE 131 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE 130 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE 129 
#define  V4L2_CID_MPEG_STREAM_TYPE 128 
 char const* const* cx2341x_get_menu (int) ; 
 char const* const* v4l2_ctrl_get_menu (int) ; 

const char * const *cx2341x_ctrl_get_menu(const struct cx2341x_mpeg_params *p, u32 id)
{
	static const char * const mpeg_stream_type_without_ts[] = {
		"MPEG-2 Program Stream",
		"",
		"MPEG-1 System Stream",
		"MPEG-2 DVD-compatible Stream",
		"MPEG-1 VCD-compatible Stream",
		"MPEG-2 SVCD-compatible Stream",
		NULL
	};

	static const char *mpeg_stream_type_with_ts[] = {
		"MPEG-2 Program Stream",
		"MPEG-2 Transport Stream",
		"MPEG-1 System Stream",
		"MPEG-2 DVD-compatible Stream",
		"MPEG-1 VCD-compatible Stream",
		"MPEG-2 SVCD-compatible Stream",
		NULL
	};

	static const char *mpeg_audio_encoding_l2_ac3[] = {
		"",
		"MPEG-1/2 Layer II",
		"",
		"",
		"AC-3",
		NULL
	};

	switch (id) {
	case V4L2_CID_MPEG_STREAM_TYPE:
		return (p->capabilities & CX2341X_CAP_HAS_TS) ?
			mpeg_stream_type_with_ts : mpeg_stream_type_without_ts;
	case V4L2_CID_MPEG_AUDIO_ENCODING:
		return (p->capabilities & CX2341X_CAP_HAS_AC3) ?
			mpeg_audio_encoding_l2_ac3 : v4l2_ctrl_get_menu(id);
	case V4L2_CID_MPEG_AUDIO_L1_BITRATE:
	case V4L2_CID_MPEG_AUDIO_L3_BITRATE:
		return NULL;
	case V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE:
	case V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE:
	case V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE:
	case V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE:
	case V4L2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE:
		return cx2341x_get_menu(id);
	default:
		return v4l2_ctrl_get_menu(id);
	}
}