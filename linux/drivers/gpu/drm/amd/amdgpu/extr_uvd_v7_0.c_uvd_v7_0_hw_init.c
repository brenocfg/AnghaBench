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
struct TYPE_4__ {int num_uvd_inst; int harvest_config; int num_enc_rings; TYPE_1__* inst; } ;
struct amdgpu_device {TYPE_2__ uvd; } ;
struct TYPE_3__ {struct amdgpu_ring* ring_enc; struct amdgpu_ring ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int,int) ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UVD ; 
 int amdgpu_ring_alloc (struct amdgpu_ring*,int) ; 
 int /*<<< orphan*/  amdgpu_ring_commit (struct amdgpu_ring*) ; 
 int amdgpu_ring_test_helper (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmUVD_SEMA_CNTL ; 
 int /*<<< orphan*/  mmUVD_SEMA_SIGNAL_INCOMPLETE_TIMEOUT_CNTL ; 
 int /*<<< orphan*/  mmUVD_SEMA_TIMEOUT_STATUS ; 
 int /*<<< orphan*/  mmUVD_SEMA_WAIT_FAULT_TIMEOUT_CNTL ; 
 int /*<<< orphan*/  mmUVD_SEMA_WAIT_INCOMPLETE_TIMEOUT_CNTL ; 
 int uvd_v7_0_sriov_start (struct amdgpu_device*) ; 
 int uvd_v7_0_start (struct amdgpu_device*) ; 

__attribute__((used)) static int uvd_v7_0_hw_init(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct amdgpu_ring *ring;
	uint32_t tmp;
	int i, j, r;

	if (amdgpu_sriov_vf(adev))
		r = uvd_v7_0_sriov_start(adev);
	else
		r = uvd_v7_0_start(adev);
	if (r)
		goto done;

	for (j = 0; j < adev->uvd.num_uvd_inst; ++j) {
		if (adev->uvd.harvest_config & (1 << j))
			continue;
		ring = &adev->uvd.inst[j].ring;

		if (!amdgpu_sriov_vf(adev)) {
			r = amdgpu_ring_test_helper(ring);
			if (r)
				goto done;

			r = amdgpu_ring_alloc(ring, 10);
			if (r) {
				DRM_ERROR("amdgpu: (%d)ring failed to lock UVD ring (%d).\n", j, r);
				goto done;
			}

			tmp = PACKET0(SOC15_REG_OFFSET(UVD, j,
				mmUVD_SEMA_WAIT_FAULT_TIMEOUT_CNTL), 0);
			amdgpu_ring_write(ring, tmp);
			amdgpu_ring_write(ring, 0xFFFFF);

			tmp = PACKET0(SOC15_REG_OFFSET(UVD, j,
				mmUVD_SEMA_WAIT_INCOMPLETE_TIMEOUT_CNTL), 0);
			amdgpu_ring_write(ring, tmp);
			amdgpu_ring_write(ring, 0xFFFFF);

			tmp = PACKET0(SOC15_REG_OFFSET(UVD, j,
				mmUVD_SEMA_SIGNAL_INCOMPLETE_TIMEOUT_CNTL), 0);
			amdgpu_ring_write(ring, tmp);
			amdgpu_ring_write(ring, 0xFFFFF);

			/* Clear timeout status bits */
			amdgpu_ring_write(ring, PACKET0(SOC15_REG_OFFSET(UVD, j,
				mmUVD_SEMA_TIMEOUT_STATUS), 0));
			amdgpu_ring_write(ring, 0x8);

			amdgpu_ring_write(ring, PACKET0(SOC15_REG_OFFSET(UVD, j,
				mmUVD_SEMA_CNTL), 0));
			amdgpu_ring_write(ring, 3);

			amdgpu_ring_commit(ring);
		}

		for (i = 0; i < adev->uvd.num_enc_rings; ++i) {
			ring = &adev->uvd.inst[j].ring_enc[i];
			r = amdgpu_ring_test_helper(ring);
			if (r)
				goto done;
		}
	}
done:
	if (!r)
		DRM_INFO("UVD and UVD ENC initialized successfully.\n");

	return r;
}