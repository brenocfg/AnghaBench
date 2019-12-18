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
struct TYPE_6__ {int ready; } ;
struct amdgpu_ring {TYPE_3__ sched; } ;
struct TYPE_5__ {TYPE_1__* inst; } ;
struct amdgpu_device {TYPE_2__ uvd; } ;
struct TYPE_4__ {struct amdgpu_ring ring; } ;

/* Variables and functions */
 scalar_t__ RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmUVD_STATUS ; 
 int /*<<< orphan*/  uvd_v5_0_stop (struct amdgpu_device*) ; 

__attribute__((used)) static int uvd_v5_0_hw_fini(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct amdgpu_ring *ring = &adev->uvd.inst->ring;

	if (RREG32(mmUVD_STATUS) != 0)
		uvd_v5_0_stop(adev);

	ring->sched.ready = false;

	return 0;
}