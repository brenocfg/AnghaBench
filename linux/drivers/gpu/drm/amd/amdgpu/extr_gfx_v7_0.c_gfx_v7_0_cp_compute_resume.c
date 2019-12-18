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
typedef  int u32 ;
struct amdgpu_ring {int dummy; } ;
struct TYPE_3__ {int num_mec; int num_pipe_per_mec; } ;
struct TYPE_4__ {int num_compute_rings; struct amdgpu_ring* compute_ring; TYPE_1__ mec; } ;
struct amdgpu_device {TYPE_2__ gfx; } ;

/* Variables and functions */
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  amdgpu_ring_test_helper (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  gfx_v7_0_compute_pipe_init (struct amdgpu_device*,int,int) ; 
 int gfx_v7_0_compute_queue_init (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v7_0_cp_compute_enable (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v7_0_cp_compute_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmCP_CPF_DEBUG ; 

__attribute__((used)) static int gfx_v7_0_cp_compute_resume(struct amdgpu_device *adev)
{
	int r, i, j;
	u32 tmp;
	struct amdgpu_ring *ring;

	/* fix up chicken bits */
	tmp = RREG32(mmCP_CPF_DEBUG);
	tmp |= (1 << 23);
	WREG32(mmCP_CPF_DEBUG, tmp);

	/* init all pipes (even the ones we don't own) */
	for (i = 0; i < adev->gfx.mec.num_mec; i++)
		for (j = 0; j < adev->gfx.mec.num_pipe_per_mec; j++)
			gfx_v7_0_compute_pipe_init(adev, i, j);

	/* init the queues */
	for (i = 0; i < adev->gfx.num_compute_rings; i++) {
		r = gfx_v7_0_compute_queue_init(adev, i);
		if (r) {
			gfx_v7_0_cp_compute_fini(adev);
			return r;
		}
	}

	gfx_v7_0_cp_compute_enable(adev, true);

	for (i = 0; i < adev->gfx.num_compute_rings; i++) {
		ring = &adev->gfx.compute_ring[i];
		amdgpu_ring_test_helper(ring);
	}

	return 0;
}