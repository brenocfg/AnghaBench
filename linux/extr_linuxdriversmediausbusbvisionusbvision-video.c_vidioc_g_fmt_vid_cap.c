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
struct TYPE_5__ {int width; int height; int bytesperline; int sizeimage; int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_6__ {TYPE_2__ pix; } ;
struct v4l2_format {TYPE_3__ fmt; } ;
struct TYPE_4__ {int bytes_per_pixel; int /*<<< orphan*/  format; } ;
struct usb_usbvision {int curwidth; int curheight; TYPE_1__ palette; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 struct usb_usbvision* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_fmt_vid_cap(struct file *file, void *priv,
					struct v4l2_format *vf)
{
	struct usb_usbvision *usbvision = video_drvdata(file);
	vf->fmt.pix.width = usbvision->curwidth;
	vf->fmt.pix.height = usbvision->curheight;
	vf->fmt.pix.pixelformat = usbvision->palette.format;
	vf->fmt.pix.bytesperline =
		usbvision->curwidth * usbvision->palette.bytes_per_pixel;
	vf->fmt.pix.sizeimage = vf->fmt.pix.bytesperline * usbvision->curheight;
	vf->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	vf->fmt.pix.field = V4L2_FIELD_NONE; /* Always progressive image */

	return 0;
}