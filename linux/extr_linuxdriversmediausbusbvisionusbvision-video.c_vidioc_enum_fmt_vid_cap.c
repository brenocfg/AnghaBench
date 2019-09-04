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
struct v4l2_fmtdesc {int index; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  description; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  format; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int EINVAL ; 
 int USBVISION_SUPPORTED_PALETTES ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* usbvision_v4l2_format ; 

__attribute__((used)) static int vidioc_enum_fmt_vid_cap(struct file *file, void  *priv,
					struct v4l2_fmtdesc *vfd)
{
	if (vfd->index >= USBVISION_SUPPORTED_PALETTES - 1)
		return -EINVAL;
	strcpy(vfd->description, usbvision_v4l2_format[vfd->index].desc);
	vfd->pixelformat = usbvision_v4l2_format[vfd->index].format;
	return 0;
}