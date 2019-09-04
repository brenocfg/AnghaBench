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
struct TYPE_2__ {int /*<<< orphan*/  vfio_device; } ;
struct intel_vgpu {TYPE_1__ vdev; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  vfio_device_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvmgt_put_vfio_device(void *vgpu)
{
	if (WARN_ON(!((struct intel_vgpu *)vgpu)->vdev.vfio_device))
		return;

	vfio_device_put(((struct intel_vgpu *)vgpu)->vdev.vfio_device);
}