#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct v4l2_meta_format {scalar_t__ dataformat; int /*<<< orphan*/  buffersize; } ;
struct TYPE_5__ {struct v4l2_meta_format meta; } ;
struct v4l2_format {scalar_t__ type; TYPE_1__ fmt; } ;
struct v4l2_fh {TYPE_4__* vdev; } ;
struct uvc_streaming {struct uvc_device* dev; } ;
struct uvc_device {TYPE_3__* info; } ;
struct file {struct v4l2_fh* private_data; } ;
struct TYPE_8__ {TYPE_2__* queue; } ;
struct TYPE_7__ {scalar_t__ meta_format; } ;
struct TYPE_6__ {scalar_t__ type; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  UVC_METATADA_BUF_SIZE ; 
 scalar_t__ V4L2_META_FMT_UVC ; 
 int /*<<< orphan*/  memset (struct v4l2_meta_format*,int /*<<< orphan*/ ,int) ; 
 struct uvc_streaming* video_get_drvdata (TYPE_4__*) ; 

__attribute__((used)) static int uvc_meta_v4l2_try_format(struct file *file, void *fh,
				    struct v4l2_format *format)
{
	struct v4l2_fh *vfh = file->private_data;
	struct uvc_streaming *stream = video_get_drvdata(vfh->vdev);
	struct uvc_device *dev = stream->dev;
	struct v4l2_meta_format *fmt = &format->fmt.meta;
	u32 fmeta = fmt->dataformat;

	if (format->type != vfh->vdev->queue->type)
		return -EINVAL;

	memset(fmt, 0, sizeof(*fmt));

	fmt->dataformat = fmeta == dev->info->meta_format
			? fmeta : V4L2_META_FMT_UVC;
	fmt->buffersize = UVC_METATADA_BUF_SIZE;

	return 0;
}