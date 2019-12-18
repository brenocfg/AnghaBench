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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_pix_format {int height; int width; scalar_t__ pixelformat; int bytesperline; int sizeimage; void* colorspace; int /*<<< orphan*/  field; } ;
struct TYPE_2__ {scalar_t__ pixelformat; } ;

/* Variables and functions */
 int NUM_OUTPUT_FORMATS ; 
 int RGB24_BPP ; 
 int RGB32_BPP ; 
 int RGB565_BPP ; 
 void* V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
#define  V4L2_PIX_FMT_BGR32 134 
#define  V4L2_PIX_FMT_RGB24 133 
#define  V4L2_PIX_FMT_RGB32 132 
#define  V4L2_PIX_FMT_RGB565 131 
#define  V4L2_PIX_FMT_RGB565X 130 
#define  V4L2_PIX_FMT_UYVY 129 
#define  V4L2_PIX_FMT_YUYV 128 
 scalar_t__ VID_MAX_HEIGHT ; 
 scalar_t__ VID_MAX_WIDTH ; 
 scalar_t__ VID_MIN_HEIGHT ; 
 scalar_t__ VID_MIN_WIDTH ; 
 int YUYV_BPP ; 
 void* clamp (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* omap_formats ; 

__attribute__((used)) static int omap_vout_try_format(struct v4l2_pix_format *pix)
{
	int ifmt, bpp = 0;

	pix->height = clamp(pix->height, (u32)VID_MIN_HEIGHT,
						(u32)VID_MAX_HEIGHT);
	pix->width = clamp(pix->width, (u32)VID_MIN_WIDTH, (u32)VID_MAX_WIDTH);

	for (ifmt = 0; ifmt < NUM_OUTPUT_FORMATS; ifmt++) {
		if (pix->pixelformat == omap_formats[ifmt].pixelformat)
			break;
	}

	if (ifmt == NUM_OUTPUT_FORMATS)
		ifmt = 0;

	pix->pixelformat = omap_formats[ifmt].pixelformat;
	pix->field = V4L2_FIELD_NONE;

	switch (pix->pixelformat) {
	case V4L2_PIX_FMT_YUYV:
	case V4L2_PIX_FMT_UYVY:
	default:
		pix->colorspace = V4L2_COLORSPACE_SRGB;
		bpp = YUYV_BPP;
		break;
	case V4L2_PIX_FMT_RGB565:
	case V4L2_PIX_FMT_RGB565X:
		pix->colorspace = V4L2_COLORSPACE_SRGB;
		bpp = RGB565_BPP;
		break;
	case V4L2_PIX_FMT_RGB24:
		pix->colorspace = V4L2_COLORSPACE_SRGB;
		bpp = RGB24_BPP;
		break;
	case V4L2_PIX_FMT_RGB32:
	case V4L2_PIX_FMT_BGR32:
		pix->colorspace = V4L2_COLORSPACE_SRGB;
		bpp = RGB32_BPP;
		break;
	}
	pix->bytesperline = pix->width * bpp;
	pix->sizeimage = pix->bytesperline * pix->height;

	return bpp;
}