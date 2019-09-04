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
struct rvin_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; TYPE_1__ vdev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int _vb2_fop_release (struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_pipeline_pm_use (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rvin_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int rvin_mc_release(struct file *file)
{
	struct rvin_dev *vin = video_drvdata(file);
	int ret;

	mutex_lock(&vin->lock);

	/* the release helper will cleanup any on-going streaming. */
	ret = _vb2_fop_release(file, NULL);

	v4l2_pipeline_pm_use(&vin->vdev.entity, 0);
	pm_runtime_put(vin->dev);

	mutex_unlock(&vin->lock);

	return ret;
}