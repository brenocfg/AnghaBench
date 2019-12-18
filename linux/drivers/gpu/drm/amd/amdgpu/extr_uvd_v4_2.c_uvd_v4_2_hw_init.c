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
typedef  int uint32_t ;
struct amdgpu_ring {int dummy; } ;
struct TYPE_4__ {TYPE_1__* inst; } ;
struct amdgpu_device {TYPE_2__ uvd; } ;
struct TYPE_3__ {struct amdgpu_ring ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_asic_set_uvd_clocks (struct amdgpu_device*,int,int) ; 
 int amdgpu_ring_alloc (struct amdgpu_ring*,int) ; 
 int /*<<< orphan*/  amdgpu_ring_commit (struct amdgpu_ring*) ; 
 int amdgpu_ring_test_helper (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int /*<<< orphan*/  mmUVD_SEMA_CNTL ; 
 int /*<<< orphan*/  mmUVD_SEMA_SIGNAL_INCOMPLETE_TIMEOUT_CNTL ; 
 int /*<<< orphan*/  mmUVD_SEMA_TIMEOUT_STATUS ; 
 int /*<<< orphan*/  mmUVD_SEMA_WAIT_FAULT_TIMEOUT_CNTL ; 
 int /*<<< orphan*/  mmUVD_SEMA_WAIT_INCOMPLETE_TIMEOUT_CNTL ; 
 int /*<<< orphan*/  uvd_v4_2_enable_mgcg (struct amdgpu_device*,int) ; 

__attribute__((used)) static int uvd_v4_2_hw_init(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct amdgpu_ring *ring = &adev->uvd.inst->ring;
	uint32_t tmp;
	int r;

	uvd_v4_2_enable_mgcg(adev, true);
	amdgpu_asic_set_uvd_clocks(adev, 10000, 10000);

	r = amdgpu_ring_test_helper(ring);
	if (r)
		goto done;

	r = amdgpu_ring_alloc(ring, 10);
	if (r) {
		DRM_ERROR("amdgpu: ring failed to lock UVD ring (%d).\n", r);
		goto done;
	}

	tmp = PACKET0(mmUVD_SEMA_WAIT_FAULT_TIMEOUT_CNTL, 0);
	amdgpu_ring_write(ring, tmp);
	amdgpu_ring_write(ring, 0xFFFFF);

	tmp = PACKET0(mmUVD_SEMA_WAIT_INCOMPLETE_TIMEOUT_CNTL, 0);
	amdgpu_ring_write(ring, tmp);
	amdgpu_ring_write(ring, 0xFFFFF);

	tmp = PACKET0(mmUVD_SEMA_SIGNAL_INCOMPLETE_TIMEOUT_CNTL, 0);
	amdgpu_ring_write(ring, tmp);
	amdgpu_ring_write(ring, 0xFFFFF);

	/* Clear timeout status bits */
	amdgpu_ring_write(ring, PACKET0(mmUVD_SEMA_TIMEOUT_STATUS, 0));
	amdgpu_ring_write(ring, 0x8);

	amdgpu_ring_write(ring, PACKET0(mmUVD_SEMA_CNTL, 0));
	amdgpu_ring_write(ring, 3);

	amdgpu_ring_commit(ring);

done:
	if (!r)
		DRM_INFO("UVD initialized successfully.\n");

	return r;
}