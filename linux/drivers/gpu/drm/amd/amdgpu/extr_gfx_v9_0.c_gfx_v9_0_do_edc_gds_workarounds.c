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
struct amdgpu_ring {scalar_t__ wptr; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int gds_size; } ;
struct TYPE_3__ {struct amdgpu_ring* compute_ring; } ;
struct amdgpu_device {int usec_timeout; TYPE_2__ gds; TYPE_1__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,int) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GC ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_DMA_DATA ; 
 int PACKET3_DMA_DATA_CMD_RAW_WAIT ; 
 int PACKET3_DMA_DATA_CP_SYNC ; 
 int PACKET3_DMA_DATA_DST_SEL (int) ; 
 int PACKET3_DMA_DATA_ENGINE (int /*<<< orphan*/ ) ; 
 int PACKET3_DMA_DATA_SRC_SEL (int) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int amdgpu_ring_alloc (struct amdgpu_ring*,int) ; 
 int /*<<< orphan*/  amdgpu_ring_commit (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 scalar_t__ gfx_v9_0_ring_get_rptr_compute (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  mmGDS_VMID0_BASE ; 
 int /*<<< orphan*/  mmGDS_VMID0_SIZE ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int gfx_v9_0_do_edc_gds_workarounds(struct amdgpu_device *adev)
{
	struct amdgpu_ring *ring = &adev->gfx.compute_ring[0];
	int i, r;

	r = amdgpu_ring_alloc(ring, 7);
	if (r) {
		DRM_ERROR("amdgpu: GDS workarounds failed to lock ring %s (%d).\n",
			ring->name, r);
		return r;
	}

	WREG32_SOC15(GC, 0, mmGDS_VMID0_BASE, 0x00000000);
	WREG32_SOC15(GC, 0, mmGDS_VMID0_SIZE, adev->gds.gds_size);

	amdgpu_ring_write(ring, PACKET3(PACKET3_DMA_DATA, 5));
	amdgpu_ring_write(ring, (PACKET3_DMA_DATA_CP_SYNC |
				PACKET3_DMA_DATA_DST_SEL(1) |
				PACKET3_DMA_DATA_SRC_SEL(2) |
				PACKET3_DMA_DATA_ENGINE(0)));
	amdgpu_ring_write(ring, 0);
	amdgpu_ring_write(ring, 0);
	amdgpu_ring_write(ring, 0);
	amdgpu_ring_write(ring, 0);
	amdgpu_ring_write(ring, PACKET3_DMA_DATA_CMD_RAW_WAIT |
				adev->gds.gds_size);

	amdgpu_ring_commit(ring);

	for (i = 0; i < adev->usec_timeout; i++) {
		if (ring->wptr == gfx_v9_0_ring_get_rptr_compute(ring))
			break;
		udelay(1);
	}

	if (i >= adev->usec_timeout)
		r = -ETIMEDOUT;

	WREG32_SOC15(GC, 0, mmGDS_VMID0_SIZE, 0x00000000);

	return r;
}