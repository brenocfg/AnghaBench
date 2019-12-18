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
struct TYPE_2__ {int /*<<< orphan*/  vfio_device; int /*<<< orphan*/  mdev; } ;
struct intel_vgpu {TYPE_1__ vdev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*) ; 
 int /*<<< orphan*/  mdev_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfio_device_get_from_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvmgt_get_vfio_device(void *p_vgpu)
{
	struct intel_vgpu *vgpu = (struct intel_vgpu *)p_vgpu;

	vgpu->vdev.vfio_device = vfio_device_get_from_dev(
		mdev_dev(vgpu->vdev.mdev));
	if (!vgpu->vdev.vfio_device) {
		gvt_vgpu_err("failed to get vfio device\n");
		return -ENODEV;
	}
	return 0;
}