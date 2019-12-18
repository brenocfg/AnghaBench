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
struct osd_layer_config {void* pixfmt; int /*<<< orphan*/  interlaced; scalar_t__ xpos; scalar_t__ ypos; int /*<<< orphan*/  line_length; int /*<<< orphan*/  ysize; int /*<<< orphan*/  xsize; } ;
struct TYPE_8__ {int /*<<< orphan*/  id; struct osd_layer_config config; } ;
struct v4l2_pix_format {scalar_t__ pixelformat; int /*<<< orphan*/  bytesperline; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct vpbe_layer {TYPE_4__ layer_info; struct v4l2_pix_format pix_fmt; int /*<<< orphan*/  buffer_queue; int /*<<< orphan*/  device_id; struct vpbe_display* disp_dev; } ;
struct vpbe_display {struct osd_state* osd_device; struct vpbe_device* vpbe_dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  interlaced; } ;
struct vpbe_device {int /*<<< orphan*/  v4l2_dev; TYPE_2__ current_timings; } ;
struct TYPE_5__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {scalar_t__ type; TYPE_1__ fmt; } ;
struct TYPE_7__ {int (* request_layer ) (struct osd_state*,int /*<<< orphan*/ ) ;int (* set_layer_config ) (struct osd_state*,int /*<<< orphan*/ ,struct osd_layer_config*) ;int /*<<< orphan*/  (* get_layer_config ) (struct osd_state*,int /*<<< orphan*/ ,struct osd_layer_config*) ;} ;
struct osd_state {TYPE_3__ ops; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 void* PIXFMT_NV12 ; 
 void* PIXFMT_YCBCRI ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 scalar_t__ V4L2_PIX_FMT_NV12 ; 
 scalar_t__ V4L2_PIX_FMT_UYVY ; 
 struct vpbe_layer* _vpbe_display_get_other_win_layer (struct vpbe_display*,struct vpbe_layer*) ; 
 int /*<<< orphan*/  debug ; 
 int stub1 (struct osd_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct osd_state*,int /*<<< orphan*/ ,struct osd_layer_config*) ; 
 int stub3 (struct osd_state*,int /*<<< orphan*/ ,struct osd_layer_config*) ; 
 int /*<<< orphan*/  stub4 (struct osd_state*,int /*<<< orphan*/ ,struct osd_layer_config*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 struct vpbe_layer* video_drvdata (struct file*) ; 
 int vpbe_try_format (struct vpbe_display*,struct v4l2_pix_format*,int) ; 

__attribute__((used)) static int vpbe_display_s_fmt(struct file *file, void *priv,
				struct v4l2_format *fmt)
{
	struct vpbe_layer *layer = video_drvdata(file);
	struct vpbe_display *disp_dev = layer->disp_dev;
	struct vpbe_device *vpbe_dev = disp_dev->vpbe_dev;
	struct osd_layer_config *cfg  = &layer->layer_info.config;
	struct v4l2_pix_format *pixfmt = &fmt->fmt.pix;
	struct osd_state *osd_device = disp_dev->osd_device;
	int ret;

	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev,
			"VIDIOC_S_FMT, layer id = %d\n",
			layer->device_id);

	if (vb2_is_busy(&layer->buffer_queue))
		return -EBUSY;

	if (V4L2_BUF_TYPE_VIDEO_OUTPUT != fmt->type) {
		v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev, "invalid type\n");
		return -EINVAL;
	}
	/* Check for valid pixel format */
	ret = vpbe_try_format(disp_dev, pixfmt, 1);
	if (ret)
		return ret;

	/* YUV420 is requested, check availability of the
	other video window */

	layer->pix_fmt = *pixfmt;
	if (pixfmt->pixelformat == V4L2_PIX_FMT_NV12) {
		struct vpbe_layer *otherlayer;

		otherlayer = _vpbe_display_get_other_win_layer(disp_dev, layer);
		/* if other layer is available, only
		 * claim it, do not configure it
		 */
		ret = osd_device->ops.request_layer(osd_device,
						    otherlayer->layer_info.id);
		if (ret < 0) {
			v4l2_err(&vpbe_dev->v4l2_dev,
				 "Display Manager failed to allocate layer\n");
			return -EBUSY;
		}
	}

	/* Get osd layer config */
	osd_device->ops.get_layer_config(osd_device,
			layer->layer_info.id, cfg);
	/* Store the pixel format in the layer object */
	cfg->xsize = pixfmt->width;
	cfg->ysize = pixfmt->height;
	cfg->line_length = pixfmt->bytesperline;
	cfg->ypos = 0;
	cfg->xpos = 0;
	cfg->interlaced = vpbe_dev->current_timings.interlaced;

	if (V4L2_PIX_FMT_UYVY == pixfmt->pixelformat)
		cfg->pixfmt = PIXFMT_YCBCRI;

	/* Change of the default pixel format for both video windows */
	if (V4L2_PIX_FMT_NV12 == pixfmt->pixelformat) {
		struct vpbe_layer *otherlayer;
		cfg->pixfmt = PIXFMT_NV12;
		otherlayer = _vpbe_display_get_other_win_layer(disp_dev,
								layer);
		otherlayer->layer_info.config.pixfmt = PIXFMT_NV12;
	}

	/* Set the layer config in the osd window */
	ret = osd_device->ops.set_layer_config(osd_device,
				layer->layer_info.id, cfg);
	if (ret < 0) {
		v4l2_err(&vpbe_dev->v4l2_dev,
				"Error in S_FMT params:\n");
		return -EINVAL;
	}

	/* Readback and fill the local copy of current pix format */
	osd_device->ops.get_layer_config(osd_device,
			layer->layer_info.id, cfg);

	return 0;
}