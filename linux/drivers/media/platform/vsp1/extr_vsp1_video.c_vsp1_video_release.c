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
struct TYPE_2__ {struct v4l2_fh* owner; } ;
struct vsp1_video {int /*<<< orphan*/  vsp1; int /*<<< orphan*/  lock; TYPE_1__ queue; } ;
struct v4l2_fh {int dummy; } ;
struct file {struct v4l2_fh* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_release (struct file*) ; 
 int /*<<< orphan*/  vb2_queue_release (TYPE_1__*) ; 
 struct vsp1_video* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  vsp1_device_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vsp1_video_release(struct file *file)
{
	struct vsp1_video *video = video_drvdata(file);
	struct v4l2_fh *vfh = file->private_data;

	mutex_lock(&video->lock);
	if (video->queue.owner == vfh) {
		vb2_queue_release(&video->queue);
		video->queue.owner = NULL;
	}
	mutex_unlock(&video->lock);

	vsp1_device_put(video->vsp1);

	v4l2_fh_release(file);

	file->private_data = NULL;

	return 0;
}