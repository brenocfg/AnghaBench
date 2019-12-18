#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct osd_layer_config {int /*<<< orphan*/  ysize; int /*<<< orphan*/  xsize; int /*<<< orphan*/  xpos; int /*<<< orphan*/  ypos; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; struct osd_layer_config config; } ;
struct vpbe_layer {TYPE_3__ layer_info; int /*<<< orphan*/  device_id; TYPE_1__* disp_dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; } ;
struct vpbe_device {TYPE_4__ current_timings; int /*<<< orphan*/  v4l2_dev; } ;
struct v4l2_rect {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct v4l2_selection {scalar_t__ type; int target; struct v4l2_rect r; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* get_layer_config ) (struct osd_state*,int /*<<< orphan*/ ,struct osd_layer_config*) ;} ;
struct osd_state {TYPE_2__ ops; } ;
struct file {int dummy; } ;
struct TYPE_5__ {struct osd_state* osd_device; struct vpbe_device* vpbe_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
#define  V4L2_SEL_TGT_CROP 130 
#define  V4L2_SEL_TGT_CROP_BOUNDS 129 
#define  V4L2_SEL_TGT_CROP_DEFAULT 128 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  stub1 (struct osd_state*,int /*<<< orphan*/ ,struct osd_layer_config*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct vpbe_layer* video_drvdata (struct file*) ; 

__attribute__((used)) static int vpbe_display_g_selection(struct file *file, void *priv,
				    struct v4l2_selection *sel)
{
	struct vpbe_layer *layer = video_drvdata(file);
	struct osd_layer_config *cfg = &layer->layer_info.config;
	struct vpbe_device *vpbe_dev = layer->disp_dev->vpbe_dev;
	struct osd_state *osd_device = layer->disp_dev->osd_device;
	struct v4l2_rect *rect = &sel->r;

	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev,
			"VIDIOC_G_SELECTION, layer id = %d\n",
			layer->device_id);

	if (sel->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		return -EINVAL;

	switch (sel->target) {
	case V4L2_SEL_TGT_CROP:
		osd_device->ops.get_layer_config(osd_device,
						 layer->layer_info.id, cfg);
		rect->top = cfg->ypos;
		rect->left = cfg->xpos;
		rect->width = cfg->xsize;
		rect->height = cfg->ysize;
		break;
	case V4L2_SEL_TGT_CROP_DEFAULT:
	case V4L2_SEL_TGT_CROP_BOUNDS:
		rect->left = 0;
		rect->top = 0;
		rect->width = vpbe_dev->current_timings.xres;
		rect->height = vpbe_dev->current_timings.yres;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}