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
#define  V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE 132 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE 131 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE 130 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE 129 
#define  V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE 128 

__attribute__((used)) static const char **cx2341x_get_menu(u32 id)
{
	static const char *cx2341x_video_spatial_filter_mode_menu[] = {
		"Manual",
		"Auto",
		NULL
	};

	static const char *cx2341x_video_luma_spatial_filter_type_menu[] = {
		"Off",
		"1D Horizontal",
		"1D Vertical",
		"2D H/V Separable",
		"2D Symmetric non-separable",
		NULL
	};

	static const char *cx2341x_video_chroma_spatial_filter_type_menu[] = {
		"Off",
		"1D Horizontal",
		NULL
	};

	static const char *cx2341x_video_temporal_filter_mode_menu[] = {
		"Manual",
		"Auto",
		NULL
	};

	static const char *cx2341x_video_median_filter_type_menu[] = {
		"Off",
		"Horizontal",
		"Vertical",
		"Horizontal/Vertical",
		"Diagonal",
		NULL
	};

	switch (id) {
	case V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE:
		return cx2341x_video_spatial_filter_mode_menu;
	case V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE:
		return cx2341x_video_luma_spatial_filter_type_menu;
	case V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE:
		return cx2341x_video_chroma_spatial_filter_type_menu;
	case V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE:
		return cx2341x_video_temporal_filter_mode_menu;
	case V4L2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE:
		return cx2341x_video_median_filter_type_menu;
	}
	return NULL;
}