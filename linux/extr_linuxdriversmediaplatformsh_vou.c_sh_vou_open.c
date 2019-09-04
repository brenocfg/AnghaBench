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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct sh_vou_device {scalar_t__ status; int /*<<< orphan*/  fop_lock; TYPE_1__ v4l2_dev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 scalar_t__ SH_VOU_IDLE ; 
 scalar_t__ SH_VOU_INITIALISING ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int sh_vou_hw_init (struct sh_vou_device*) ; 
 scalar_t__ v4l2_fh_is_singular_file (struct file*) ; 
 int v4l2_fh_open (struct file*) ; 
 int /*<<< orphan*/  v4l2_fh_release (struct file*) ; 
 struct sh_vou_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int sh_vou_open(struct file *file)
{
	struct sh_vou_device *vou_dev = video_drvdata(file);
	int err;

	if (mutex_lock_interruptible(&vou_dev->fop_lock))
		return -ERESTARTSYS;

	err = v4l2_fh_open(file);
	if (err)
		goto done_open;
	if (v4l2_fh_is_singular_file(file) &&
	    vou_dev->status == SH_VOU_INITIALISING) {
		/* First open */
		pm_runtime_get_sync(vou_dev->v4l2_dev.dev);
		err = sh_vou_hw_init(vou_dev);
		if (err < 0) {
			pm_runtime_put(vou_dev->v4l2_dev.dev);
			v4l2_fh_release(file);
		} else {
			vou_dev->status = SH_VOU_IDLE;
		}
	}
done_open:
	mutex_unlock(&vou_dev->fop_lock);
	return err;
}