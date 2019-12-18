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
struct vm_area_struct {int dummy; } ;
struct videobuf_queue {int dummy; } ;
struct video_device {int vfl_type; int /*<<< orphan*/  lock; } ;
struct saa7146_fh {struct videobuf_queue vbi_q; TYPE_2__* dev; struct videobuf_queue video_q; } ;
struct file {struct saa7146_fh* private_data; } ;
struct TYPE_4__ {TYPE_1__* ext_vv_data; } ;
struct TYPE_3__ {int capabilities; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DEB_EE (char*,struct file*,struct vm_area_struct*) ; 
 int ENODEV ; 
 int ERESTARTSYS ; 
 int V4L2_CAP_SLICED_VBI_OUTPUT ; 
#define  VFL_TYPE_GRABBER 129 
#define  VFL_TYPE_VBI 128 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 
 struct video_device* video_devdata (struct file*) ; 
 int videobuf_mmap_mapper (struct videobuf_queue*,struct vm_area_struct*) ; 

__attribute__((used)) static int fops_mmap(struct file *file, struct vm_area_struct * vma)
{
	struct video_device *vdev = video_devdata(file);
	struct saa7146_fh *fh = file->private_data;
	struct videobuf_queue *q;
	int res;

	switch (vdev->vfl_type) {
	case VFL_TYPE_GRABBER: {
		DEB_EE("V4L2_BUF_TYPE_VIDEO_CAPTURE: file:%p, vma:%p\n",
		       file, vma);
		q = &fh->video_q;
		break;
		}
	case VFL_TYPE_VBI: {
		DEB_EE("V4L2_BUF_TYPE_VBI_CAPTURE: file:%p, vma:%p\n",
		       file, vma);
		if (fh->dev->ext_vv_data->capabilities & V4L2_CAP_SLICED_VBI_OUTPUT)
			return -ENODEV;
		q = &fh->vbi_q;
		break;
		}
	default:
		BUG();
	}

	if (mutex_lock_interruptible(vdev->lock))
		return -ERESTARTSYS;
	res = videobuf_mmap_mapper(q, vma);
	mutex_unlock(vdev->lock);
	return res;
}