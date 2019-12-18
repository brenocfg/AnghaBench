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
typedef  unsigned int u32 ;
struct v4l2_fmtdesc {unsigned int index; scalar_t__ type; int /*<<< orphan*/  pixelformat; } ;
struct v4l2_fh {TYPE_3__* vdev; } ;
struct uvc_streaming {struct uvc_device* dev; } ;
struct uvc_device {TYPE_2__* info; } ;
struct file {struct v4l2_fh* private_data; } ;
struct TYPE_6__ {TYPE_1__* queue; } ;
struct TYPE_5__ {int /*<<< orphan*/  meta_format; } ;
struct TYPE_4__ {scalar_t__ type; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_META_FMT_UVC ; 
 int /*<<< orphan*/  memset (struct v4l2_fmtdesc*,int /*<<< orphan*/ ,int) ; 
 struct uvc_streaming* video_get_drvdata (TYPE_3__*) ; 

__attribute__((used)) static int uvc_meta_v4l2_enum_formats(struct file *file, void *fh,
				      struct v4l2_fmtdesc *fdesc)
{
	struct v4l2_fh *vfh = file->private_data;
	struct uvc_streaming *stream = video_get_drvdata(vfh->vdev);
	struct uvc_device *dev = stream->dev;
	u32 index = fdesc->index;

	if (fdesc->type != vfh->vdev->queue->type ||
	    index > 1U || (index && !dev->info->meta_format))
		return -EINVAL;

	memset(fdesc, 0, sizeof(*fdesc));

	fdesc->type = vfh->vdev->queue->type;
	fdesc->index = index;
	fdesc->pixelformat = index ? dev->info->meta_format : V4L2_META_FMT_UVC;

	return 0;
}