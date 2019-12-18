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

/* Variables and functions */
#define  V4L2_PIX_FMT_BGR24 158 
#define  V4L2_PIX_FMT_BGR32 157 
#define  V4L2_PIX_FMT_HM12 156 
#define  V4L2_PIX_FMT_JPEG 155 
#define  V4L2_PIX_FMT_NV12 154 
#define  V4L2_PIX_FMT_NV16 153 
#define  V4L2_PIX_FMT_NV21 152 
#define  V4L2_PIX_FMT_NV61 151 
#define  V4L2_PIX_FMT_RGB24 150 
#define  V4L2_PIX_FMT_RGB32 149 
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
 int /*<<< orphan*/  WARN (int,char*,unsigned int) ; 

__attribute__((used)) static inline int sun6i_csi_get_bpp(unsigned int pixformat)
{
	switch (pixformat) {
	case V4L2_PIX_FMT_SBGGR8:
	case V4L2_PIX_FMT_SGBRG8:
	case V4L2_PIX_FMT_SGRBG8:
	case V4L2_PIX_FMT_SRGGB8:
	case V4L2_PIX_FMT_JPEG:
		return 8;
	case V4L2_PIX_FMT_SBGGR10:
	case V4L2_PIX_FMT_SGBRG10:
	case V4L2_PIX_FMT_SGRBG10:
	case V4L2_PIX_FMT_SRGGB10:
		return 10;
	case V4L2_PIX_FMT_SBGGR12:
	case V4L2_PIX_FMT_SGBRG12:
	case V4L2_PIX_FMT_SGRBG12:
	case V4L2_PIX_FMT_SRGGB12:
	case V4L2_PIX_FMT_HM12:
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV21:
	case V4L2_PIX_FMT_YUV420:
	case V4L2_PIX_FMT_YVU420:
		return 12;
	case V4L2_PIX_FMT_YUYV:
	case V4L2_PIX_FMT_YVYU:
	case V4L2_PIX_FMT_UYVY:
	case V4L2_PIX_FMT_VYUY:
	case V4L2_PIX_FMT_NV16:
	case V4L2_PIX_FMT_NV61:
	case V4L2_PIX_FMT_YUV422P:
	case V4L2_PIX_FMT_RGB565:
	case V4L2_PIX_FMT_RGB565X:
		return 16;
	case V4L2_PIX_FMT_RGB24:
	case V4L2_PIX_FMT_BGR24:
		return 24;
	case V4L2_PIX_FMT_RGB32:
	case V4L2_PIX_FMT_BGR32:
		return 32;
	default:
		WARN(1, "Unsupported pixformat: 0x%x\n", pixformat);
		break;
	}

	return 0;
}