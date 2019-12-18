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
struct video_device {int /*<<< orphan*/  entity; } ;
struct vb2_queue {scalar_t__ owner; } ;
struct file {scalar_t__ private_data; } ;
struct TYPE_2__ {struct video_device* vfd; } ;
struct capture_priv {int /*<<< orphan*/  mutex; struct vb2_queue q; TYPE_1__ vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_release (struct file*) ; 
 int /*<<< orphan*/  v4l2_pipeline_pm_use (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_queue_release (struct vb2_queue*) ; 
 struct capture_priv* video_drvdata (struct file*) ; 

__attribute__((used)) static int capture_release(struct file *file)
{
	struct capture_priv *priv = video_drvdata(file);
	struct video_device *vfd = priv->vdev.vfd;
	struct vb2_queue *vq = &priv->q;

	mutex_lock(&priv->mutex);

	if (file->private_data == vq->owner) {
		vb2_queue_release(vq);
		vq->owner = NULL;
	}

	v4l2_pipeline_pm_use(&vfd->entity, 0);

	v4l2_fh_release(file);
	mutex_unlock(&priv->mutex);
	return 0;
}