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
struct v4l2_pix_format {int pixelformat; } ;
struct omapvideo_info {struct omap_overlay** overlays; } ;
struct omap_vout_device {struct omapvideo_info vid_info; struct v4l2_pix_format pix; } ;
struct omap_overlay {int /*<<< orphan*/  id; } ;
typedef  enum omap_color_mode { ____Placeholder_omap_color_mode } omap_color_mode ;

/* Variables and functions */
 int EINVAL ; 
 int OMAP_DSS_COLOR_ARGB32 ; 
 int OMAP_DSS_COLOR_RGB16 ; 
 int OMAP_DSS_COLOR_RGB24P ; 
 int OMAP_DSS_COLOR_RGB24U ; 
 int OMAP_DSS_COLOR_RGBX32 ; 
 int OMAP_DSS_COLOR_UYVY ; 
 int OMAP_DSS_COLOR_YUV2 ; 
 int /*<<< orphan*/  OMAP_DSS_VIDEO1 ; 
#define  V4L2_PIX_FMT_BGR32 133 
#define  V4L2_PIX_FMT_RGB24 132 
#define  V4L2_PIX_FMT_RGB32 131 
#define  V4L2_PIX_FMT_RGB565 130 
#define  V4L2_PIX_FMT_UYVY 129 
#define  V4L2_PIX_FMT_YUYV 128 

__attribute__((used)) static int video_mode_to_dss_mode(struct omap_vout_device *vout)
{
	struct omap_overlay *ovl;
	struct omapvideo_info *ovid;
	struct v4l2_pix_format *pix = &vout->pix;
	enum omap_color_mode mode;

	ovid = &vout->vid_info;
	ovl = ovid->overlays[0];

	switch (pix->pixelformat) {
	case V4L2_PIX_FMT_YUYV:
		mode = OMAP_DSS_COLOR_YUV2;
		break;
	case V4L2_PIX_FMT_UYVY:
		mode = OMAP_DSS_COLOR_UYVY;
		break;
	case V4L2_PIX_FMT_RGB565:
		mode = OMAP_DSS_COLOR_RGB16;
		break;
	case V4L2_PIX_FMT_RGB24:
		mode = OMAP_DSS_COLOR_RGB24P;
		break;
	case V4L2_PIX_FMT_RGB32:
		mode = (ovl->id == OMAP_DSS_VIDEO1) ?
			OMAP_DSS_COLOR_RGB24U : OMAP_DSS_COLOR_ARGB32;
		break;
	case V4L2_PIX_FMT_BGR32:
		mode = OMAP_DSS_COLOR_RGBX32;
		break;
	default:
		mode = -EINVAL;
		break;
	}
	return mode;
}