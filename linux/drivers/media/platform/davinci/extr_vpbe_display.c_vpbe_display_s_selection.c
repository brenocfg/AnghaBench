#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct osd_layer_config {int dummy; } ;
struct TYPE_3__ {scalar_t__ h_zoom; scalar_t__ v_zoom; scalar_t__ h_exp; scalar_t__ v_exp; int /*<<< orphan*/  id; struct osd_layer_config config; } ;
struct vpbe_layer {TYPE_1__ layer_info; int /*<<< orphan*/  device_id; struct vpbe_display* disp_dev; } ;
struct vpbe_display {struct osd_state* osd_device; struct vpbe_device* vpbe_dev; } ;
struct vpbe_device {int /*<<< orphan*/  v4l2_dev; } ;
struct v4l2_rect {scalar_t__ top; scalar_t__ left; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_selection {scalar_t__ type; scalar_t__ target; struct v4l2_rect r; } ;
struct TYPE_4__ {int (* set_layer_config ) (struct osd_state*,int /*<<< orphan*/ ,struct osd_layer_config*) ;int (* set_vid_expansion ) (struct osd_state*,scalar_t__,scalar_t__) ;int /*<<< orphan*/  (* set_interpolation_filter ) (struct osd_state*,int) ;int /*<<< orphan*/  (* set_zoom ) (struct osd_state*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ;int /*<<< orphan*/  (* get_layer_config ) (struct osd_state*,int /*<<< orphan*/ ,struct osd_layer_config*) ;} ;
struct osd_state {TYPE_2__ ops; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ H_EXP_OFF ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 scalar_t__ V4L2_SEL_TGT_CROP ; 
 scalar_t__ V_EXP_OFF ; 
 scalar_t__ ZOOM_X1 ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  stub1 (struct osd_state*,int /*<<< orphan*/ ,struct osd_layer_config*) ; 
 int stub2 (struct osd_state*,int /*<<< orphan*/ ,struct osd_layer_config*) ; 
 int /*<<< orphan*/  stub3 (struct osd_state*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int stub4 (struct osd_state*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub5 (struct osd_state*,int) ; 
 int /*<<< orphan*/  stub6 (struct osd_state*,int) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 struct vpbe_layer* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  vpbe_disp_adj_position (struct vpbe_display*,struct vpbe_layer*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vpbe_disp_calculate_scale_factor (struct vpbe_display*,struct vpbe_layer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpbe_disp_check_window_params (struct vpbe_display*,struct v4l2_rect*) ; 

__attribute__((used)) static int vpbe_display_s_selection(struct file *file, void *priv,
			     struct v4l2_selection *sel)
{
	struct vpbe_layer *layer = video_drvdata(file);
	struct vpbe_display *disp_dev = layer->disp_dev;
	struct vpbe_device *vpbe_dev = disp_dev->vpbe_dev;
	struct osd_layer_config *cfg = &layer->layer_info.config;
	struct osd_state *osd_device = disp_dev->osd_device;
	struct v4l2_rect rect = sel->r;
	int ret;

	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev,
		"VIDIOC_S_SELECTION, layer id = %d\n", layer->device_id);

	if (sel->type != V4L2_BUF_TYPE_VIDEO_OUTPUT ||
	    sel->target != V4L2_SEL_TGT_CROP)
		return -EINVAL;

	if (rect.top < 0)
		rect.top = 0;
	if (rect.left < 0)
		rect.left = 0;

	vpbe_disp_check_window_params(disp_dev, &rect);

	osd_device->ops.get_layer_config(osd_device,
			layer->layer_info.id, cfg);

	vpbe_disp_calculate_scale_factor(disp_dev, layer,
					rect.width,
					rect.height);
	vpbe_disp_adj_position(disp_dev, layer, rect.top,
					rect.left);
	ret = osd_device->ops.set_layer_config(osd_device,
				layer->layer_info.id, cfg);
	if (ret < 0) {
		v4l2_err(&vpbe_dev->v4l2_dev,
			"Error in set layer config:\n");
		return -EINVAL;
	}

	/* apply zooming and h or v expansion */
	osd_device->ops.set_zoom(osd_device,
			layer->layer_info.id,
			layer->layer_info.h_zoom,
			layer->layer_info.v_zoom);
	ret = osd_device->ops.set_vid_expansion(osd_device,
			layer->layer_info.h_exp,
			layer->layer_info.v_exp);
	if (ret < 0) {
		v4l2_err(&vpbe_dev->v4l2_dev,
		"Error in set vid expansion:\n");
		return -EINVAL;
	}

	if ((layer->layer_info.h_zoom != ZOOM_X1) ||
		(layer->layer_info.v_zoom != ZOOM_X1) ||
		(layer->layer_info.h_exp != H_EXP_OFF) ||
		(layer->layer_info.v_exp != V_EXP_OFF))
		/* Enable expansion filter */
		osd_device->ops.set_interpolation_filter(osd_device, 1);
	else
		osd_device->ops.set_interpolation_filter(osd_device, 0);

	sel->r = rect;
	return 0;
}