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
struct vpbe_display {struct vpbe_device* vpbe_dev; } ;
struct TYPE_2__ {int xres; int yres; scalar_t__ interlaced; } ;
struct vpbe_device {TYPE_1__ current_timings; } ;
struct v4l2_pix_format {scalar_t__ pixelformat; scalar_t__ field; int width; int height; int bytesperline; int sizeimage; } ;

/* Variables and functions */
 scalar_t__ V4L2_FIELD_INTERLACED ; 
 scalar_t__ V4L2_FIELD_NONE ; 
 scalar_t__ V4L2_PIX_FMT_NV12 ; 
 scalar_t__ V4L2_PIX_FMT_UYVY ; 

__attribute__((used)) static int vpbe_try_format(struct vpbe_display *disp_dev,
			struct v4l2_pix_format *pixfmt, int check)
{
	struct vpbe_device *vpbe_dev = disp_dev->vpbe_dev;
	int min_height = 1;
	int min_width = 32;
	int max_height;
	int max_width;
	int bpp;

	if ((pixfmt->pixelformat != V4L2_PIX_FMT_UYVY) &&
	    (pixfmt->pixelformat != V4L2_PIX_FMT_NV12))
		/* choose default as V4L2_PIX_FMT_UYVY */
		pixfmt->pixelformat = V4L2_PIX_FMT_UYVY;

	/* Check the field format */
	if ((pixfmt->field != V4L2_FIELD_INTERLACED) &&
		(pixfmt->field != V4L2_FIELD_NONE)) {
		if (vpbe_dev->current_timings.interlaced)
			pixfmt->field = V4L2_FIELD_INTERLACED;
		else
			pixfmt->field = V4L2_FIELD_NONE;
	}

	if (pixfmt->field == V4L2_FIELD_INTERLACED)
		min_height = 2;

	if (pixfmt->pixelformat == V4L2_PIX_FMT_NV12)
		bpp = 1;
	else
		bpp = 2;

	max_width = vpbe_dev->current_timings.xres;
	max_height = vpbe_dev->current_timings.yres;

	min_width /= bpp;

	if (!pixfmt->width || (pixfmt->width < min_width) ||
		(pixfmt->width > max_width)) {
		pixfmt->width = vpbe_dev->current_timings.xres;
	}

	if (!pixfmt->height || (pixfmt->height  < min_height) ||
		(pixfmt->height  > max_height)) {
		pixfmt->height = vpbe_dev->current_timings.yres;
	}

	if (pixfmt->bytesperline < (pixfmt->width * bpp))
		pixfmt->bytesperline = pixfmt->width * bpp;

	/* Make the bytesperline 32 byte aligned */
	pixfmt->bytesperline = ((pixfmt->width * bpp + 31) & ~31);

	if (pixfmt->pixelformat == V4L2_PIX_FMT_NV12)
		pixfmt->sizeimage = pixfmt->bytesperline * pixfmt->height +
				(pixfmt->bytesperline * pixfmt->height >> 1);
	else
		pixfmt->sizeimage = pixfmt->bytesperline * pixfmt->height;

	return 0;
}