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
typedef  int u16 ;
struct v4l2_pix_format {int pixelformat; int field; unsigned int width; unsigned int height; int /*<<< orphan*/  colorspace; } ;
struct v4l2_mbus_framefmt {int field; scalar_t__ code; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_2__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct soc_camera_host {struct sh_mobile_ceu_dev* priv; } ;
struct soc_camera_format_xlate {scalar_t__ code; } ;
struct soc_camera_device {struct soc_camera_format_xlate const* current_fmt; struct sh_mobile_ceu_cam* host_priv; struct device* parent; } ;
struct sh_mobile_ceu_dev {unsigned int max_width; unsigned int max_height; int cflcr; int field; int image_mode; } ;
struct sh_mobile_ceu_cam {scalar_t__ code; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  subrect; int /*<<< orphan*/  rect; } ;
struct device {int dummy; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;
typedef  int __u32 ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_FIELD_INTERLACED 135 
#define  V4L2_FIELD_INTERLACED_BT 134 
#define  V4L2_FIELD_INTERLACED_TB 133 
#define  V4L2_FIELD_NONE 132 
#define  V4L2_PIX_FMT_NV12 131 
#define  V4L2_PIX_FMT_NV16 130 
#define  V4L2_PIX_FMT_NV21 129 
#define  V4L2_PIX_FMT_NV61 128 
 int calc_scale (unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  dev_geo (struct device*,char*,unsigned int,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 int /*<<< orphan*/  soc_camera_calc_client_output (struct soc_camera_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct v4l2_pix_format*,struct v4l2_mbus_framefmt*,int) ; 
 int soc_camera_client_scale (struct soc_camera_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct v4l2_mbus_framefmt*,unsigned int*,unsigned int*,int,int) ; 
 struct soc_camera_format_xlate* soc_camera_xlate_by_fourcc (struct soc_camera_device*,int) ; 
 struct soc_camera_host* to_soc_camera_host (struct device*) ; 

__attribute__((used)) static int sh_mobile_ceu_set_fmt(struct soc_camera_device *icd,
				 struct v4l2_format *f)
{
	struct device *dev = icd->parent;
	struct soc_camera_host *ici = to_soc_camera_host(dev);
	struct sh_mobile_ceu_dev *pcdev = ici->priv;
	struct sh_mobile_ceu_cam *cam = icd->host_priv;
	struct v4l2_pix_format *pix = &f->fmt.pix;
	struct v4l2_mbus_framefmt mf;
	__u32 pixfmt = pix->pixelformat;
	const struct soc_camera_format_xlate *xlate;
	unsigned int ceu_sub_width = pcdev->max_width,
		ceu_sub_height = pcdev->max_height;
	u16 scale_v, scale_h;
	int ret;
	bool image_mode;
	enum v4l2_field field;

	switch (pix->field) {
	default:
		pix->field = V4L2_FIELD_NONE;
		/* fall-through */
	case V4L2_FIELD_INTERLACED_TB:
	case V4L2_FIELD_INTERLACED_BT:
	case V4L2_FIELD_NONE:
		field = pix->field;
		break;
	case V4L2_FIELD_INTERLACED:
		field = V4L2_FIELD_INTERLACED_TB;
		break;
	}

	xlate = soc_camera_xlate_by_fourcc(icd, pixfmt);
	if (!xlate) {
		dev_warn(dev, "Format %x not found\n", pixfmt);
		return -EINVAL;
	}

	/* 1.-4. Calculate desired client output geometry */
	soc_camera_calc_client_output(icd, &cam->rect, &cam->subrect, pix, &mf, 12);
	mf.field	= pix->field;
	mf.colorspace	= pix->colorspace;
	mf.code		= xlate->code;

	switch (pixfmt) {
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV21:
	case V4L2_PIX_FMT_NV16:
	case V4L2_PIX_FMT_NV61:
		image_mode = true;
		break;
	default:
		image_mode = false;
	}

	dev_geo(dev, "S_FMT(pix=0x%x, fld 0x%x, code 0x%x, %ux%u)\n", pixfmt, mf.field, mf.code,
		pix->width, pix->height);

	dev_geo(dev, "4: request camera output %ux%u\n", mf.width, mf.height);

	/* 5. - 9. */
	ret = soc_camera_client_scale(icd, &cam->rect, &cam->subrect,
				&mf, &ceu_sub_width, &ceu_sub_height,
				image_mode && V4L2_FIELD_NONE == field, 12);

	dev_geo(dev, "5-9: client scale return %d\n", ret);

	/* Done with the camera. Now see if we can improve the result */

	dev_geo(dev, "fmt %ux%u, requested %ux%u\n",
		mf.width, mf.height, pix->width, pix->height);
	if (ret < 0)
		return ret;

	if (mf.code != xlate->code)
		return -EINVAL;

	/* 9. Prepare CEU crop */
	cam->width = mf.width;
	cam->height = mf.height;

	/* 10. Use CEU scaling to scale to the requested user window. */

	/* We cannot scale up */
	if (pix->width > ceu_sub_width)
		ceu_sub_width = pix->width;

	if (pix->height > ceu_sub_height)
		ceu_sub_height = pix->height;

	pix->colorspace = mf.colorspace;

	if (image_mode) {
		/* Scale pix->{width x height} down to width x height */
		scale_h		= calc_scale(ceu_sub_width, &pix->width);
		scale_v		= calc_scale(ceu_sub_height, &pix->height);
	} else {
		pix->width	= ceu_sub_width;
		pix->height	= ceu_sub_height;
		scale_h		= 0;
		scale_v		= 0;
	}

	pcdev->cflcr = scale_h | (scale_v << 16);

	/*
	 * We have calculated CFLCR, the actual configuration will be performed
	 * in sh_mobile_ceu_set_bus_param()
	 */

	dev_geo(dev, "10: W: %u : 0x%x = %u, H: %u : 0x%x = %u\n",
		ceu_sub_width, scale_h, pix->width,
		ceu_sub_height, scale_v, pix->height);

	cam->code		= xlate->code;
	icd->current_fmt	= xlate;

	pcdev->field = field;
	pcdev->image_mode = image_mode;

	/* CFSZR requirement */
	pix->width	&= ~3;
	pix->height	&= ~3;

	return 0;
}