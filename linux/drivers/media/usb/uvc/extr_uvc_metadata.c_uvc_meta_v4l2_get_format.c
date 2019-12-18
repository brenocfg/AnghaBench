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
struct v4l2_meta_format {int /*<<< orphan*/  buffersize; int /*<<< orphan*/  dataformat; } ;
struct TYPE_7__ {struct v4l2_meta_format meta; } ;
struct v4l2_format {scalar_t__ type; TYPE_3__ fmt; } ;
struct v4l2_fh {TYPE_4__* vdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  format; } ;
struct uvc_streaming {TYPE_2__ meta; } ;
struct file {struct v4l2_fh* private_data; } ;
struct TYPE_8__ {TYPE_1__* queue; } ;
struct TYPE_5__ {scalar_t__ type; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  UVC_METATADA_BUF_SIZE ; 
 int /*<<< orphan*/  memset (struct v4l2_meta_format*,int /*<<< orphan*/ ,int) ; 
 struct uvc_streaming* video_get_drvdata (TYPE_4__*) ; 

__attribute__((used)) static int uvc_meta_v4l2_get_format(struct file *file, void *fh,
				    struct v4l2_format *format)
{
	struct v4l2_fh *vfh = file->private_data;
	struct uvc_streaming *stream = video_get_drvdata(vfh->vdev);
	struct v4l2_meta_format *fmt = &format->fmt.meta;

	if (format->type != vfh->vdev->queue->type)
		return -EINVAL;

	memset(fmt, 0, sizeof(*fmt));

	fmt->dataformat = stream->meta.format;
	fmt->buffersize = UVC_METATADA_BUF_SIZE;

	return 0;
}