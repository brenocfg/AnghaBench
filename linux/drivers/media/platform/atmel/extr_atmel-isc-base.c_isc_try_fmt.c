#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_format {int /*<<< orphan*/  format; int /*<<< orphan*/  which; } ;
struct v4l2_pix_format {int width; int height; int bytesperline; int sizeimage; int /*<<< orphan*/  field; scalar_t__ pixelformat; } ;
struct TYPE_4__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {scalar_t__ type; TYPE_1__ fmt; } ;
struct isc_format {scalar_t__ fourcc; int /*<<< orphan*/  mbus_code; } ;
struct TYPE_6__ {int bpp; scalar_t__ fourcc; struct isc_format* sd_format; } ;
struct isc_device {int num_user_formats; TYPE_3__ try_config; int /*<<< orphan*/  v4l2_dev; TYPE_2__* current_subdev; struct isc_format** user_formats; } ;
struct TYPE_5__ {int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ISC_IS_FORMAT_RAW (int /*<<< orphan*/ ) ; 
 int ISC_MAX_SUPPORT_HEIGHT ; 
 int ISC_MAX_SUPPORT_WIDTH ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_TRY ; 
 int /*<<< orphan*/  debug ; 
 struct isc_format* find_format_by_fourcc (struct isc_device*,scalar_t__) ; 
 int isc_try_configure_pipeline (struct isc_device*) ; 
 int isc_try_configure_rlp_dma (struct isc_device*,int) ; 
 int isc_try_validate_formats (struct isc_device*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pad ; 
 scalar_t__ sensor_preferred ; 
 int /*<<< orphan*/  set_fmt ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,...) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_fill_mbus_format (int /*<<< orphan*/ *,struct v4l2_pix_format*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_fill_pix_format (struct v4l2_pix_format*,int /*<<< orphan*/ *) ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_subdev_pad_config*,struct v4l2_subdev_format*) ; 

__attribute__((used)) static int isc_try_fmt(struct isc_device *isc, struct v4l2_format *f,
			u32 *code)
{
	int i;
	struct isc_format *sd_fmt = NULL, *direct_fmt = NULL;
	struct v4l2_pix_format *pixfmt = &f->fmt.pix;
	struct v4l2_subdev_pad_config pad_cfg;
	struct v4l2_subdev_format format = {
		.which = V4L2_SUBDEV_FORMAT_TRY,
	};
	u32 mbus_code;
	int ret;
	bool rlp_dma_direct_dump = false;

	if (f->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	/* Step 1: find a RAW format that is supported */
	for (i = 0; i < isc->num_user_formats; i++) {
		if (ISC_IS_FORMAT_RAW(isc->user_formats[i]->mbus_code)) {
			sd_fmt = isc->user_formats[i];
			break;
		}
	}
	/* Step 2: We can continue with this RAW format, or we can look
	 * for better: maybe sensor supports directly what we need.
	 */
	direct_fmt = find_format_by_fourcc(isc, pixfmt->pixelformat);

	/* Step 3: We have both. We decide given the module parameter which
	 * one to use.
	 */
	if (direct_fmt && sd_fmt && sensor_preferred)
		sd_fmt = direct_fmt;

	/* Step 4: we do not have RAW but we have a direct format. Use it. */
	if (direct_fmt && !sd_fmt)
		sd_fmt = direct_fmt;

	/* Step 5: if we are using a direct format, we need to package
	 * everything as 8 bit data and just dump it
	 */
	if (sd_fmt == direct_fmt)
		rlp_dma_direct_dump = true;

	/* Step 6: We have no format. This can happen if the userspace
	 * requests some weird/invalid format.
	 * In this case, default to whatever we have
	 */
	if (!sd_fmt && !direct_fmt) {
		sd_fmt = isc->user_formats[isc->num_user_formats - 1];
		v4l2_dbg(1, debug, &isc->v4l2_dev,
			 "Sensor not supporting %.4s, using %.4s\n",
			 (char *)&pixfmt->pixelformat, (char *)&sd_fmt->fourcc);
	}

	if (!sd_fmt) {
		ret = -EINVAL;
		goto isc_try_fmt_err;
	}

	/* Step 7: Print out what we decided for debugging */
	v4l2_dbg(1, debug, &isc->v4l2_dev,
		 "Preferring to have sensor using format %.4s\n",
		 (char *)&sd_fmt->fourcc);

	/* Step 8: at this moment we decided which format the subdev will use */
	isc->try_config.sd_format = sd_fmt;

	/* Limit to Atmel ISC hardware capabilities */
	if (pixfmt->width > ISC_MAX_SUPPORT_WIDTH)
		pixfmt->width = ISC_MAX_SUPPORT_WIDTH;
	if (pixfmt->height > ISC_MAX_SUPPORT_HEIGHT)
		pixfmt->height = ISC_MAX_SUPPORT_HEIGHT;

	/*
	 * The mbus format is the one the subdev outputs.
	 * The pixels will be transferred in this format Sensor -> ISC
	 */
	mbus_code = sd_fmt->mbus_code;

	/*
	 * Validate formats. If the required format is not OK, default to raw.
	 */

	isc->try_config.fourcc = pixfmt->pixelformat;

	if (isc_try_validate_formats(isc)) {
		pixfmt->pixelformat = isc->try_config.fourcc = sd_fmt->fourcc;
		/* Re-try to validate the new format */
		ret = isc_try_validate_formats(isc);
		if (ret)
			goto isc_try_fmt_err;
	}

	ret = isc_try_configure_rlp_dma(isc, rlp_dma_direct_dump);
	if (ret)
		goto isc_try_fmt_err;

	ret = isc_try_configure_pipeline(isc);
	if (ret)
		goto isc_try_fmt_err;

	v4l2_fill_mbus_format(&format.format, pixfmt, mbus_code);
	ret = v4l2_subdev_call(isc->current_subdev->sd, pad, set_fmt,
			       &pad_cfg, &format);
	if (ret < 0)
		goto isc_try_fmt_subdev_err;

	v4l2_fill_pix_format(pixfmt, &format.format);

	pixfmt->field = V4L2_FIELD_NONE;
	pixfmt->bytesperline = (pixfmt->width * isc->try_config.bpp) >> 3;
	pixfmt->sizeimage = pixfmt->bytesperline * pixfmt->height;

	if (code)
		*code = mbus_code;

	return 0;

isc_try_fmt_err:
	v4l2_err(&isc->v4l2_dev, "Could not find any possible format for a working pipeline\n");
isc_try_fmt_subdev_err:
	memset(&isc->try_config, 0, sizeof(isc->try_config));

	return ret;
}