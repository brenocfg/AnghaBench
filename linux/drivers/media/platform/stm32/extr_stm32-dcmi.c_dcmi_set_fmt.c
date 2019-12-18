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
struct v4l2_mbus_framefmt {char* code; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_subdev_format {struct v4l2_mbus_framefmt format; int /*<<< orphan*/  which; } ;
struct v4l2_pix_format {scalar_t__ pixelformat; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_2__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct dcmi_framesize {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct stm32_dcmi {int do_crop; struct dcmi_framesize sd_framesize; struct dcmi_format const* sd_format; struct v4l2_format fmt; int /*<<< orphan*/  dev; } ;
struct dcmi_format {int /*<<< orphan*/  mbus_code; } ;

/* Variables and functions */
 scalar_t__ V4L2_PIX_FMT_JPEG ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int dcmi_pipeline_s_fmt (struct stm32_dcmi*,int /*<<< orphan*/ *,struct v4l2_subdev_format*) ; 
 int dcmi_try_fmt (struct stm32_dcmi*,struct v4l2_format*,struct dcmi_format const**,struct dcmi_framesize*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_fill_mbus_format (struct v4l2_mbus_framefmt*,struct v4l2_pix_format*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dcmi_set_fmt(struct stm32_dcmi *dcmi, struct v4l2_format *f)
{
	struct v4l2_subdev_format format = {
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	};
	const struct dcmi_format *sd_format;
	struct dcmi_framesize sd_framesize;
	struct v4l2_mbus_framefmt *mf = &format.format;
	struct v4l2_pix_format *pix = &f->fmt.pix;
	int ret;

	/*
	 * Try format, fmt.width/height could have been changed
	 * to match sensor capability or crop request
	 * sd_format & sd_framesize will contain what subdev
	 * can do for this request.
	 */
	ret = dcmi_try_fmt(dcmi, f, &sd_format, &sd_framesize);
	if (ret)
		return ret;

	/* Disable crop if JPEG is requested */
	if (pix->pixelformat == V4L2_PIX_FMT_JPEG)
		dcmi->do_crop = false;

	/* pix to mbus format */
	v4l2_fill_mbus_format(mf, pix,
			      sd_format->mbus_code);
	mf->width = sd_framesize.width;
	mf->height = sd_framesize.height;

	ret = dcmi_pipeline_s_fmt(dcmi, NULL, &format);
	if (ret < 0)
		return ret;

	dev_dbg(dcmi->dev, "Sensor format set to 0x%x %ux%u\n",
		mf->code, mf->width, mf->height);
	dev_dbg(dcmi->dev, "Buffer format set to %4.4s %ux%u\n",
		(char *)&pix->pixelformat,
		pix->width, pix->height);

	dcmi->fmt = *f;
	dcmi->sd_format = sd_format;
	dcmi->sd_framesize = sd_framesize;

	return 0;
}