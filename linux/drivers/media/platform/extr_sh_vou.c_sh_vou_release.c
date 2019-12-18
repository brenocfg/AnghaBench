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
struct sh_vou_device {int /*<<< orphan*/  fop_lock; TYPE_1__ v4l2_dev; int /*<<< orphan*/  status; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SH_VOU_INITIALISING ; 
 int /*<<< orphan*/  VOUER ; 
 int /*<<< orphan*/  _vb2_fop_release (struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_vou_reg_a_set (struct sh_vou_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int v4l2_fh_is_singular_file (struct file*) ; 
 struct sh_vou_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int sh_vou_release(struct file *file)
{
	struct sh_vou_device *vou_dev = video_drvdata(file);
	bool is_last;

	mutex_lock(&vou_dev->fop_lock);
	is_last = v4l2_fh_is_singular_file(file);
	_vb2_fop_release(file, NULL);
	if (is_last) {
		/* Last close */
		vou_dev->status = SH_VOU_INITIALISING;
		sh_vou_reg_a_set(vou_dev, VOUER, 0, 0x101);
		pm_runtime_put(vou_dev->v4l2_dev.dev);
	}
	mutex_unlock(&vou_dev->fop_lock);
	return 0;
}