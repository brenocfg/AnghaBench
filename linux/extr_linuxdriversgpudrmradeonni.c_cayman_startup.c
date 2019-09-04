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
typedef  scalar_t__ u32 ;
struct radeon_ring {int /*<<< orphan*/  ring_size; } ;
struct TYPE_6__ {int /*<<< orphan*/  installed; } ;
struct TYPE_5__ {int /*<<< orphan*/  cs_data; scalar_t__ reg_list_size; int /*<<< orphan*/  reg_list; } ;
struct TYPE_4__ {int /*<<< orphan*/  dpm_enabled; } ;
struct radeon_device {int flags; int /*<<< orphan*/  dev; struct radeon_ring* ring; TYPE_3__ irq; TYPE_2__ rlc; TYPE_1__ pm; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 size_t CAYMAN_RING_TYPE_CP1_INDEX ; 
 size_t CAYMAN_RING_TYPE_CP2_INDEX ; 
 size_t CAYMAN_RING_TYPE_DMA1_INDEX ; 
 int /*<<< orphan*/  CAYMAN_WB_DMA1_RPTR_OFFSET ; 
 int /*<<< orphan*/  DMA_PACKET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_PACKET_NOP ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 size_t R600_RING_TYPE_DMA_INDEX ; 
 int /*<<< orphan*/  R600_WB_DMA_RPTR_OFFSET ; 
 int /*<<< orphan*/  RADEON_CP_PACKET2 ; 
 int RADEON_IS_IGP ; 
 size_t RADEON_RING_TYPE_GFX_INDEX ; 
 int /*<<< orphan*/  RADEON_WB_CP_RPTR_OFFSET ; 
 int cayman_cp_load_microcode (struct radeon_device*) ; 
 int cayman_cp_resume (struct radeon_device*) ; 
 int /*<<< orphan*/  cayman_cs_data ; 
 int cayman_dma_resume (struct radeon_device*) ; 
 int /*<<< orphan*/  cayman_gpu_init (struct radeon_device*) ; 
 int cayman_pcie_gart_enable (struct radeon_device*) ; 
 int /*<<< orphan*/  cayman_uvd_resume (struct radeon_device*) ; 
 int /*<<< orphan*/  cayman_uvd_start (struct radeon_device*) ; 
 int /*<<< orphan*/  cayman_vce_resume (struct radeon_device*) ; 
 int /*<<< orphan*/  cayman_vce_start (struct radeon_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  evergreen_irq_set (struct radeon_device*) ; 
 int /*<<< orphan*/  evergreen_mc_program (struct radeon_device*) ; 
 int /*<<< orphan*/  evergreen_pcie_gen2_enable (struct radeon_device*) ; 
 int /*<<< orphan*/  evergreen_program_aspm (struct radeon_device*) ; 
 int ni_mc_load_microcode (struct radeon_device*) ; 
 int r600_irq_init (struct radeon_device*) ; 
 int r600_vram_scratch_init (struct radeon_device*) ; 
 int radeon_audio_init (struct radeon_device*) ; 
 int radeon_fence_driver_start_ring (struct radeon_device*,size_t) ; 
 int radeon_ib_pool_init (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_irq_kms_fini (struct radeon_device*) ; 
 int radeon_irq_kms_init (struct radeon_device*) ; 
 int radeon_ring_init (struct radeon_device*,struct radeon_ring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int radeon_vm_manager_init (struct radeon_device*) ; 
 int radeon_wb_init (struct radeon_device*) ; 
 int sumo_rlc_init (struct radeon_device*) ; 
 int /*<<< orphan*/  tn_rlc_save_restore_register_list ; 

__attribute__((used)) static int cayman_startup(struct radeon_device *rdev)
{
	struct radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	int r;

	/* enable pcie gen2 link */
	evergreen_pcie_gen2_enable(rdev);
	/* enable aspm */
	evergreen_program_aspm(rdev);

	/* scratch needs to be initialized before MC */
	r = r600_vram_scratch_init(rdev);
	if (r)
		return r;

	evergreen_mc_program(rdev);

	if (!(rdev->flags & RADEON_IS_IGP) && !rdev->pm.dpm_enabled) {
		r = ni_mc_load_microcode(rdev);
		if (r) {
			DRM_ERROR("Failed to load MC firmware!\n");
			return r;
		}
	}

	r = cayman_pcie_gart_enable(rdev);
	if (r)
		return r;
	cayman_gpu_init(rdev);

	/* allocate rlc buffers */
	if (rdev->flags & RADEON_IS_IGP) {
		rdev->rlc.reg_list = tn_rlc_save_restore_register_list;
		rdev->rlc.reg_list_size =
			(u32)ARRAY_SIZE(tn_rlc_save_restore_register_list);
		rdev->rlc.cs_data = cayman_cs_data;
		r = sumo_rlc_init(rdev);
		if (r) {
			DRM_ERROR("Failed to init rlc BOs!\n");
			return r;
		}
	}

	/* allocate wb buffer */
	r = radeon_wb_init(rdev);
	if (r)
		return r;

	r = radeon_fence_driver_start_ring(rdev, RADEON_RING_TYPE_GFX_INDEX);
	if (r) {
		dev_err(rdev->dev, "failed initializing CP fences (%d).\n", r);
		return r;
	}

	cayman_uvd_start(rdev);
	cayman_vce_start(rdev);

	r = radeon_fence_driver_start_ring(rdev, CAYMAN_RING_TYPE_CP1_INDEX);
	if (r) {
		dev_err(rdev->dev, "failed initializing CP fences (%d).\n", r);
		return r;
	}

	r = radeon_fence_driver_start_ring(rdev, CAYMAN_RING_TYPE_CP2_INDEX);
	if (r) {
		dev_err(rdev->dev, "failed initializing CP fences (%d).\n", r);
		return r;
	}

	r = radeon_fence_driver_start_ring(rdev, R600_RING_TYPE_DMA_INDEX);
	if (r) {
		dev_err(rdev->dev, "failed initializing DMA fences (%d).\n", r);
		return r;
	}

	r = radeon_fence_driver_start_ring(rdev, CAYMAN_RING_TYPE_DMA1_INDEX);
	if (r) {
		dev_err(rdev->dev, "failed initializing DMA fences (%d).\n", r);
		return r;
	}

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
	evergreen_irq_set(rdev);

	r = radeon_ring_init(rdev, ring, ring->ring_size, RADEON_WB_CP_RPTR_OFFSET,
			     RADEON_CP_PACKET2);
	if (r)
		return r;

	ring = &rdev->ring[R600_RING_TYPE_DMA_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, R600_WB_DMA_RPTR_OFFSET,
			     DMA_PACKET(DMA_PACKET_NOP, 0, 0, 0));
	if (r)
		return r;

	ring = &rdev->ring[CAYMAN_RING_TYPE_DMA1_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, CAYMAN_WB_DMA1_RPTR_OFFSET,
			     DMA_PACKET(DMA_PACKET_NOP, 0, 0, 0));
	if (r)
		return r;

	r = cayman_cp_load_microcode(rdev);
	if (r)
		return r;
	r = cayman_cp_resume(rdev);
	if (r)
		return r;

	r = cayman_dma_resume(rdev);
	if (r)
		return r;

	cayman_uvd_resume(rdev);
	cayman_vce_resume(rdev);

	r = radeon_ib_pool_init(rdev);
	if (r) {
		dev_err(rdev->dev, "IB initialization failed (%d).\n", r);
		return r;
	}

	r = radeon_vm_manager_init(rdev);
	if (r) {
		dev_err(rdev->dev, "vm manager initialization failed (%d).\n", r);
		return r;
	}

	r = radeon_audio_init(rdev);
	if (r)
		return r;

	return 0;
}