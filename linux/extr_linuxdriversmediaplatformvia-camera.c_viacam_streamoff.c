#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct via_camera {scalar_t__ opstate; int /*<<< orphan*/  lock; int /*<<< orphan*/  buffer_queue; int /*<<< orphan*/  vb_queue; int /*<<< orphan*/  qos_request; } ;
struct file {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ S_RUNNING ; 
 int V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_qos_remove_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  viacam_stop_engine (struct via_camera*) ; 
 int videobuf_streamoff (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int viacam_streamoff(struct file *filp, void *priv, enum v4l2_buf_type t)
{
	struct via_camera *cam = priv;
	int ret;

	if (t != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;
	mutex_lock(&cam->lock);
	if (cam->opstate != S_RUNNING) {
		ret = -EINVAL;
		goto out;
	}
	pm_qos_remove_request(&cam->qos_request);
	viacam_stop_engine(cam);
	/*
	 * Videobuf will recycle all of the outstanding buffers, but
	 * we should be sure we don't retain any references to
	 * any of them.
	 */
	ret = videobuf_streamoff(&cam->vb_queue);
	INIT_LIST_HEAD(&cam->buffer_queue);
out:
	mutex_unlock(&cam->lock);
	return ret;
}