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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct amdgpu_ring {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ring_lock; struct amdgpu_ring ring; } ;
struct TYPE_4__ {TYPE_1__ kiq; } ;
struct amdgpu_device {int /*<<< orphan*/  usec_timeout; TYPE_2__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,long) ; 
 int ETIME ; 
 int PACKET3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PACKET3_INVALIDATE_TLBS ; 
 int PACKET3_INVALIDATE_TLBS_DST_SEL (int) ; 
 int PACKET3_INVALIDATE_TLBS_PASID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_fence_emit_polling (struct amdgpu_ring*,int /*<<< orphan*/ *) ; 
 long amdgpu_fence_wait_polling (struct amdgpu_ring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ring_alloc (struct amdgpu_ring*,int) ; 
 int /*<<< orphan*/  amdgpu_ring_commit (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int invalidate_tlbs_with_kiq(struct amdgpu_device *adev, uint16_t pasid)
{
	signed long r;
	uint32_t seq;
	struct amdgpu_ring *ring = &adev->gfx.kiq.ring;

	spin_lock(&adev->gfx.kiq.ring_lock);
	amdgpu_ring_alloc(ring, 12); /* fence + invalidate_tlbs package*/
	amdgpu_ring_write(ring, PACKET3(PACKET3_INVALIDATE_TLBS, 0));
	amdgpu_ring_write(ring,
			PACKET3_INVALIDATE_TLBS_DST_SEL(1) |
			PACKET3_INVALIDATE_TLBS_PASID(pasid));
	amdgpu_fence_emit_polling(ring, &seq);
	amdgpu_ring_commit(ring);
	spin_unlock(&adev->gfx.kiq.ring_lock);

	r = amdgpu_fence_wait_polling(ring, seq, adev->usec_timeout);
	if (r < 1) {
		DRM_ERROR("wait for kiq fence error: %ld.\n", r);
		return -ETIME;
	}

	return 0;
}