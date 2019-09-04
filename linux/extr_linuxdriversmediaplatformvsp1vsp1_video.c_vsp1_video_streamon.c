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
struct TYPE_5__ {int /*<<< orphan*/  entity; } ;
struct TYPE_6__ {scalar_t__ owner; } ;
struct vsp1_video {TYPE_2__ video; TYPE_3__ queue; TYPE_1__* vsp1; } ;
struct vsp1_pipeline {int /*<<< orphan*/  pipe; } ;
struct v4l2_fh {int /*<<< orphan*/  vdev; } ;
struct media_device {int /*<<< orphan*/  graph_mutex; } ;
struct file {scalar_t__ private_data; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;
struct TYPE_4__ {struct media_device media_dev; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ IS_ERR (struct vsp1_pipeline*) ; 
 int PTR_ERR (struct vsp1_pipeline*) ; 
 int __media_pipeline_start (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_pipeline_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vsp1_video* to_vsp1_video (int /*<<< orphan*/ ) ; 
 int vb2_streamon (TYPE_3__*,int) ; 
 struct vsp1_pipeline* vsp1_video_pipeline_get (struct vsp1_video*) ; 
 int /*<<< orphan*/  vsp1_video_pipeline_put (struct vsp1_pipeline*) ; 
 int vsp1_video_verify_format (struct vsp1_video*) ; 

__attribute__((used)) static int
vsp1_video_streamon(struct file *file, void *fh, enum v4l2_buf_type type)
{
	struct v4l2_fh *vfh = file->private_data;
	struct vsp1_video *video = to_vsp1_video(vfh->vdev);
	struct media_device *mdev = &video->vsp1->media_dev;
	struct vsp1_pipeline *pipe;
	int ret;

	if (video->queue.owner && video->queue.owner != file->private_data)
		return -EBUSY;

	/*
	 * Get a pipeline for the video node and start streaming on it. No link
	 * touching an entity in the pipeline can be activated or deactivated
	 * once streaming is started.
	 */
	mutex_lock(&mdev->graph_mutex);

	pipe = vsp1_video_pipeline_get(video);
	if (IS_ERR(pipe)) {
		mutex_unlock(&mdev->graph_mutex);
		return PTR_ERR(pipe);
	}

	ret = __media_pipeline_start(&video->video.entity, &pipe->pipe);
	if (ret < 0) {
		mutex_unlock(&mdev->graph_mutex);
		goto err_pipe;
	}

	mutex_unlock(&mdev->graph_mutex);

	/*
	 * Verify that the configured format matches the output of the connected
	 * subdev.
	 */
	ret = vsp1_video_verify_format(video);
	if (ret < 0)
		goto err_stop;

	/* Start the queue. */
	ret = vb2_streamon(&video->queue, type);
	if (ret < 0)
		goto err_stop;

	return 0;

err_stop:
	media_pipeline_stop(&video->video.entity);
err_pipe:
	vsp1_video_pipeline_put(pipe);
	return ret;
}