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
struct TYPE_6__ {scalar_t__ type; } ;
struct vsp1_video {int /*<<< orphan*/  lock; TYPE_2__* rwpf; TYPE_3__ queue; } ;
struct vsp1_format_info {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  pix_mp; } ;
struct v4l2_format {scalar_t__ type; TYPE_1__ fmt; } ;
struct v4l2_fh {int /*<<< orphan*/  vdev; } ;
struct file {struct v4l2_fh* private_data; } ;
struct TYPE_5__ {struct vsp1_format_info const* fmtinfo; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int __vsp1_video_try_format (struct vsp1_video*,int /*<<< orphan*/ *,struct vsp1_format_info const**) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vsp1_video* to_vsp1_video (int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_is_busy (TYPE_3__*) ; 

__attribute__((used)) static int
vsp1_video_set_format(struct file *file, void *fh, struct v4l2_format *format)
{
	struct v4l2_fh *vfh = file->private_data;
	struct vsp1_video *video = to_vsp1_video(vfh->vdev);
	const struct vsp1_format_info *info;
	int ret;

	if (format->type != video->queue.type)
		return -EINVAL;

	ret = __vsp1_video_try_format(video, &format->fmt.pix_mp, &info);
	if (ret < 0)
		return ret;

	mutex_lock(&video->lock);

	if (vb2_is_busy(&video->queue)) {
		ret = -EBUSY;
		goto done;
	}

	video->rwpf->format = format->fmt.pix_mp;
	video->rwpf->fmtinfo = info;

done:
	mutex_unlock(&video->lock);
	return ret;
}