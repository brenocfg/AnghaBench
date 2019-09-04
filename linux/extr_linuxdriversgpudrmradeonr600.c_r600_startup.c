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
struct radeon_ring {int /*<<< orphan*/  ring_size; } ;
struct TYPE_2__ {int /*<<< orphan*/  installed; } ;
struct radeon_device {int flags; int /*<<< orphan*/  dev; struct radeon_ring* ring; TYPE_1__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  RADEON_CP_PACKET2 ; 
 int RADEON_IS_AGP ; 
 size_t RADEON_RING_TYPE_GFX_INDEX ; 
 int /*<<< orphan*/  RADEON_WB_CP_RPTR_OFFSET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  r600_agp_enable (struct radeon_device*) ; 
 int r600_cp_load_microcode (struct radeon_device*) ; 
 int r600_cp_resume (struct radeon_device*) ; 
 int /*<<< orphan*/  r600_gpu_init (struct radeon_device*) ; 
 int r600_irq_init (struct radeon_device*) ; 
 int /*<<< orphan*/  r600_irq_set (struct radeon_device*) ; 
 int /*<<< orphan*/  r600_mc_program (struct radeon_device*) ; 
 int r600_pcie_gart_enable (struct radeon_device*) ; 
 int /*<<< orphan*/  r600_pcie_gen2_enable (struct radeon_device*) ; 
 int /*<<< orphan*/  r600_uvd_resume (struct radeon_device*) ; 
 int /*<<< orphan*/  r600_uvd_start (struct radeon_device*) ; 
 int r600_vram_scratch_init (struct radeon_device*) ; 
 int radeon_audio_init (struct radeon_device*) ; 
 int radeon_fence_driver_start_ring (struct radeon_device*,size_t) ; 
 int radeon_ib_pool_init (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_irq_kms_fini (struct radeon_device*) ; 
 int radeon_irq_kms_init (struct radeon_device*) ; 
 int radeon_ring_init (struct radeon_device*,struct radeon_ring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int radeon_wb_init (struct radeon_device*) ; 

__attribute__((used)) static int r600_startup(struct radeon_device *rdev)
{
	struct radeon_ring *ring;
	int r;

	/* enable pcie gen2 link */
	r600_pcie_gen2_enable(rdev);

	/* scratch needs to be initialized before MC */
	r = r600_vram_scratch_init(rdev);
	if (r)
		return r;

	r600_mc_program(rdev);

	if (rdev->flags & RADEON_IS_AGP) {
		r600_agp_enable(rdev);
	} else {
		r = r600_pcie_gart_enable(rdev);
		if (r)
			return r;
	}
	r600_gpu_init(rdev);

	/* allocate wb buffer */
	r = radeon_wb_init(rdev);
	if (r)
		return r;

	r = radeon_fence_driver_start_ring(rdev, RADEON_RING_TYPE_GFX_INDEX);
	if (r) {
		dev_err(rdev->dev, "failed initializing CP fences (%d).\n", r);
		return r;
	}

	r600_uvd_start(rdev);

	/* Enable IRQ */
	if (!rdev->irq.installed) {
		r = radeon_irq_kms_init(rdev);
		if (r)
			return r;
	}

	r = r600_irq_init(rdev);
	if (r) {
		DRM_ERROR("radeon: IH init failed (%d).\n", r);
		radeon_irq_kms_fini(rdev);
		return r;
	}
	r600_irq_set(rdev);

	ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, RADEON_WB_CP_RPTR_OFFSET,
			     RADEON_CP_PACKET2);
	if (r)
		return r;

	r = r600_cp_load_microcode(rdev);
	if (r)
		return r;
	r = r600_cp_resume(rdev);
	if (r)
		return r;

	r600_uvd_resume(rdev);

	r = radeon_ib_pool_init(rdev);
	if (r) {
		dev_err(rdev->dev, "IB initialization failed (%d).\n", r);
		return r;
	}

	r = radeon_audio_init(rdev);
	if (r) {
		DRM_ERROR("radeon: audio init failed\n");
		return r;
	}

	return 0;
}