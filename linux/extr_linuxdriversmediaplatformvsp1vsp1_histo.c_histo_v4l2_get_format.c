#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ type; } ;
struct vsp1_histogram {int /*<<< orphan*/  data_size; int /*<<< orphan*/  meta_format; TYPE_1__ queue; } ;
struct v4l2_meta_format {int /*<<< orphan*/  buffersize; int /*<<< orphan*/  dataformat; } ;
struct TYPE_4__ {struct v4l2_meta_format meta; } ;
struct v4l2_format {scalar_t__ type; TYPE_2__ fmt; } ;
struct v4l2_fh {int /*<<< orphan*/  vdev; } ;
struct file {struct v4l2_fh* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memset (struct v4l2_meta_format*,int /*<<< orphan*/ ,int) ; 
 struct vsp1_histogram* vdev_to_histo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int histo_v4l2_get_format(struct file *file, void *fh,
				 struct v4l2_format *format)
{
	struct v4l2_fh *vfh = file->private_data;
	struct vsp1_histogram *histo = vdev_to_histo(vfh->vdev);
	struct v4l2_meta_format *meta = &format->fmt.meta;

	if (format->type != histo->queue.type)
		return -EINVAL;

	memset(meta, 0, sizeof(*meta));

	meta->dataformat = histo->meta_format;
	meta->buffersize = histo->data_size;

	return 0;
}