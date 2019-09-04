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
struct v4l2_subdev_mbus_code_enum {int code; int /*<<< orphan*/  index; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int dummy; } ;
struct ceu_mbus_fmt {int mbus_code; int bps; int swapped; int bpp; void* fmt_order_swap; void* fmt_order; } ;
struct ceu_subdev {struct v4l2_subdev* v4l2_sd; struct ceu_mbus_fmt mbus_fmt; } ;
struct ceu_device {struct ceu_subdev* sd; } ;

/* Variables and functions */
 void* CEU_CAMCR_DTARY_8_UYVY ; 
 void* CEU_CAMCR_DTARY_8_VYUY ; 
 void* CEU_CAMCR_DTARY_8_YUYV ; 
 void* CEU_CAMCR_DTARY_8_YVYU ; 
 int ENXIO ; 
#define  MEDIA_BUS_FMT_UYVY8_2X8 131 
#define  MEDIA_BUS_FMT_VYUY8_2X8 130 
#define  MEDIA_BUS_FMT_YUYV8_2X8 129 
#define  MEDIA_BUS_FMT_YVYU8_2X8 128 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  enum_mbus_code ; 
 int /*<<< orphan*/  pad ; 
 int /*<<< orphan*/  v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_mbus_code_enum*) ; 

__attribute__((used)) static int ceu_init_mbus_fmt(struct ceu_device *ceudev)
{
	struct ceu_subdev *ceu_sd = ceudev->sd;
	struct ceu_mbus_fmt *mbus_fmt = &ceu_sd->mbus_fmt;
	struct v4l2_subdev *v4l2_sd = ceu_sd->v4l2_sd;
	bool yuyv_bus_fmt = false;

	struct v4l2_subdev_mbus_code_enum sd_mbus_fmt = {
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		.index = 0,
	};

	/* Find out if sensor can produce any permutation of 8-bits YUYV422. */
	while (!yuyv_bus_fmt &&
	       !v4l2_subdev_call(v4l2_sd, pad, enum_mbus_code,
				 NULL, &sd_mbus_fmt)) {
		switch (sd_mbus_fmt.code) {
		case MEDIA_BUS_FMT_YUYV8_2X8:
		case MEDIA_BUS_FMT_YVYU8_2X8:
		case MEDIA_BUS_FMT_UYVY8_2X8:
		case MEDIA_BUS_FMT_VYUY8_2X8:
			yuyv_bus_fmt = true;
			break;
		default:
			/*
			 * Only support 8-bits YUYV bus formats at the moment;
			 *
			 * TODO: add support for binary formats (data sync
			 * fetch mode).
			 */
			break;
		}

		sd_mbus_fmt.index++;
	}

	if (!yuyv_bus_fmt)
		return -ENXIO;

	/*
	 * Save the first encountered YUYV format as "mbus_fmt" and use it
	 * to output all planar YUV422 and YUV420 (NV*) formats to memory as
	 * well as for data synch fetch mode (YUYV - YVYU etc. ).
	 */
	mbus_fmt->mbus_code	= sd_mbus_fmt.code;
	mbus_fmt->bps		= 8;

	/* Annotate the selected bus format components ordering. */
	switch (sd_mbus_fmt.code) {
	case MEDIA_BUS_FMT_YUYV8_2X8:
		mbus_fmt->fmt_order		= CEU_CAMCR_DTARY_8_YUYV;
		mbus_fmt->fmt_order_swap	= CEU_CAMCR_DTARY_8_YVYU;
		mbus_fmt->swapped		= false;
		mbus_fmt->bpp			= 16;
		break;

	case MEDIA_BUS_FMT_YVYU8_2X8:
		mbus_fmt->fmt_order		= CEU_CAMCR_DTARY_8_YVYU;
		mbus_fmt->fmt_order_swap	= CEU_CAMCR_DTARY_8_YUYV;
		mbus_fmt->swapped		= true;
		mbus_fmt->bpp			= 16;
		break;

	case MEDIA_BUS_FMT_UYVY8_2X8:
		mbus_fmt->fmt_order		= CEU_CAMCR_DTARY_8_UYVY;
		mbus_fmt->fmt_order_swap	= CEU_CAMCR_DTARY_8_VYUY;
		mbus_fmt->swapped		= false;
		mbus_fmt->bpp			= 16;
		break;

	case MEDIA_BUS_FMT_VYUY8_2X8:
		mbus_fmt->fmt_order		= CEU_CAMCR_DTARY_8_VYUY;
		mbus_fmt->fmt_order_swap	= CEU_CAMCR_DTARY_8_UYVY;
		mbus_fmt->swapped		= true;
		mbus_fmt->bpp			= 16;
		break;
	}

	return 0;
}