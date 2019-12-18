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

/* Variables and functions */
#define  V4L2_CID_MPEG_CX2341X_STREAM_INSERT_NAV_PACKETS 139 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_BOTTOM 138 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_TOP 137 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE 136 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_BOTTOM 135 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_TOP 134 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE 133 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE 132 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER 131 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE 130 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER 129 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE 128 

__attribute__((used)) static const char *cx2341x_get_name(u32 id)
{
	switch (id) {
	case V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE:
		return "Spatial Filter Mode";
	case V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER:
		return "Spatial Filter";
	case V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE:
		return "Spatial Luma Filter Type";
	case V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE:
		return "Spatial Chroma Filter Type";
	case V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE:
		return "Temporal Filter Mode";
	case V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER:
		return "Temporal Filter";
	case V4L2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE:
		return "Median Filter Type";
	case V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_TOP:
		return "Median Luma Filter Maximum";
	case V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_BOTTOM:
		return "Median Luma Filter Minimum";
	case V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_TOP:
		return "Median Chroma Filter Maximum";
	case V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_BOTTOM:
		return "Median Chroma Filter Minimum";
	case V4L2_CID_MPEG_CX2341X_STREAM_INSERT_NAV_PACKETS:
		return "Insert Navigation Packets";
	}
	return NULL;
}