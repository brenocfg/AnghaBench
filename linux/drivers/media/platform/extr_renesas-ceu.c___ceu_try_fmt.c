#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct TYPE_7__ {void* code; } ;
struct v4l2_subdev_format {TYPE_3__ format; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_pix_format_mplane {int pixelformat; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_5__ {struct v4l2_pix_format_mplane pix_mp; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct TYPE_6__ {void* mbus_code; } ;
struct ceu_subdev {TYPE_2__ mbus_fmt; struct v4l2_subdev* v4l2_sd; } ;
struct ceu_fmt {int dummy; } ;
struct ceu_device {struct ceu_subdev* sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEU_MAX_HEIGHT ; 
 int /*<<< orphan*/  CEU_MAX_WIDTH ; 
 int EINVAL ; 
 void* MEDIA_BUS_FMT_UYVY8_2X8 ; 
 void* MEDIA_BUS_FMT_VYUY8_2X8 ; 
 void* MEDIA_BUS_FMT_YUYV8_2X8 ; 
 void* MEDIA_BUS_FMT_YVYU8_2X8 ; 
#define  V4L2_PIX_FMT_NV12 135 
#define  V4L2_PIX_FMT_NV16 134 
#define  V4L2_PIX_FMT_NV21 133 
#define  V4L2_PIX_FMT_NV61 132 
#define  V4L2_PIX_FMT_UYVY 131 
#define  V4L2_PIX_FMT_VYUY 130 
#define  V4L2_PIX_FMT_YUYV 129 
#define  V4L2_PIX_FMT_YVYU 128 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_TRY ; 
 int /*<<< orphan*/  ceu_calc_plane_sizes (struct ceu_device*,struct ceu_fmt const*,struct v4l2_pix_format_mplane*) ; 
 struct ceu_fmt* get_ceu_fmt_from_fourcc (int) ; 
 int /*<<< orphan*/  pad ; 
 int /*<<< orphan*/  set_fmt ; 
 int /*<<< orphan*/  v4l2_fill_mbus_format_mplane (TYPE_3__*,struct v4l2_pix_format_mplane*) ; 
 int /*<<< orphan*/  v4l2_fill_pix_format_mplane (struct v4l2_pix_format_mplane*,TYPE_3__*) ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_subdev_pad_config*,struct v4l2_subdev_format*) ; 
 int /*<<< orphan*/  v4l_bound_align_image (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __ceu_try_fmt(struct ceu_device *ceudev, struct v4l2_format *v4l2_fmt,
			 u32 *sd_mbus_code)
{
	struct ceu_subdev *ceu_sd = ceudev->sd;
	struct v4l2_pix_format_mplane *pix = &v4l2_fmt->fmt.pix_mp;
	struct v4l2_subdev *v4l2_sd = ceu_sd->v4l2_sd;
	struct v4l2_subdev_pad_config pad_cfg;
	const struct ceu_fmt *ceu_fmt;
	u32 mbus_code_old;
	u32 mbus_code;
	int ret;

	/*
	 * Set format on sensor sub device: bus format used to produce memory
	 * format is selected depending on YUV component ordering or
	 * at initialization time.
	 */
	struct v4l2_subdev_format sd_format = {
		.which	= V4L2_SUBDEV_FORMAT_TRY,
	};

	mbus_code_old = ceu_sd->mbus_fmt.mbus_code;

	switch (pix->pixelformat) {
	case V4L2_PIX_FMT_YUYV:
		mbus_code = MEDIA_BUS_FMT_YUYV8_2X8;
		break;
	case V4L2_PIX_FMT_UYVY:
		mbus_code = MEDIA_BUS_FMT_UYVY8_2X8;
		break;
	case V4L2_PIX_FMT_YVYU:
		mbus_code = MEDIA_BUS_FMT_YVYU8_2X8;
		break;
	case V4L2_PIX_FMT_VYUY:
		mbus_code = MEDIA_BUS_FMT_VYUY8_2X8;
		break;
	case V4L2_PIX_FMT_NV16:
	case V4L2_PIX_FMT_NV61:
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV21:
		mbus_code = ceu_sd->mbus_fmt.mbus_code;
		break;

	default:
		pix->pixelformat = V4L2_PIX_FMT_NV16;
		mbus_code = ceu_sd->mbus_fmt.mbus_code;
		break;
	}

	ceu_fmt = get_ceu_fmt_from_fourcc(pix->pixelformat);

	/* CFSZR requires height and width to be 4-pixel aligned. */
	v4l_bound_align_image(&pix->width, 2, CEU_MAX_WIDTH, 4,
			      &pix->height, 4, CEU_MAX_HEIGHT, 4, 0);

	v4l2_fill_mbus_format_mplane(&sd_format.format, pix);

	/*
	 * Try with the mbus_code matching YUYV components ordering first,
	 * if that one fails, fallback to default selected at initialization
	 * time.
	 */
	sd_format.format.code = mbus_code;
	ret = v4l2_subdev_call(v4l2_sd, pad, set_fmt, &pad_cfg, &sd_format);
	if (ret) {
		if (ret == -EINVAL) {
			/* fallback */
			sd_format.format.code = mbus_code_old;
			ret = v4l2_subdev_call(v4l2_sd, pad, set_fmt,
					       &pad_cfg, &sd_format);
		}

		if (ret)
			return ret;
	}

	/* Apply size returned by sensor as the CEU can't scale. */
	v4l2_fill_pix_format_mplane(pix, &sd_format.format);

	/* Calculate per-plane sizes based on image format. */
	ceu_calc_plane_sizes(ceudev, ceu_fmt, pix);

	/* Report to caller the configured mbus format. */
	*sd_mbus_code = sd_format.format.code;

	return 0;
}