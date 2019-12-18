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
typedef  int u32 ;
struct TYPE_5__ {int bus_width; } ;
struct TYPE_6__ {TYPE_1__ parallel; } ;
struct TYPE_7__ {scalar_t__ bus_type; TYPE_2__ bus; } ;
struct TYPE_8__ {TYPE_3__ v4l2_ep; } ;
struct sun6i_csi_dev {int /*<<< orphan*/  dev; TYPE_4__ csi; } ;
struct sun6i_csi {int dummy; } ;

/* Variables and functions */
 int MEDIA_BUS_FMT_JPEG_1X8 ; 
 int MEDIA_BUS_FMT_RGB565_2X8_BE ; 
 int MEDIA_BUS_FMT_RGB565_2X8_LE ; 
 int MEDIA_BUS_FMT_SBGGR10_1X10 ; 
 int MEDIA_BUS_FMT_SBGGR12_1X12 ; 
 int MEDIA_BUS_FMT_SBGGR8_1X8 ; 
 int MEDIA_BUS_FMT_SGBRG10_1X10 ; 
 int MEDIA_BUS_FMT_SGBRG12_1X12 ; 
 int MEDIA_BUS_FMT_SGBRG8_1X8 ; 
 int MEDIA_BUS_FMT_SGRBG10_1X10 ; 
 int MEDIA_BUS_FMT_SGRBG12_1X12 ; 
 int MEDIA_BUS_FMT_SGRBG8_1X8 ; 
 int MEDIA_BUS_FMT_SRGGB10_1X10 ; 
 int MEDIA_BUS_FMT_SRGGB12_1X12 ; 
 int MEDIA_BUS_FMT_SRGGB8_1X8 ; 
#define  MEDIA_BUS_FMT_UYVY8_1X16 162 
#define  MEDIA_BUS_FMT_UYVY8_2X8 161 
#define  MEDIA_BUS_FMT_VYUY8_1X16 160 
#define  MEDIA_BUS_FMT_VYUY8_2X8 159 
#define  MEDIA_BUS_FMT_YUYV8_1X16 158 
#define  MEDIA_BUS_FMT_YUYV8_2X8 157 
#define  MEDIA_BUS_FMT_YVYU8_1X16 156 
#define  MEDIA_BUS_FMT_YVYU8_2X8 155 
 scalar_t__ V4L2_MBUS_BT656 ; 
 scalar_t__ V4L2_MBUS_PARALLEL ; 
#define  V4L2_PIX_FMT_HM12 154 
#define  V4L2_PIX_FMT_JPEG 153 
#define  V4L2_PIX_FMT_NV12 152 
#define  V4L2_PIX_FMT_NV16 151 
#define  V4L2_PIX_FMT_NV21 150 
#define  V4L2_PIX_FMT_NV61 149 
#define  V4L2_PIX_FMT_RGB565 148 
#define  V4L2_PIX_FMT_RGB565X 147 
#define  V4L2_PIX_FMT_SBGGR10 146 
#define  V4L2_PIX_FMT_SBGGR12 145 
#define  V4L2_PIX_FMT_SBGGR8 144 
#define  V4L2_PIX_FMT_SGBRG10 143 
#define  V4L2_PIX_FMT_SGBRG12 142 
#define  V4L2_PIX_FMT_SGBRG8 141 
#define  V4L2_PIX_FMT_SGRBG10 140 
#define  V4L2_PIX_FMT_SGRBG12 139 
#define  V4L2_PIX_FMT_SGRBG8 138 
#define  V4L2_PIX_FMT_SRGGB10 137 
#define  V4L2_PIX_FMT_SRGGB12 136 
#define  V4L2_PIX_FMT_SRGGB8 135 
#define  V4L2_PIX_FMT_UYVY 134 
#define  V4L2_PIX_FMT_VYUY 133 
#define  V4L2_PIX_FMT_YUV420 132 
#define  V4L2_PIX_FMT_YUV422P 131 
#define  V4L2_PIX_FMT_YUYV 130 
#define  V4L2_PIX_FMT_YVU420 129 
#define  V4L2_PIX_FMT_YVYU 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 struct sun6i_csi_dev* sun6i_csi_to_dev (struct sun6i_csi*) ; 

bool sun6i_csi_is_format_supported(struct sun6i_csi *csi,
				   u32 pixformat, u32 mbus_code)
{
	struct sun6i_csi_dev *sdev = sun6i_csi_to_dev(csi);

	/*
	 * Some video receivers have the ability to be compatible with
	 * 8bit and 16bit bus width.
	 * Identify the media bus format from device tree.
	 */
	if ((sdev->csi.v4l2_ep.bus_type == V4L2_MBUS_PARALLEL
	     || sdev->csi.v4l2_ep.bus_type == V4L2_MBUS_BT656)
	     && sdev->csi.v4l2_ep.bus.parallel.bus_width == 16) {
		switch (pixformat) {
		case V4L2_PIX_FMT_HM12:
		case V4L2_PIX_FMT_NV12:
		case V4L2_PIX_FMT_NV21:
		case V4L2_PIX_FMT_NV16:
		case V4L2_PIX_FMT_NV61:
		case V4L2_PIX_FMT_YUV420:
		case V4L2_PIX_FMT_YVU420:
		case V4L2_PIX_FMT_YUV422P:
			switch (mbus_code) {
			case MEDIA_BUS_FMT_UYVY8_1X16:
			case MEDIA_BUS_FMT_VYUY8_1X16:
			case MEDIA_BUS_FMT_YUYV8_1X16:
			case MEDIA_BUS_FMT_YVYU8_1X16:
				return true;
			default:
				dev_dbg(sdev->dev, "Unsupported mbus code: 0x%x\n",
					mbus_code);
				break;
			}
			break;
		default:
			dev_dbg(sdev->dev, "Unsupported pixformat: 0x%x\n",
				pixformat);
			break;
		}
		return false;
	}

	switch (pixformat) {
	case V4L2_PIX_FMT_SBGGR8:
		return (mbus_code == MEDIA_BUS_FMT_SBGGR8_1X8);
	case V4L2_PIX_FMT_SGBRG8:
		return (mbus_code == MEDIA_BUS_FMT_SGBRG8_1X8);
	case V4L2_PIX_FMT_SGRBG8:
		return (mbus_code == MEDIA_BUS_FMT_SGRBG8_1X8);
	case V4L2_PIX_FMT_SRGGB8:
		return (mbus_code == MEDIA_BUS_FMT_SRGGB8_1X8);
	case V4L2_PIX_FMT_SBGGR10:
		return (mbus_code == MEDIA_BUS_FMT_SBGGR10_1X10);
	case V4L2_PIX_FMT_SGBRG10:
		return (mbus_code == MEDIA_BUS_FMT_SGBRG10_1X10);
	case V4L2_PIX_FMT_SGRBG10:
		return (mbus_code == MEDIA_BUS_FMT_SGRBG10_1X10);
	case V4L2_PIX_FMT_SRGGB10:
		return (mbus_code == MEDIA_BUS_FMT_SRGGB10_1X10);
	case V4L2_PIX_FMT_SBGGR12:
		return (mbus_code == MEDIA_BUS_FMT_SBGGR12_1X12);
	case V4L2_PIX_FMT_SGBRG12:
		return (mbus_code == MEDIA_BUS_FMT_SGBRG12_1X12);
	case V4L2_PIX_FMT_SGRBG12:
		return (mbus_code == MEDIA_BUS_FMT_SGRBG12_1X12);
	case V4L2_PIX_FMT_SRGGB12:
		return (mbus_code == MEDIA_BUS_FMT_SRGGB12_1X12);

	case V4L2_PIX_FMT_YUYV:
		return (mbus_code == MEDIA_BUS_FMT_YUYV8_2X8);
	case V4L2_PIX_FMT_YVYU:
		return (mbus_code == MEDIA_BUS_FMT_YVYU8_2X8);
	case V4L2_PIX_FMT_UYVY:
		return (mbus_code == MEDIA_BUS_FMT_UYVY8_2X8);
	case V4L2_PIX_FMT_VYUY:
		return (mbus_code == MEDIA_BUS_FMT_VYUY8_2X8);

	case V4L2_PIX_FMT_HM12:
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV21:
	case V4L2_PIX_FMT_NV16:
	case V4L2_PIX_FMT_NV61:
	case V4L2_PIX_FMT_YUV420:
	case V4L2_PIX_FMT_YVU420:
	case V4L2_PIX_FMT_YUV422P:
		switch (mbus_code) {
		case MEDIA_BUS_FMT_UYVY8_2X8:
		case MEDIA_BUS_FMT_VYUY8_2X8:
		case MEDIA_BUS_FMT_YUYV8_2X8:
		case MEDIA_BUS_FMT_YVYU8_2X8:
			return true;
		default:
			dev_dbg(sdev->dev, "Unsupported mbus code: 0x%x\n",
				mbus_code);
			break;
		}
		break;

	case V4L2_PIX_FMT_RGB565:
		return (mbus_code == MEDIA_BUS_FMT_RGB565_2X8_LE);
	case V4L2_PIX_FMT_RGB565X:
		return (mbus_code == MEDIA_BUS_FMT_RGB565_2X8_BE);

	case V4L2_PIX_FMT_JPEG:
		return (mbus_code == MEDIA_BUS_FMT_JPEG_1X8);

	default:
		dev_dbg(sdev->dev, "Unsupported pixformat: 0x%x\n", pixformat);
		break;
	}

	return false;
}