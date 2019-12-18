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
struct TYPE_2__ {int /*<<< orphan*/  entity; } ;
struct sun6i_video {int /*<<< orphan*/  lock; int /*<<< orphan*/  csi; TYPE_1__ vdev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _vb2_fop_release (struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sun6i_csi_set_power (int /*<<< orphan*/ ,int) ; 
 int v4l2_fh_is_singular_file (struct file*) ; 
 int /*<<< orphan*/  v4l2_pipeline_pm_use (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sun6i_video* video_drvdata (struct file*) ; 

__attribute__((used)) static int sun6i_video_close(struct file *file)
{
	struct sun6i_video *video = video_drvdata(file);
	bool last_fh;

	mutex_lock(&video->lock);

	last_fh = v4l2_fh_is_singular_file(file);

	_vb2_fop_release(file, NULL);

	v4l2_pipeline_pm_use(&video->vdev.entity, 0);

	if (last_fh)
		sun6i_csi_set_power(video->csi, false);

	mutex_unlock(&video->lock);

	return 0;
}