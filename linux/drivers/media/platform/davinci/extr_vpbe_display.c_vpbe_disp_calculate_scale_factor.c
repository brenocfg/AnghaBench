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
typedef  int v4l2_std_id ;
struct osd_layer_config {int xsize; int ysize; } ;
struct display_layer_info {int /*<<< orphan*/  v_exp; void* v_zoom; int /*<<< orphan*/  h_exp; void* h_zoom; struct osd_layer_config config; } ;
struct v4l2_pix_format {int width; int height; } ;
struct vpbe_layer {struct display_layer_info layer_info; struct v4l2_pix_format pix_fmt; } ;
struct vpbe_display {struct vpbe_device* vpbe_dev; } ;
struct TYPE_2__ {int std_id; int xres; } ;
struct vpbe_device {int /*<<< orphan*/  v4l2_dev; TYPE_1__ current_timings; } ;

/* Variables and functions */
 int /*<<< orphan*/  H_EXP_9_OVER_8 ; 
 int /*<<< orphan*/  H_EXP_OFF ; 
 int V4L2_STD_525_60 ; 
 int V4L2_STD_625_50 ; 
 int VPBE_DISPLAY_H_EXP_RATIO_D ; 
 int VPBE_DISPLAY_H_EXP_RATIO_N ; 
 int VPBE_DISPLAY_V_EXP_RATIO_D ; 
 int VPBE_DISPLAY_V_EXP_RATIO_N ; 
 int /*<<< orphan*/  V_EXP_6_OVER_5 ; 
 int /*<<< orphan*/  V_EXP_OFF ; 
 void* ZOOM_X1 ; 
 void* ZOOM_X2 ; 
 void* ZOOM_X4 ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int,int) ; 

__attribute__((used)) static void
vpbe_disp_calculate_scale_factor(struct vpbe_display *disp_dev,
			struct vpbe_layer *layer,
			int expected_xsize, int expected_ysize)
{
	struct display_layer_info *layer_info = &layer->layer_info;
	struct v4l2_pix_format *pixfmt = &layer->pix_fmt;
	struct osd_layer_config *cfg  = &layer->layer_info.config;
	struct vpbe_device *vpbe_dev = disp_dev->vpbe_dev;
	int calculated_xsize;
	int h_exp = 0;
	int v_exp = 0;
	int h_scale;
	int v_scale;

	v4l2_std_id standard_id = vpbe_dev->current_timings.std_id;

	/*
	 * Application initially set the image format. Current display
	 * size is obtained from the vpbe display controller. expected_xsize
	 * and expected_ysize are set through S_SELECTION ioctl. Based on this,
	 * driver will calculate the scale factors for vertical and
	 * horizontal direction so that the image is displayed scaled
	 * and expanded. Application uses expansion to display the image
	 * in a square pixel. Otherwise it is displayed using displays
	 * pixel aspect ratio.It is expected that application chooses
	 * the crop coordinates for cropped or scaled display. if crop
	 * size is less than the image size, it is displayed cropped or
	 * it is displayed scaled and/or expanded.
	 *
	 * to begin with, set the crop window same as expected. Later we
	 * will override with scaled window size
	 */

	cfg->xsize = pixfmt->width;
	cfg->ysize = pixfmt->height;
	layer_info->h_zoom = ZOOM_X1;	/* no horizontal zoom */
	layer_info->v_zoom = ZOOM_X1;	/* no horizontal zoom */
	layer_info->h_exp = H_EXP_OFF;	/* no horizontal zoom */
	layer_info->v_exp = V_EXP_OFF;	/* no horizontal zoom */

	if (pixfmt->width < expected_xsize) {
		h_scale = vpbe_dev->current_timings.xres / pixfmt->width;
		if (h_scale < 2)
			h_scale = 1;
		else if (h_scale >= 4)
			h_scale = 4;
		else
			h_scale = 2;
		cfg->xsize *= h_scale;
		if (cfg->xsize < expected_xsize) {
			if ((standard_id & V4L2_STD_525_60) ||
			(standard_id & V4L2_STD_625_50)) {
				calculated_xsize = (cfg->xsize *
					VPBE_DISPLAY_H_EXP_RATIO_N) /
					VPBE_DISPLAY_H_EXP_RATIO_D;
				if (calculated_xsize <= expected_xsize) {
					h_exp = 1;
					cfg->xsize = calculated_xsize;
				}
			}
		}
		if (h_scale == 2)
			layer_info->h_zoom = ZOOM_X2;
		else if (h_scale == 4)
			layer_info->h_zoom = ZOOM_X4;
		if (h_exp)
			layer_info->h_exp = H_EXP_9_OVER_8;
	} else {
		/* no scaling, only cropping. Set display area to crop area */
		cfg->xsize = expected_xsize;
	}

	if (pixfmt->height < expected_ysize) {
		v_scale = expected_ysize / pixfmt->height;
		if (v_scale < 2)
			v_scale = 1;
		else if (v_scale >= 4)
			v_scale = 4;
		else
			v_scale = 2;
		cfg->ysize *= v_scale;
		if (cfg->ysize < expected_ysize) {
			if ((standard_id & V4L2_STD_625_50)) {
				calculated_xsize = (cfg->ysize *
					VPBE_DISPLAY_V_EXP_RATIO_N) /
					VPBE_DISPLAY_V_EXP_RATIO_D;
				if (calculated_xsize <= expected_ysize) {
					v_exp = 1;
					cfg->ysize = calculated_xsize;
				}
			}
		}
		if (v_scale == 2)
			layer_info->v_zoom = ZOOM_X2;
		else if (v_scale == 4)
			layer_info->v_zoom = ZOOM_X4;
		if (v_exp)
			layer_info->v_exp = V_EXP_6_OVER_5;
	} else {
		/* no scaling, only cropping. Set display area to crop area */
		cfg->ysize = expected_ysize;
	}
	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev,
		"crop display xsize = %d, ysize = %d\n",
		cfg->xsize, cfg->ysize);
}