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
struct file {int dummy; } ;
struct TYPE_2__ {struct video_device* vfd; } ;
struct capture_priv {int /*<<< orphan*/  mutex; int /*<<< orphan*/  src_sd; TYPE_1__ vdev; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ ,char*) ; 
 int v4l2_fh_open (struct file*) ; 
 int /*<<< orphan*/  v4l2_fh_release (struct file*) ; 
 int v4l2_pipeline_pm_use (int /*<<< orphan*/ *,int) ; 
 struct capture_priv* video_drvdata (struct file*) ; 

__attribute__((used)) static int capture_open(struct file *file)
{
	struct capture_priv *priv = video_drvdata(file);
	struct video_device *vfd = priv->vdev.vfd;
	int ret;

	if (mutex_lock_interruptible(&priv->mutex))
		return -ERESTARTSYS;

	ret = v4l2_fh_open(file);
	if (ret)
		v4l2_err(priv->src_sd, "v4l2_fh_open failed\n");

	ret = v4l2_pipeline_pm_use(&vfd->entity, 1);
	if (ret)
		v4l2_fh_release(file);

	mutex_unlock(&priv->mutex);
	return ret;
}