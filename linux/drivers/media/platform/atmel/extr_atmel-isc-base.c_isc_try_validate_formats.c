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
struct TYPE_4__ {int fourcc; TYPE_1__* sd_format; } ;
struct isc_device {int /*<<< orphan*/  v4l2_dev; TYPE_2__ try_config; } ;
struct TYPE_3__ {int /*<<< orphan*/  mbus_code; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ISC_IS_FORMAT_RAW (int /*<<< orphan*/ ) ; 
#define  V4L2_PIX_FMT_ABGR32 148 
#define  V4L2_PIX_FMT_ARGB444 147 
#define  V4L2_PIX_FMT_ARGB555 146 
#define  V4L2_PIX_FMT_GREY 145 
#define  V4L2_PIX_FMT_RGB565 144 
#define  V4L2_PIX_FMT_SBGGR10 143 
#define  V4L2_PIX_FMT_SBGGR12 142 
#define  V4L2_PIX_FMT_SBGGR8 141 
#define  V4L2_PIX_FMT_SGBRG10 140 
#define  V4L2_PIX_FMT_SGBRG12 139 
#define  V4L2_PIX_FMT_SGBRG8 138 
#define  V4L2_PIX_FMT_SGRBG10 137 
#define  V4L2_PIX_FMT_SGRBG12 136 
#define  V4L2_PIX_FMT_SGRBG8 135 
#define  V4L2_PIX_FMT_SRGGB10 134 
#define  V4L2_PIX_FMT_SRGGB12 133 
#define  V4L2_PIX_FMT_SRGGB8 132 
#define  V4L2_PIX_FMT_XBGR32 131 
#define  V4L2_PIX_FMT_YUV420 130 
#define  V4L2_PIX_FMT_YUV422P 129 
#define  V4L2_PIX_FMT_YUYV 128 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int,int,int,int) ; 

__attribute__((used)) static int isc_try_validate_formats(struct isc_device *isc)
{
	int ret;
	bool bayer = false, yuv = false, rgb = false, grey = false;

	/* all formats supported by the RLP module are OK */
	switch (isc->try_config.fourcc) {
	case V4L2_PIX_FMT_SBGGR8:
	case V4L2_PIX_FMT_SGBRG8:
	case V4L2_PIX_FMT_SGRBG8:
	case V4L2_PIX_FMT_SRGGB8:
	case V4L2_PIX_FMT_SBGGR10:
	case V4L2_PIX_FMT_SGBRG10:
	case V4L2_PIX_FMT_SGRBG10:
	case V4L2_PIX_FMT_SRGGB10:
	case V4L2_PIX_FMT_SBGGR12:
	case V4L2_PIX_FMT_SGBRG12:
	case V4L2_PIX_FMT_SGRBG12:
	case V4L2_PIX_FMT_SRGGB12:
		ret = 0;
		bayer = true;
		break;

	case V4L2_PIX_FMT_YUV420:
	case V4L2_PIX_FMT_YUV422P:
	case V4L2_PIX_FMT_YUYV:
		ret = 0;
		yuv = true;
		break;

	case V4L2_PIX_FMT_RGB565:
	case V4L2_PIX_FMT_ABGR32:
	case V4L2_PIX_FMT_XBGR32:
	case V4L2_PIX_FMT_ARGB444:
	case V4L2_PIX_FMT_ARGB555:
		ret = 0;
		rgb = true;
		break;
	case V4L2_PIX_FMT_GREY:
		ret = 0;
		grey = true;
		break;
	default:
	/* any other different formats are not supported */
		ret = -EINVAL;
	}

	/* we cannot output RAW/Grey if we do not receive RAW */
	if ((bayer || grey) &&
	    !ISC_IS_FORMAT_RAW(isc->try_config.sd_format->mbus_code))
		return -EINVAL;

	v4l2_dbg(1, debug, &isc->v4l2_dev,
		 "Format validation, requested rgb=%u, yuv=%u, grey=%u, bayer=%u\n",
		 rgb, yuv, grey, bayer);

	return ret;
}