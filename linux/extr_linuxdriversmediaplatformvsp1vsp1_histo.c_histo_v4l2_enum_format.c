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
struct TYPE_2__ {scalar_t__ type; } ;
struct vsp1_histogram {int /*<<< orphan*/  meta_format; TYPE_1__ queue; } ;
struct v4l2_fmtdesc {scalar_t__ index; scalar_t__ type; int /*<<< orphan*/  pixelformat; } ;
struct v4l2_fh {int /*<<< orphan*/  vdev; } ;
struct file {struct v4l2_fh* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 struct vsp1_histogram* vdev_to_histo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int histo_v4l2_enum_format(struct file *file, void *fh,
				  struct v4l2_fmtdesc *f)
{
	struct v4l2_fh *vfh = file->private_data;
	struct vsp1_histogram *histo = vdev_to_histo(vfh->vdev);

	if (f->index > 0 || f->type != histo->queue.type)
		return -EINVAL;

	f->pixelformat = histo->meta_format;

	return 0;
}