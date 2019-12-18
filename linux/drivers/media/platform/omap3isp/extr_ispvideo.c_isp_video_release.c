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
struct v4l2_fh {int dummy; } ;
struct isp_video_fh {int /*<<< orphan*/  queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  entity; } ;
struct isp_video {int /*<<< orphan*/  isp; TYPE_1__ video; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  type; } ;
struct file {struct v4l2_fh* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  isp_video_streamoff (struct file*,struct v4l2_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct isp_video_fh*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap3isp_put (int /*<<< orphan*/ ) ; 
 struct isp_video_fh* to_isp_video_fh (struct v4l2_fh*) ; 
 int /*<<< orphan*/  v4l2_fh_del (struct v4l2_fh*) ; 
 int /*<<< orphan*/  v4l2_fh_exit (struct v4l2_fh*) ; 
 int /*<<< orphan*/  v4l2_pipeline_pm_use (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_queue_release (int /*<<< orphan*/ *) ; 
 struct isp_video* video_drvdata (struct file*) ; 

__attribute__((used)) static int isp_video_release(struct file *file)
{
	struct isp_video *video = video_drvdata(file);
	struct v4l2_fh *vfh = file->private_data;
	struct isp_video_fh *handle = to_isp_video_fh(vfh);

	/* Disable streaming and free the buffers queue resources. */
	isp_video_streamoff(file, vfh, video->type);

	mutex_lock(&video->queue_lock);
	vb2_queue_release(&handle->queue);
	mutex_unlock(&video->queue_lock);

	v4l2_pipeline_pm_use(&video->video.entity, 0);

	/* Release the file handle. */
	v4l2_fh_del(vfh);
	v4l2_fh_exit(vfh);
	kfree(handle);
	file->private_data = NULL;

	omap3isp_put(video->isp);

	return 0;
}