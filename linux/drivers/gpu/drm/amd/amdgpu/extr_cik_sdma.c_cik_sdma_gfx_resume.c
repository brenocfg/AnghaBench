#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_11__ {int ready; } ;
struct amdgpu_ring {int rptr_offs; int ring_size; int gpu_addr; TYPE_4__ sched; scalar_t__ wptr; } ;
struct TYPE_14__ {struct amdgpu_ring* buffer_funcs_ring; } ;
struct TYPE_13__ {int num_instances; TYPE_5__* instance; } ;
struct TYPE_10__ {int gpu_addr; } ;
struct TYPE_8__ {int gb_addr_config; } ;
struct TYPE_9__ {TYPE_1__ config; } ;
struct amdgpu_device {TYPE_7__ mman; TYPE_6__ sdma; TYPE_3__ wb; TYPE_2__ gfx; int /*<<< orphan*/  srbm_mutex; } ;
struct TYPE_12__ {struct amdgpu_ring ring; } ;

/* Variables and functions */
 int SDMA0_GFX_IB_CNTL__IB_ENABLE_MASK ; 
 int SDMA0_GFX_IB_CNTL__IB_SWAP_ENABLE_MASK ; 
 int SDMA0_GFX_RB_CNTL__RB_ENABLE_MASK ; 
 int SDMA0_GFX_RB_CNTL__RB_SWAP_ENABLE_MASK ; 
 int SDMA0_GFX_RB_CNTL__RPTR_WRITEBACK_ENABLE_MASK ; 
 int SDMA0_GFX_RB_CNTL__RPTR_WRITEBACK_SWAP_ENABLE_MASK ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 int amdgpu_ring_test_helper (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  amdgpu_ttm_set_buffer_funcs_status (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  cik_sdma_enable (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  cik_srbm_select (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int lower_32_bits (scalar_t__) ; 
 scalar_t__ mmSDMA0_GFX_APE1_CNTL ; 
 scalar_t__ mmSDMA0_GFX_IB_CNTL ; 
 scalar_t__ mmSDMA0_GFX_IB_OFFSET ; 
 scalar_t__ mmSDMA0_GFX_IB_RPTR ; 
 scalar_t__ mmSDMA0_GFX_RB_BASE ; 
 scalar_t__ mmSDMA0_GFX_RB_BASE_HI ; 
 scalar_t__ mmSDMA0_GFX_RB_CNTL ; 
 scalar_t__ mmSDMA0_GFX_RB_RPTR ; 
 scalar_t__ mmSDMA0_GFX_RB_RPTR_ADDR_HI ; 
 scalar_t__ mmSDMA0_GFX_RB_RPTR_ADDR_LO ; 
 scalar_t__ mmSDMA0_GFX_RB_WPTR ; 
 scalar_t__ mmSDMA0_GFX_VIRTUAL_ADDR ; 
 scalar_t__ mmSDMA0_SEM_INCOMPLETE_TIMER_CNTL ; 
 scalar_t__ mmSDMA0_SEM_WAIT_FAIL_TIMER_CNTL ; 
 scalar_t__ mmSDMA0_TILING_CONFIG ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int order_base_2 (int) ; 
 scalar_t__* sdma_offsets ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static int cik_sdma_gfx_resume(struct amdgpu_device *adev)
{
	struct amdgpu_ring *ring;
	u32 rb_cntl, ib_cntl;
	u32 rb_bufsz;
	u32 wb_offset;
	int i, j, r;

	for (i = 0; i < adev->sdma.num_instances; i++) {
		ring = &adev->sdma.instance[i].ring;
		wb_offset = (ring->rptr_offs * 4);

		mutex_lock(&adev->srbm_mutex);
		for (j = 0; j < 16; j++) {
			cik_srbm_select(adev, 0, 0, 0, j);
			/* SDMA GFX */
			WREG32(mmSDMA0_GFX_VIRTUAL_ADDR + sdma_offsets[i], 0);
			WREG32(mmSDMA0_GFX_APE1_CNTL + sdma_offsets[i], 0);
			/* XXX SDMA RLC - todo */
		}
		cik_srbm_select(adev, 0, 0, 0, 0);
		mutex_unlock(&adev->srbm_mutex);

		WREG32(mmSDMA0_TILING_CONFIG + sdma_offsets[i],
		       adev->gfx.config.gb_addr_config & 0x70);

		WREG32(mmSDMA0_SEM_INCOMPLETE_TIMER_CNTL + sdma_offsets[i], 0);
		WREG32(mmSDMA0_SEM_WAIT_FAIL_TIMER_CNTL + sdma_offsets[i], 0);

		/* Set ring buffer size in dwords */
		rb_bufsz = order_base_2(ring->ring_size / 4);
		rb_cntl = rb_bufsz << 1;
#ifdef __BIG_ENDIAN
		rb_cntl |= SDMA0_GFX_RB_CNTL__RB_SWAP_ENABLE_MASK |
			SDMA0_GFX_RB_CNTL__RPTR_WRITEBACK_SWAP_ENABLE_MASK;
#endif
		WREG32(mmSDMA0_GFX_RB_CNTL + sdma_offsets[i], rb_cntl);

		/* Initialize the ring buffer's read and write pointers */
		WREG32(mmSDMA0_GFX_RB_RPTR + sdma_offsets[i], 0);
		WREG32(mmSDMA0_GFX_RB_WPTR + sdma_offsets[i], 0);
		WREG32(mmSDMA0_GFX_IB_RPTR + sdma_offsets[i], 0);
		WREG32(mmSDMA0_GFX_IB_OFFSET + sdma_offsets[i], 0);

		/* set the wb address whether it's enabled or not */
		WREG32(mmSDMA0_GFX_RB_RPTR_ADDR_HI + sdma_offsets[i],
		       upper_32_bits(adev->wb.gpu_addr + wb_offset) & 0xFFFFFFFF);
		WREG32(mmSDMA0_GFX_RB_RPTR_ADDR_LO + sdma_offsets[i],
		       ((adev->wb.gpu_addr + wb_offset) & 0xFFFFFFFC));

		rb_cntl |= SDMA0_GFX_RB_CNTL__RPTR_WRITEBACK_ENABLE_MASK;

		WREG32(mmSDMA0_GFX_RB_BASE + sdma_offsets[i], ring->gpu_addr >> 8);
		WREG32(mmSDMA0_GFX_RB_BASE_HI + sdma_offsets[i], ring->gpu_addr >> 40);

		ring->wptr = 0;
		WREG32(mmSDMA0_GFX_RB_WPTR + sdma_offsets[i], lower_32_bits(ring->wptr) << 2);

		/* enable DMA RB */
		WREG32(mmSDMA0_GFX_RB_CNTL + sdma_offsets[i],
		       rb_cntl | SDMA0_GFX_RB_CNTL__RB_ENABLE_MASK);

		ib_cntl = SDMA0_GFX_IB_CNTL__IB_ENABLE_MASK;
#ifdef __BIG_ENDIAN
		ib_cntl |= SDMA0_GFX_IB_CNTL__IB_SWAP_ENABLE_MASK;
#endif
		/* enable DMA IBs */
		WREG32(mmSDMA0_GFX_IB_CNTL + sdma_offsets[i], ib_cntl);

		ring->sched.ready = true;
	}

	cik_sdma_enable(adev, true);

	for (i = 0; i < adev->sdma.num_instances; i++) {
		ring = &adev->sdma.instance[i].ring;
		r = amdgpu_ring_test_helper(ring);
		if (r)
			return r;

		if (adev->mman.buffer_funcs_ring == ring)
			amdgpu_ttm_set_buffer_funcs_status(adev, true);
	}

	return 0;
}