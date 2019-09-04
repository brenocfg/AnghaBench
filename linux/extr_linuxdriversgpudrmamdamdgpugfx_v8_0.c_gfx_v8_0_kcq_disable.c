#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
struct amdgpu_ring {int /*<<< orphan*/  doorbell_index; struct amdgpu_device* adev; } ;
struct amdgpu_device {int usec_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int,...) ; 
 int /*<<< orphan*/  DRM_UDELAY (int) ; 
 int EINVAL ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_SET_UCONFIG_REG ; 
 int PACKET3_SET_UCONFIG_REG_START ; 
 int /*<<< orphan*/  PACKET3_UNMAP_QUEUES ; 
 int PACKET3_UNMAP_QUEUES_ACTION (int) ; 
 int PACKET3_UNMAP_QUEUES_DOORBELL_OFFSET0 (int /*<<< orphan*/ ) ; 
 int PACKET3_UNMAP_QUEUES_ENGINE_SEL (int /*<<< orphan*/ ) ; 
 int PACKET3_UNMAP_QUEUES_NUM_QUEUES (int) ; 
 int PACKET3_UNMAP_QUEUES_QUEUE_SEL (int /*<<< orphan*/ ) ; 
 int RREG32 (int) ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int /*<<< orphan*/  amdgpu_gfx_scratch_free (struct amdgpu_device*,int) ; 
 int amdgpu_gfx_scratch_get (struct amdgpu_device*,int*) ; 
 int amdgpu_ring_alloc (struct amdgpu_ring*,int) ; 
 int /*<<< orphan*/  amdgpu_ring_commit (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 

__attribute__((used)) static int gfx_v8_0_kcq_disable(struct amdgpu_ring *kiq_ring,struct amdgpu_ring *ring)
{
	struct amdgpu_device *adev = kiq_ring->adev;
	uint32_t scratch, tmp = 0;
	int r, i;

	r = amdgpu_gfx_scratch_get(adev, &scratch);
	if (r) {
		DRM_ERROR("Failed to get scratch reg (%d).\n", r);
		return r;
	}
	WREG32(scratch, 0xCAFEDEAD);

	r = amdgpu_ring_alloc(kiq_ring, 10);
	if (r) {
		DRM_ERROR("Failed to lock KIQ (%d).\n", r);
		amdgpu_gfx_scratch_free(adev, scratch);
		return r;
	}

	/* unmap queues */
	amdgpu_ring_write(kiq_ring, PACKET3(PACKET3_UNMAP_QUEUES, 4));
	amdgpu_ring_write(kiq_ring, /* Q_sel: 0, vmid: 0, engine: 0, num_Q: 1 */
						PACKET3_UNMAP_QUEUES_ACTION(1) | /* RESET_QUEUES */
						PACKET3_UNMAP_QUEUES_QUEUE_SEL(0) |
						PACKET3_UNMAP_QUEUES_ENGINE_SEL(0) |
						PACKET3_UNMAP_QUEUES_NUM_QUEUES(1));
	amdgpu_ring_write(kiq_ring, PACKET3_UNMAP_QUEUES_DOORBELL_OFFSET0(ring->doorbell_index));
	amdgpu_ring_write(kiq_ring, 0);
	amdgpu_ring_write(kiq_ring, 0);
	amdgpu_ring_write(kiq_ring, 0);
	/* write to scratch for completion */
	amdgpu_ring_write(kiq_ring, PACKET3(PACKET3_SET_UCONFIG_REG, 1));
	amdgpu_ring_write(kiq_ring, (scratch - PACKET3_SET_UCONFIG_REG_START));
	amdgpu_ring_write(kiq_ring, 0xDEADBEEF);
	amdgpu_ring_commit(kiq_ring);

	for (i = 0; i < adev->usec_timeout; i++) {
		tmp = RREG32(scratch);
		if (tmp == 0xDEADBEEF)
			break;
		DRM_UDELAY(1);
	}
	if (i >= adev->usec_timeout) {
		DRM_ERROR("KCQ disabled failed (scratch(0x%04X)=0x%08X)\n", scratch, tmp);
		r = -EINVAL;
	}
	amdgpu_gfx_scratch_free(adev, scratch);
	return r;
}