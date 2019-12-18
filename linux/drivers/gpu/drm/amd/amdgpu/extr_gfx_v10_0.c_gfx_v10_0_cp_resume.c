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
struct amdgpu_ring {TYPE_3__ sched; int /*<<< orphan*/  queue; int /*<<< orphan*/  pipe; int /*<<< orphan*/  me; } ;
struct TYPE_5__ {int num_gfx_rings; int num_compute_rings; struct amdgpu_ring* compute_ring; struct amdgpu_ring* gfx_ring; } ;
struct TYPE_4__ {scalar_t__ load_type; } ;
struct amdgpu_device {int flags; TYPE_2__ gfx; TYPE_1__ firmware; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_FW_LOAD_DIRECT ; 
 int AMD_IS_APU ; 
 int /*<<< orphan*/  DRM_INFO (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_async_gfx_ring ; 
 int amdgpu_ring_test_ring (struct amdgpu_ring*) ; 
 int gfx_v10_0_cp_async_gfx_ring_resume (struct amdgpu_device*) ; 
 int gfx_v10_0_cp_compute_load_microcode (struct amdgpu_device*) ; 
 int gfx_v10_0_cp_gfx_load_microcode (struct amdgpu_device*) ; 
 int gfx_v10_0_cp_gfx_resume (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v10_0_enable_gui_idle_interrupt (struct amdgpu_device*,int) ; 
 int gfx_v10_0_kcq_resume (struct amdgpu_device*) ; 
 int gfx_v10_0_kiq_resume (struct amdgpu_device*) ; 

__attribute__((used)) static int gfx_v10_0_cp_resume(struct amdgpu_device *adev)
{
	int r, i;
	struct amdgpu_ring *ring;

	if (!(adev->flags & AMD_IS_APU))
		gfx_v10_0_enable_gui_idle_interrupt(adev, false);

	if (adev->firmware.load_type == AMDGPU_FW_LOAD_DIRECT) {
		/* legacy firmware loading */
		r = gfx_v10_0_cp_gfx_load_microcode(adev);
		if (r)
			return r;

		r = gfx_v10_0_cp_compute_load_microcode(adev);
		if (r)
			return r;
	}

	r = gfx_v10_0_kiq_resume(adev);
	if (r)
		return r;

	r = gfx_v10_0_kcq_resume(adev);
	if (r)
		return r;

	if (!amdgpu_async_gfx_ring) {
		r = gfx_v10_0_cp_gfx_resume(adev);
		if (r)
			return r;
	} else {
		r = gfx_v10_0_cp_async_gfx_ring_resume(adev);
		if (r)
			return r;
	}

	for (i = 0; i < adev->gfx.num_gfx_rings; i++) {
		ring = &adev->gfx.gfx_ring[i];
		DRM_INFO("gfx %d ring me %d pipe %d q %d\n",
			 i, ring->me, ring->pipe, ring->queue);
		r = amdgpu_ring_test_ring(ring);
		if (r) {
			ring->sched.ready = false;
			return r;
		}
	}

	for (i = 0; i < adev->gfx.num_compute_rings; i++) {
		ring = &adev->gfx.compute_ring[i];
		ring->sched.ready = true;
		DRM_INFO("compute ring %d mec %d pipe %d q %d\n",
			 i, ring->me, ring->pipe, ring->queue);
		r = amdgpu_ring_test_ring(ring);
		if (r)
			ring->sched.ready = false;
	}

	return 0;
}