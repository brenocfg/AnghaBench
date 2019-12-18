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
struct v4l2_buffer {int dummy; } ;
struct isp_video_fh {int /*<<< orphan*/  queue; } ;
struct TYPE_4__ {TYPE_1__* v4l2_dev; } ;
struct isp_video {int /*<<< orphan*/  queue_lock; TYPE_2__ video; } ;
struct file {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct isp_video_fh* to_isp_video_fh (void*) ; 
 int vb2_qbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct v4l2_buffer*) ; 
 struct isp_video* video_drvdata (struct file*) ; 

__attribute__((used)) static int
isp_video_qbuf(struct file *file, void *fh, struct v4l2_buffer *b)
{
	struct isp_video_fh *vfh = to_isp_video_fh(fh);
	struct isp_video *video = video_drvdata(file);
	int ret;

	mutex_lock(&video->queue_lock);
	ret = vb2_qbuf(&vfh->queue, video->video.v4l2_dev->mdev, b);
	mutex_unlock(&video->queue_lock);

	return ret;
}