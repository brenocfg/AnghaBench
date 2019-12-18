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
struct mdev_device {int dummy; } ;
struct kobject {int dummy; } ;
struct intel_vgpu_type {int dummy; } ;
struct TYPE_4__ {struct mdev_device* mdev; int /*<<< orphan*/  release_work; } ;
struct intel_vgpu {TYPE_1__ vdev; } ;
struct device {int dummy; } ;
struct TYPE_6__ {struct intel_vgpu* (* vgpu_create ) (void*,struct intel_vgpu_type*) ;struct intel_vgpu_type* (* gvt_find_vgpu_type ) (void*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {void* gvt; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR_OR_NULL (struct intel_vgpu*) ; 
 int PTR_ERR (struct intel_vgpu*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gvt_dbg_core (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gvt_err (char*,int) ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* intel_gvt_ops ; 
 int /*<<< orphan*/  intel_vgpu_release_work ; 
 TYPE_2__* kdev_to_i915 (struct device*) ; 
 int /*<<< orphan*/  kobject_name (struct kobject*) ; 
 int /*<<< orphan*/  mdev_dev (struct mdev_device*) ; 
 struct device* mdev_parent_dev (struct mdev_device*) ; 
 int /*<<< orphan*/  mdev_set_drvdata (struct mdev_device*,struct intel_vgpu*) ; 
 struct intel_vgpu_type* stub1 (void*,int /*<<< orphan*/ ) ; 
 struct intel_vgpu* stub2 (void*,struct intel_vgpu_type*) ; 

__attribute__((used)) static int intel_vgpu_create(struct kobject *kobj, struct mdev_device *mdev)
{
	struct intel_vgpu *vgpu = NULL;
	struct intel_vgpu_type *type;
	struct device *pdev;
	void *gvt;
	int ret;

	pdev = mdev_parent_dev(mdev);
	gvt = kdev_to_i915(pdev)->gvt;

	type = intel_gvt_ops->gvt_find_vgpu_type(gvt, kobject_name(kobj));
	if (!type) {
		gvt_vgpu_err("failed to find type %s to create\n",
						kobject_name(kobj));
		ret = -EINVAL;
		goto out;
	}

	vgpu = intel_gvt_ops->vgpu_create(gvt, type);
	if (IS_ERR_OR_NULL(vgpu)) {
		ret = vgpu == NULL ? -EFAULT : PTR_ERR(vgpu);
		gvt_err("failed to create intel vgpu: %d\n", ret);
		goto out;
	}

	INIT_WORK(&vgpu->vdev.release_work, intel_vgpu_release_work);

	vgpu->vdev.mdev = mdev;
	mdev_set_drvdata(mdev, vgpu);

	gvt_dbg_core("intel_vgpu_create succeeded for mdev: %s\n",
		     dev_name(mdev_dev(mdev)));
	ret = 0;

out:
	return ret;
}