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
struct v4l2_queryctrl {int id; int /*<<< orphan*/  name; int /*<<< orphan*/ * reserved; void* default_value; void* step; void* maximum; void* minimum; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;
typedef  void* s32 ;

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
 int /*<<< orphan*/  cx2341x_ctrl_fill (int,char const**,int /*<<< orphan*/ *,void**,void**,void**,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char const*,int) ; 
 int v4l2_ctrl_query_fill (struct v4l2_queryctrl*,void*,void*,void*,void*) ; 

__attribute__((used)) static int cx2341x_ctrl_query_fill(struct v4l2_queryctrl *qctrl,
				   s32 min, s32 max, s32 step, s32 def)
{
	const char *name;

	switch (qctrl->id) {
	/* MPEG controls */
	case V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE:
	case V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER:
	case V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE:
	case V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE:
	case V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE:
	case V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER:
	case V4L2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE:
	case V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_TOP:
	case V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_BOTTOM:
	case V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_TOP:
	case V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_BOTTOM:
	case V4L2_CID_MPEG_CX2341X_STREAM_INSERT_NAV_PACKETS:
		cx2341x_ctrl_fill(qctrl->id, &name, &qctrl->type,
				&min, &max, &step, &def, &qctrl->flags);
		qctrl->minimum = min;
		qctrl->maximum = max;
		qctrl->step = step;
		qctrl->default_value = def;
		qctrl->reserved[0] = qctrl->reserved[1] = 0;
		strscpy(qctrl->name, name, sizeof(qctrl->name));
		return 0;

	default:
		return v4l2_ctrl_query_fill(qctrl, min, max, step, def);
	}
}