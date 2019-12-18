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
struct TYPE_4__ {int /*<<< orphan*/  entity; } ;
struct rvin_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; TYPE_2__ vdev; TYPE_1__* info; } ;
struct file {int dummy; } ;
struct TYPE_3__ {scalar_t__ use_mc; } ;

/* Variables and functions */
 int _vb2_fop_release (struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvin_power_parallel (struct rvin_dev*,int) ; 
 int v4l2_fh_is_singular_file (struct file*) ; 
 int /*<<< orphan*/  v4l2_pipeline_pm_use (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rvin_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int rvin_release(struct file *file)
{
	struct rvin_dev *vin = video_drvdata(file);
	bool fh_singular;
	int ret;

	mutex_lock(&vin->lock);

	/* Save the singular status before we call the clean-up helper */
	fh_singular = v4l2_fh_is_singular_file(file);

	/* the release helper will cleanup any on-going streaming */
	ret = _vb2_fop_release(file, NULL);

	if (vin->info->use_mc) {
		v4l2_pipeline_pm_use(&vin->vdev.entity, 0);
	} else {
		if (fh_singular)
			rvin_power_parallel(vin, false);
	}

	mutex_unlock(&vin->lock);

	pm_runtime_put(vin->dev);

	return ret;
}