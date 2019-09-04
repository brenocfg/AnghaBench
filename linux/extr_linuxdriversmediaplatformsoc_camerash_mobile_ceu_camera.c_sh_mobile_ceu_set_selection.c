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
struct v4l2_mbus_framefmt {int width; int height; } ;
struct v4l2_subdev_format {struct v4l2_mbus_framefmt format; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int /*<<< orphan*/  v4l2_dev; } ;
struct v4l2_rect {unsigned int width; unsigned int height; int left; int top; } ;
struct v4l2_selection {struct v4l2_rect r; } ;
struct soc_camera_host {struct sh_mobile_ceu_dev* priv; } ;
struct soc_camera_device {int user_width; int user_height; struct sh_mobile_ceu_cam* host_priv; struct device* parent; } ;
struct sh_mobile_ceu_dev {int cflcr; int max_width; int max_height; scalar_t__ active; scalar_t__ image_mode; } ;
struct sh_mobile_ceu_cam {int width; int height; int ceu_left; int ceu_top; struct v4l2_rect subrect; int /*<<< orphan*/  rect; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFLCR ; 
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 void* calc_generic_scale (unsigned int,int) ; 
 unsigned int calc_scale (int,unsigned int*) ; 
 int /*<<< orphan*/  capture_restore (struct sh_mobile_ceu_dev*,int) ; 
 int capture_save_reset (struct sh_mobile_ceu_dev*) ; 
 int /*<<< orphan*/  ceu_write (struct sh_mobile_ceu_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int) ; 
 int /*<<< orphan*/  dev_geo (struct device*,char*,unsigned int,unsigned int,...) ; 
 int /*<<< orphan*/  get_fmt ; 
 unsigned int min (int,int) ; 
 int /*<<< orphan*/  pad ; 
 int scale_down (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  set_fmt ; 
 int /*<<< orphan*/  sh_mobile_ceu_set_rect (struct soc_camera_device*) ; 
 int soc_camera_client_s_selection (struct v4l2_subdev*,struct v4l2_selection*,struct v4l2_selection*,int /*<<< orphan*/ *,struct v4l2_rect*) ; 
 int /*<<< orphan*/  soc_camera_grp_id (struct soc_camera_device*) ; 
 struct v4l2_subdev* soc_camera_to_subdev (struct soc_camera_device*) ; 
 struct soc_camera_host* to_soc_camera_host (struct device*) ; 
 int v4l2_device_call_until_err (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_format*) ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_format*) ; 

__attribute__((used)) static int sh_mobile_ceu_set_selection(struct soc_camera_device *icd,
				       struct v4l2_selection *sel)
{
	struct v4l2_rect *rect = &sel->r;
	struct device *dev = icd->parent;
	struct soc_camera_host *ici = to_soc_camera_host(dev);
	struct sh_mobile_ceu_dev *pcdev = ici->priv;
	struct v4l2_selection cam_sel;
	struct sh_mobile_ceu_cam *cam = icd->host_priv;
	struct v4l2_rect *cam_rect = &cam_sel.r;
	struct v4l2_subdev *sd = soc_camera_to_subdev(icd);
	struct v4l2_subdev_format fmt = {
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	};
	struct v4l2_mbus_framefmt *mf = &fmt.format;
	unsigned int scale_cam_h, scale_cam_v, scale_ceu_h, scale_ceu_v,
		out_width, out_height;
	int interm_width, interm_height;
	u32 capsr, cflcr;
	int ret;

	dev_geo(dev, "S_SELECTION(%ux%u@%u:%u)\n", rect->width, rect->height,
		rect->left, rect->top);

	/* During camera cropping its output window can change too, stop CEU */
	capsr = capture_save_reset(pcdev);
	dev_dbg(dev, "CAPSR 0x%x, CFLCR 0x%x\n", capsr, pcdev->cflcr);

	/*
	 * 1. - 2. Apply iterative camera S_SELECTION for new input window, read back
	 * actual camera rectangle.
	 */
	ret = soc_camera_client_s_selection(sd, sel, &cam_sel,
				       &cam->rect, &cam->subrect);
	if (ret < 0)
		return ret;

	dev_geo(dev, "1-2: camera cropped to %ux%u@%u:%u\n",
		cam_rect->width, cam_rect->height,
		cam_rect->left, cam_rect->top);

	/* On success cam_crop contains current camera crop */

	/* 3. Retrieve camera output window */
	ret = v4l2_subdev_call(sd, pad, get_fmt, NULL, &fmt);
	if (ret < 0)
		return ret;

	if (mf->width > pcdev->max_width || mf->height > pcdev->max_height)
		return -EINVAL;

	/* 4. Calculate camera scales */
	scale_cam_h	= calc_generic_scale(cam_rect->width, mf->width);
	scale_cam_v	= calc_generic_scale(cam_rect->height, mf->height);

	/* Calculate intermediate window */
	interm_width	= scale_down(rect->width, scale_cam_h);
	interm_height	= scale_down(rect->height, scale_cam_v);

	if (interm_width < icd->user_width) {
		u32 new_scale_h;

		new_scale_h = calc_generic_scale(rect->width, icd->user_width);

		mf->width = scale_down(cam_rect->width, new_scale_h);
	}

	if (interm_height < icd->user_height) {
		u32 new_scale_v;

		new_scale_v = calc_generic_scale(rect->height, icd->user_height);

		mf->height = scale_down(cam_rect->height, new_scale_v);
	}

	if (interm_width < icd->user_width || interm_height < icd->user_height) {
		ret = v4l2_device_call_until_err(sd->v4l2_dev,
					soc_camera_grp_id(icd), pad,
					set_fmt, NULL, &fmt);
		if (ret < 0)
			return ret;

		dev_geo(dev, "New camera output %ux%u\n", mf->width, mf->height);
		scale_cam_h	= calc_generic_scale(cam_rect->width, mf->width);
		scale_cam_v	= calc_generic_scale(cam_rect->height, mf->height);
		interm_width	= scale_down(rect->width, scale_cam_h);
		interm_height	= scale_down(rect->height, scale_cam_v);
	}

	/* Cache camera output window */
	cam->width	= mf->width;
	cam->height	= mf->height;

	if (pcdev->image_mode) {
		out_width	= min(interm_width, icd->user_width);
		out_height	= min(interm_height, icd->user_height);
	} else {
		out_width	= interm_width;
		out_height	= interm_height;
	}

	/*
	 * 5. Calculate CEU scales from camera scales from results of (5) and
	 *    the user window
	 */
	scale_ceu_h	= calc_scale(interm_width, &out_width);
	scale_ceu_v	= calc_scale(interm_height, &out_height);

	dev_geo(dev, "5: CEU scales %u:%u\n", scale_ceu_h, scale_ceu_v);

	/* Apply CEU scales. */
	cflcr = scale_ceu_h | (scale_ceu_v << 16);
	if (cflcr != pcdev->cflcr) {
		pcdev->cflcr = cflcr;
		ceu_write(pcdev, CFLCR, cflcr);
	}

	icd->user_width	 = out_width & ~3;
	icd->user_height = out_height & ~3;
	/* Offsets are applied at the CEU scaling filter input */
	cam->ceu_left	 = scale_down(rect->left - cam_rect->left, scale_cam_h) & ~1;
	cam->ceu_top	 = scale_down(rect->top - cam_rect->top, scale_cam_v) & ~1;

	/* 6. Use CEU cropping to crop to the new window. */
	sh_mobile_ceu_set_rect(icd);

	cam->subrect = *rect;

	dev_geo(dev, "6: CEU cropped to %ux%u@%u:%u\n",
		icd->user_width, icd->user_height,
		cam->ceu_left, cam->ceu_top);

	/* Restore capture. The CE bit can be cleared by the hardware */
	if (pcdev->active)
		capsr |= 1;
	capture_restore(pcdev, capsr);

	/* Even if only camera cropping succeeded */
	return ret;
}