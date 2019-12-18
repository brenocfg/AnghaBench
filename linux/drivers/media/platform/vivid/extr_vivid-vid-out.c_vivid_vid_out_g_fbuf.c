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
struct TYPE_4__ {int length; } ;
struct TYPE_5__ {TYPE_1__ green; } ;
struct vivid_dev {int fbuf_out_flags; int display_height; int display_byte_stride; TYPE_2__ fb_defined; int /*<<< orphan*/  display_width; scalar_t__ video_pbase; } ;
struct TYPE_6__ {int height; int bytesperline; int sizeimage; scalar_t__ priv; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  width; } ;
struct v4l2_framebuffer {int capability; int flags; TYPE_3__ fmt; void* base; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int V4L2_FBUF_CAP_BITMAP_CLIPPING ; 
 int V4L2_FBUF_CAP_CHROMAKEY ; 
 int V4L2_FBUF_CAP_EXTERNOVERLAY ; 
 int V4L2_FBUF_CAP_GLOBAL_ALPHA ; 
 int V4L2_FBUF_CAP_LIST_CLIPPING ; 
 int V4L2_FBUF_CAP_LOCAL_ALPHA ; 
 int V4L2_FBUF_CAP_LOCAL_INV_ALPHA ; 
 int V4L2_FBUF_CAP_SRC_CHROMAKEY ; 
 int V4L2_FBUF_FLAG_OVERLAY ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_ARGB555 ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_RGB565 ; 
 struct vivid_dev* video_drvdata (struct file*) ; 

int vivid_vid_out_g_fbuf(struct file *file, void *fh,
				struct v4l2_framebuffer *a)
{
	struct vivid_dev *dev = video_drvdata(file);

	a->capability = V4L2_FBUF_CAP_EXTERNOVERLAY |
			V4L2_FBUF_CAP_BITMAP_CLIPPING |
			V4L2_FBUF_CAP_LIST_CLIPPING |
			V4L2_FBUF_CAP_CHROMAKEY |
			V4L2_FBUF_CAP_SRC_CHROMAKEY |
			V4L2_FBUF_CAP_GLOBAL_ALPHA |
			V4L2_FBUF_CAP_LOCAL_ALPHA |
			V4L2_FBUF_CAP_LOCAL_INV_ALPHA;
	a->flags = V4L2_FBUF_FLAG_OVERLAY | dev->fbuf_out_flags;
	a->base = (void *)dev->video_pbase;
	a->fmt.width = dev->display_width;
	a->fmt.height = dev->display_height;
	if (dev->fb_defined.green.length == 5)
		a->fmt.pixelformat = V4L2_PIX_FMT_ARGB555;
	else
		a->fmt.pixelformat = V4L2_PIX_FMT_RGB565;
	a->fmt.bytesperline = dev->display_byte_stride;
	a->fmt.sizeimage = a->fmt.height * a->fmt.bytesperline;
	a->fmt.field = V4L2_FIELD_NONE;
	a->fmt.colorspace = V4L2_COLORSPACE_SRGB;
	a->fmt.priv = 0;
	return 0;
}