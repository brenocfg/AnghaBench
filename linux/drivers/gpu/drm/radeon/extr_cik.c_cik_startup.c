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
typedef  void* u32 ;
struct radeon_ring {int me; int queue; int /*<<< orphan*/  ring_size; int /*<<< orphan*/  wptr_offs; scalar_t__ pipe; } ;
struct TYPE_6__ {int /*<<< orphan*/  installed; } ;
struct TYPE_5__ {int cp_table_size; int /*<<< orphan*/  cs_data; void* reg_list_size; void* reg_list; } ;
struct TYPE_4__ {int /*<<< orphan*/  dpm_enabled; } ;
struct radeon_device {int flags; scalar_t__ family; int /*<<< orphan*/  dev; struct radeon_ring* ring; scalar_t__ new_fw; TYPE_3__ irq; TYPE_2__ rlc; TYPE_1__ pm; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 scalar_t__ ARRAY_SIZE (void*) ; 
 size_t CAYMAN_RING_TYPE_CP1_INDEX ; 
 size_t CAYMAN_RING_TYPE_CP2_INDEX ; 
 size_t CAYMAN_RING_TYPE_DMA1_INDEX ; 
 int /*<<< orphan*/  CAYMAN_WB_DMA1_RPTR_OFFSET ; 
 scalar_t__ CHIP_HAWAII ; 
 scalar_t__ CHIP_KAVERI ; 
 int /*<<< orphan*/  CIK_WB_CP1_WPTR_OFFSET ; 
 int /*<<< orphan*/  CIK_WB_CP2_WPTR_OFFSET ; 
 int CP_ME_TABLE_SIZE ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 void* PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_NOP ; 
 size_t R600_RING_TYPE_DMA_INDEX ; 
 int /*<<< orphan*/  R600_WB_DMA_RPTR_OFFSET ; 
 void* RADEON_CP_PACKET2 ; 
 int RADEON_IS_IGP ; 
 size_t RADEON_RING_TYPE_GFX_INDEX ; 
 int /*<<< orphan*/  RADEON_WB_CP1_RPTR_OFFSET ; 
 int /*<<< orphan*/  RADEON_WB_CP2_RPTR_OFFSET ; 
 int /*<<< orphan*/  RADEON_WB_CP_RPTR_OFFSET ; 
 int /*<<< orphan*/  SDMA_OPCODE_NOP ; 
 void* SDMA_PACKET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ci_cs_data ; 
 int ci_mc_load_microcode (struct radeon_device*) ; 
 int cik_cp_resume (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_gpu_init (struct radeon_device*) ; 
 int cik_irq_init (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_irq_set (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_mc_program (struct radeon_device*) ; 
 int cik_mec_init (struct radeon_device*) ; 
 int cik_pcie_gart_enable (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_pcie_gen3_enable (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_program_aspm (struct radeon_device*) ; 
 int cik_sdma_resume (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_uvd_resume (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_uvd_start (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_vce_resume (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_vce_start (struct radeon_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 void* kalindi_rlc_save_restore_register_list ; 
 int r600_vram_scratch_init (struct radeon_device*) ; 
 int radeon_audio_init (struct radeon_device*) ; 
 int radeon_fence_driver_start_ring (struct radeon_device*,size_t) ; 
 int radeon_ib_pool_init (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_irq_kms_fini (struct radeon_device*) ; 
 int radeon_irq_kms_init (struct radeon_device*) ; 
 int radeon_ring_init (struct radeon_device*,struct radeon_ring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int radeon_vm_manager_init (struct radeon_device*) ; 
 int radeon_wb_init (struct radeon_device*) ; 
 void* spectre_rlc_save_restore_register_list ; 
 int sumo_rlc_init (struct radeon_device*) ; 

__attribute__((used)) static int cik_startup(struct radeon_device *rdev)
{
	struct radeon_ring *ring;
	u32 nop;
	int r;

	/* enable pcie gen2/3 link */
	cik_pcie_gen3_enable(rdev);
	/* enable aspm */
	cik_program_aspm(rdev);

	/* scratch needs to be initialized before MC */
	r = r600_vram_scratch_init(rdev);
	if (r)
		return r;

	cik_mc_program(rdev);

	if (!(rdev->flags & RADEON_IS_IGP) && !rdev->pm.dpm_enabled) {
		r = ci_mc_load_microcode(rdev);
		if (r) {
			DRM_ERROR("Failed to load MC firmware!\n");
			return r;
		}
	}

	r = cik_pcie_gart_enable(rdev);
	if (r)
		return r;
	cik_gpu_init(rdev);

	/* allocate rlc buffers */
	if (rdev->flags & RADEON_IS_IGP) {
		if (rdev->family == CHIP_KAVERI) {
			rdev->rlc.reg_list = spectre_rlc_save_restore_register_list;
			rdev->rlc.reg_list_size =
				(u32)ARRAY_SIZE(spectre_rlc_save_restore_register_list);
		} else {
			rdev->rlc.reg_list = kalindi_rlc_save_restore_register_list;
			rdev->rlc.reg_list_size =
				(u32)ARRAY_SIZE(kalindi_rlc_save_restore_register_list);
		}
	}
	rdev->rlc.cs_data = ci_cs_data;
	rdev->rlc.cp_table_size = ALIGN(CP_ME_TABLE_SIZE * 5 * 4, 2048); /* CP JT */
	rdev->rlc.cp_table_size += 64 * 1024; /* GDS */
	r = sumo_rlc_init(rdev);
	if (r) {
		DRM_ERROR("Failed to init rlc BOs!\n");
		return r;
	}

	/* allocate wb buffer */
	r = radeon_wb_init(rdev);
	if (r)
		return r;

	/* allocate mec buffers */
	r = cik_mec_init(rdev);
	if (r) {
		DRM_ERROR("Failed to init MEC BOs!\n");
		return r;
	}

	r = radeon_fence_driver_start_ring(rdev, RADEON_RING_TYPE_GFX_INDEX);
	if (r) {
		dev_err(rdev->dev, "failed initializing CP fences (%d).\n", r);
		return r;
	}

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

	cik_uvd_start(rdev);
	cik_vce_start(rdev);

	/* Enable IRQ */
	if (!rdev->irq.installed) {
		r = radeon_irq_kms_init(rdev);
		if (r)
			return r;
	}

	r = cik_irq_init(rdev);
	if (r) {
		DRM_ERROR("radeon: IH init failed (%d).\n", r);
		radeon_irq_kms_fini(rdev);
		return r;
	}
	cik_irq_set(rdev);

	if (rdev->family == CHIP_HAWAII) {
		if (rdev->new_fw)
			nop = PACKET3(PACKET3_NOP, 0x3FFF);
		else
			nop = RADEON_CP_PACKET2;
	} else {
		nop = PACKET3(PACKET3_NOP, 0x3FFF);
	}

	ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, RADEON_WB_CP_RPTR_OFFSET,
			     nop);
	if (r)
		return r;

	/* set up the compute queues */
	/* type-2 packets are deprecated on MEC, use type-3 instead */
	ring = &rdev->ring[CAYMAN_RING_TYPE_CP1_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, RADEON_WB_CP1_RPTR_OFFSET,
			     nop);
	if (r)
		return r;
	ring->me = 1; /* first MEC */
	ring->pipe = 0; /* first pipe */
	ring->queue = 0; /* first queue */
	ring->wptr_offs = CIK_WB_CP1_WPTR_OFFSET;

	/* type-2 packets are deprecated on MEC, use type-3 instead */
	ring = &rdev->ring[CAYMAN_RING_TYPE_CP2_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, RADEON_WB_CP2_RPTR_OFFSET,
			     nop);
	if (r)
		return r;
	/* dGPU only have 1 MEC */
	ring->me = 1; /* first MEC */
	ring->pipe = 0; /* first pipe */
	ring->queue = 1; /* second queue */
	ring->wptr_offs = CIK_WB_CP2_WPTR_OFFSET;

	ring = &rdev->ring[R600_RING_TYPE_DMA_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, R600_WB_DMA_RPTR_OFFSET,
			     SDMA_PACKET(SDMA_OPCODE_NOP, 0, 0));
	if (r)
		return r;

	ring = &rdev->ring[CAYMAN_RING_TYPE_DMA1_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, CAYMAN_WB_DMA1_RPTR_OFFSET,
			     SDMA_PACKET(SDMA_OPCODE_NOP, 0, 0));
	if (r)
		return r;

	r = cik_cp_resume(rdev);
	if (r)
		return r;

	r = cik_sdma_resume(rdev);
	if (r)
		return r;

	cik_uvd_resume(rdev);
	cik_vce_resume(rdev);

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