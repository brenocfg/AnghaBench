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
struct mdev_device {int dummy; } ;
struct intel_vgpu {int /*<<< orphan*/  handle; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* vgpu_destroy ) (struct intel_vgpu*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ handle_valid (int /*<<< orphan*/ ) ; 
 TYPE_1__* intel_gvt_ops ; 
 struct intel_vgpu* mdev_get_drvdata (struct mdev_device*) ; 
 int /*<<< orphan*/  stub1 (struct intel_vgpu*) ; 

__attribute__((used)) static int intel_vgpu_remove(struct mdev_device *mdev)
{
	struct intel_vgpu *vgpu = mdev_get_drvdata(mdev);

	if (handle_valid(vgpu->handle))
		return -EBUSY;

	intel_gvt_ops->vgpu_destroy(vgpu);
	return 0;
}