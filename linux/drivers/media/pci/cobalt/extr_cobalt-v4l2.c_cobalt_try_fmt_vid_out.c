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
struct v4l2_pix_format {int width; int height; int pixelformat; int bytesperline; int sizeimage; int /*<<< orphan*/  field; } ;
struct TYPE_2__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int COBALT_BYTES_PER_PIXEL_RGB32 ; 
 int COBALT_BYTES_PER_PIXEL_YUYV ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
#define  V4L2_PIX_FMT_BGR32 129 
#define  V4L2_PIX_FMT_YUYV 128 
 void* max (int,int) ; 

__attribute__((used)) static int cobalt_try_fmt_vid_out(struct file *file, void *priv_fh,
		struct v4l2_format *f)
{
	struct v4l2_pix_format *pix = &f->fmt.pix;

	/* Check for min (QCIF) and max (Full HD) size */
	if ((pix->width < 176) || (pix->height < 144)) {
		pix->width = 176;
		pix->height = 144;
	}

	if ((pix->width > 1920) || (pix->height > 1080)) {
		pix->width = 1920;
		pix->height = 1080;
	}

	/* Make width multiple of 4 */
	pix->width &= ~0x3;

	/* Make height multiple of 2 */
	pix->height &= ~0x1;

	switch (pix->pixelformat) {
	case V4L2_PIX_FMT_YUYV:
	default:
		pix->bytesperline = max(pix->bytesperline & ~0x3,
				pix->width * COBALT_BYTES_PER_PIXEL_YUYV);
		pix->pixelformat = V4L2_PIX_FMT_YUYV;
		break;
	case V4L2_PIX_FMT_BGR32:
		pix->bytesperline = max(pix->bytesperline & ~0x3,
				pix->width * COBALT_BYTES_PER_PIXEL_RGB32);
		break;
	}

	pix->sizeimage = pix->bytesperline * pix->height;
	pix->field = V4L2_FIELD_NONE;

	return 0;
}