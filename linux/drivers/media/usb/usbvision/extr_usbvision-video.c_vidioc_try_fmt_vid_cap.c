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
struct TYPE_4__ {scalar_t__ pixelformat; int width; int height; int bytesperline; int sizeimage; int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; } ;
struct TYPE_5__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct TYPE_6__ {scalar_t__ format; int bytes_per_pixel; } ;
struct usb_usbvision {TYPE_3__ palette; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAX_FRAME_HEIGHT ; 
 int /*<<< orphan*/  MAX_FRAME_WIDTH ; 
 int /*<<< orphan*/  MIN_FRAME_HEIGHT ; 
 int /*<<< orphan*/  MIN_FRAME_WIDTH ; 
 int /*<<< orphan*/  RESTRICT_TO_RANGE (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int USBVISION_SUPPORTED_PALETTES ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 TYPE_3__* usbvision_v4l2_format ; 
 struct usb_usbvision* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_try_fmt_vid_cap(struct file *file, void *priv,
			       struct v4l2_format *vf)
{
	struct usb_usbvision *usbvision = video_drvdata(file);
	int format_idx;

	/* Find requested format in available ones */
	for (format_idx = 0; format_idx < USBVISION_SUPPORTED_PALETTES; format_idx++) {
		if (vf->fmt.pix.pixelformat ==
		   usbvision_v4l2_format[format_idx].format) {
			usbvision->palette = usbvision_v4l2_format[format_idx];
			break;
		}
	}
	/* robustness */
	if (format_idx == USBVISION_SUPPORTED_PALETTES)
		return -EINVAL;
	RESTRICT_TO_RANGE(vf->fmt.pix.width, MIN_FRAME_WIDTH, MAX_FRAME_WIDTH);
	RESTRICT_TO_RANGE(vf->fmt.pix.height, MIN_FRAME_HEIGHT, MAX_FRAME_HEIGHT);

	vf->fmt.pix.bytesperline = vf->fmt.pix.width*
		usbvision->palette.bytes_per_pixel;
	vf->fmt.pix.sizeimage = vf->fmt.pix.bytesperline*vf->fmt.pix.height;
	vf->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	vf->fmt.pix.field = V4L2_FIELD_NONE; /* Always progressive image */

	return 0;
}