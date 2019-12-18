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
typedef  scalar_t__ u32 ;
struct sun6i_csi_dev {int /*<<< orphan*/  dev; } ;
typedef  enum csi_output_fmt { ____Placeholder_csi_output_fmt } csi_output_fmt ;

/* Variables and functions */
 int CSI_FIELD_MB_YUV420 ; 
 int CSI_FIELD_PLANAR_YUV420 ; 
 int CSI_FIELD_PLANAR_YUV422 ; 
 int CSI_FIELD_RAW_10 ; 
 int CSI_FIELD_RAW_12 ; 
 int CSI_FIELD_RAW_8 ; 
 int CSI_FIELD_RGB565 ; 
 int CSI_FIELD_UV_CB_YUV420 ; 
 int CSI_FIELD_UV_CB_YUV422 ; 
 int CSI_FRAME_MB_YUV420 ; 
 int CSI_FRAME_PLANAR_YUV420 ; 
 int CSI_FRAME_PLANAR_YUV422 ; 
 int CSI_FRAME_RAW_10 ; 
 int CSI_FRAME_RAW_12 ; 
 int CSI_FRAME_RAW_8 ; 
 int CSI_FRAME_RGB565 ; 
 int CSI_FRAME_UV_CB_YUV420 ; 
 int CSI_FRAME_UV_CB_YUV422 ; 
 scalar_t__ V4L2_FIELD_INTERLACED ; 
 scalar_t__ V4L2_FIELD_INTERLACED_BT ; 
 scalar_t__ V4L2_FIELD_INTERLACED_TB ; 
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
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static enum csi_output_fmt get_csi_output_format(struct sun6i_csi_dev *sdev,
						 u32 pixformat, u32 field)
{
	bool buf_interlaced = false;

	if (field == V4L2_FIELD_INTERLACED
	    || field == V4L2_FIELD_INTERLACED_TB
	    || field == V4L2_FIELD_INTERLACED_BT)
		buf_interlaced = true;

	switch (pixformat) {
	case V4L2_PIX_FMT_SBGGR8:
	case V4L2_PIX_FMT_SGBRG8:
	case V4L2_PIX_FMT_SGRBG8:
	case V4L2_PIX_FMT_SRGGB8:
		return buf_interlaced ? CSI_FRAME_RAW_8 : CSI_FIELD_RAW_8;
	case V4L2_PIX_FMT_SBGGR10:
	case V4L2_PIX_FMT_SGBRG10:
	case V4L2_PIX_FMT_SGRBG10:
	case V4L2_PIX_FMT_SRGGB10:
		return buf_interlaced ? CSI_FRAME_RAW_10 : CSI_FIELD_RAW_10;
	case V4L2_PIX_FMT_SBGGR12:
	case V4L2_PIX_FMT_SGBRG12:
	case V4L2_PIX_FMT_SGRBG12:
	case V4L2_PIX_FMT_SRGGB12:
		return buf_interlaced ? CSI_FRAME_RAW_12 : CSI_FIELD_RAW_12;

	case V4L2_PIX_FMT_YUYV:
	case V4L2_PIX_FMT_YVYU:
	case V4L2_PIX_FMT_UYVY:
	case V4L2_PIX_FMT_VYUY:
		return buf_interlaced ? CSI_FRAME_RAW_8 : CSI_FIELD_RAW_8;

	case V4L2_PIX_FMT_HM12:
		return buf_interlaced ? CSI_FRAME_MB_YUV420 :
					CSI_FIELD_MB_YUV420;
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV21:
		return buf_interlaced ? CSI_FRAME_UV_CB_YUV420 :
					CSI_FIELD_UV_CB_YUV420;
	case V4L2_PIX_FMT_YUV420:
	case V4L2_PIX_FMT_YVU420:
		return buf_interlaced ? CSI_FRAME_PLANAR_YUV420 :
					CSI_FIELD_PLANAR_YUV420;
	case V4L2_PIX_FMT_NV16:
	case V4L2_PIX_FMT_NV61:
		return buf_interlaced ? CSI_FRAME_UV_CB_YUV422 :
					CSI_FIELD_UV_CB_YUV422;
	case V4L2_PIX_FMT_YUV422P:
		return buf_interlaced ? CSI_FRAME_PLANAR_YUV422 :
					CSI_FIELD_PLANAR_YUV422;

	case V4L2_PIX_FMT_RGB565:
	case V4L2_PIX_FMT_RGB565X:
		return buf_interlaced ? CSI_FRAME_RGB565 : CSI_FIELD_RGB565;

	case V4L2_PIX_FMT_JPEG:
		return buf_interlaced ? CSI_FRAME_RAW_8 : CSI_FIELD_RAW_8;

	default:
		dev_warn(sdev->dev, "Unsupported pixformat: 0x%x\n", pixformat);
		break;
	}

	return CSI_FIELD_RAW_8;
}