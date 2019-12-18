#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct TYPE_7__ {int ready; } ;
struct amdgpu_ring {int rptr_offs; int ring_size; int wptr_offs; int gpu_addr; int doorbell_index; TYPE_1__ sched; scalar_t__ use_doorbell; scalar_t__ wptr; } ;
struct TYPE_8__ {struct amdgpu_ring* buffer_funcs_ring; } ;
struct TYPE_11__ {scalar_t__ gpu_addr; } ;
struct TYPE_10__ {int num_instances; TYPE_3__* instance; } ;
struct amdgpu_device {TYPE_2__ mman; TYPE_6__* nbio_funcs; TYPE_5__ wb; TYPE_4__ sdma; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* sdma_doorbell_range ) (struct amdgpu_device*,int,scalar_t__,int,int) ;} ;
struct TYPE_9__ {struct amdgpu_ring ring; } ;

/* Variables and functions */
 int CACHE_READ_POLICY_L2__DEFAULT ; 
 int CACHE_WRITE_POLICY_L2__DEFAULT ; 
 int /*<<< orphan*/  ENABLE ; 
 int /*<<< orphan*/  F32_POLL_ENABLE ; 
 int /*<<< orphan*/  HALT ; 
 int /*<<< orphan*/  IB_ENABLE ; 
 int /*<<< orphan*/  IB_SWAP_ENABLE ; 
 int /*<<< orphan*/  MIDCMD_PREEMPT_ENABLE ; 
 int /*<<< orphan*/  OFFSET ; 
 int /*<<< orphan*/  RB_ENABLE ; 
 int /*<<< orphan*/  RB_SIZE ; 
 int /*<<< orphan*/  RB_SWAP_ENABLE ; 
 int /*<<< orphan*/  REDO_DELAY ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RESP_MODE ; 
 int /*<<< orphan*/  RPTR_WRITEBACK_ENABLE ; 
 int /*<<< orphan*/  RPTR_WRITEBACK_SWAP_ENABLE ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDMA0_CNTL ; 
 int /*<<< orphan*/  SDMA0_F32_CNTL ; 
 int /*<<< orphan*/  SDMA0_GFX_DOORBELL ; 
 int /*<<< orphan*/  SDMA0_GFX_DOORBELL_OFFSET ; 
 int /*<<< orphan*/  SDMA0_GFX_IB_CNTL ; 
 int /*<<< orphan*/  SDMA0_GFX_RB_CNTL ; 
 int /*<<< orphan*/  SDMA0_GFX_RB_WPTR_POLL_CNTL ; 
 int /*<<< orphan*/  SDMA0_UTCL1_CNTL ; 
 int /*<<< orphan*/  UTC_L1_ENABLE ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int amdgpu_ring_test_ring (struct amdgpu_ring*) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_ttm_set_buffer_funcs_status (struct amdgpu_device*,int) ; 
 int lower_32_bits (scalar_t__) ; 
 int /*<<< orphan*/  mmSDMA0_CNTL ; 
 int /*<<< orphan*/  mmSDMA0_F32_CNTL ; 
 int /*<<< orphan*/  mmSDMA0_GFX_DOORBELL ; 
 int /*<<< orphan*/  mmSDMA0_GFX_DOORBELL_OFFSET ; 
 int /*<<< orphan*/  mmSDMA0_GFX_IB_CNTL ; 
 int /*<<< orphan*/  mmSDMA0_GFX_MINOR_PTR_UPDATE ; 
 int /*<<< orphan*/  mmSDMA0_GFX_RB_BASE ; 
 int /*<<< orphan*/  mmSDMA0_GFX_RB_BASE_HI ; 
 int /*<<< orphan*/  mmSDMA0_GFX_RB_CNTL ; 
 int /*<<< orphan*/  mmSDMA0_GFX_RB_RPTR ; 
 int /*<<< orphan*/  mmSDMA0_GFX_RB_RPTR_ADDR_HI ; 
 int /*<<< orphan*/  mmSDMA0_GFX_RB_RPTR_ADDR_LO ; 
 int /*<<< orphan*/  mmSDMA0_GFX_RB_RPTR_HI ; 
 int /*<<< orphan*/  mmSDMA0_GFX_RB_WPTR ; 
 int /*<<< orphan*/  mmSDMA0_GFX_RB_WPTR_HI ; 
 int /*<<< orphan*/  mmSDMA0_GFX_RB_WPTR_POLL_ADDR_HI ; 
 int /*<<< orphan*/  mmSDMA0_GFX_RB_WPTR_POLL_ADDR_LO ; 
 int /*<<< orphan*/  mmSDMA0_GFX_RB_WPTR_POLL_CNTL ; 
 int /*<<< orphan*/  mmSDMA0_SEM_WAIT_FAIL_TIMER_CNTL ; 
 int /*<<< orphan*/  mmSDMA0_UTCL1_CNTL ; 
 int /*<<< orphan*/  mmSDMA0_UTCL1_PAGE ; 
 int order_base_2 (int) ; 
 int /*<<< orphan*/  sdma_v5_0_ctx_switch_enable (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  sdma_v5_0_enable (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  sdma_v5_0_get_reg_offset (struct amdgpu_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdma_v5_0_ring_set_wptr (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_device*,int,scalar_t__,int,int) ; 
 int upper_32_bits (scalar_t__) ; 

__attribute__((used)) static int sdma_v5_0_gfx_resume(struct amdgpu_device *adev)
{
	struct amdgpu_ring *ring;
	u32 rb_cntl, ib_cntl;
	u32 rb_bufsz;
	u32 wb_offset;
	u32 doorbell;
	u32 doorbell_offset;
	u32 temp;
	u32 wptr_poll_cntl;
	u64 wptr_gpu_addr;
	int i, r;

	for (i = 0; i < adev->sdma.num_instances; i++) {
		ring = &adev->sdma.instance[i].ring;
		wb_offset = (ring->rptr_offs * 4);

		WREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_SEM_WAIT_FAIL_TIMER_CNTL), 0);

		/* Set ring buffer size in dwords */
		rb_bufsz = order_base_2(ring->ring_size / 4);
		rb_cntl = RREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_GFX_RB_CNTL));
		rb_cntl = REG_SET_FIELD(rb_cntl, SDMA0_GFX_RB_CNTL, RB_SIZE, rb_bufsz);
#ifdef __BIG_ENDIAN
		rb_cntl = REG_SET_FIELD(rb_cntl, SDMA0_GFX_RB_CNTL, RB_SWAP_ENABLE, 1);
		rb_cntl = REG_SET_FIELD(rb_cntl, SDMA0_GFX_RB_CNTL,
					RPTR_WRITEBACK_SWAP_ENABLE, 1);
#endif
		WREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_GFX_RB_CNTL), rb_cntl);

		/* Initialize the ring buffer's read and write pointers */
		WREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_GFX_RB_RPTR), 0);
		WREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_GFX_RB_RPTR_HI), 0);
		WREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_GFX_RB_WPTR), 0);
		WREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_GFX_RB_WPTR_HI), 0);

		/* setup the wptr shadow polling */
		wptr_gpu_addr = adev->wb.gpu_addr + (ring->wptr_offs * 4);
		WREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_GFX_RB_WPTR_POLL_ADDR_LO),
		       lower_32_bits(wptr_gpu_addr));
		WREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_GFX_RB_WPTR_POLL_ADDR_HI),
		       upper_32_bits(wptr_gpu_addr));
		wptr_poll_cntl = RREG32(sdma_v5_0_get_reg_offset(adev, i,
							 mmSDMA0_GFX_RB_WPTR_POLL_CNTL));
		wptr_poll_cntl = REG_SET_FIELD(wptr_poll_cntl,
					       SDMA0_GFX_RB_WPTR_POLL_CNTL,
					       F32_POLL_ENABLE, 1);
		WREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_GFX_RB_WPTR_POLL_CNTL),
		       wptr_poll_cntl);

		/* set the wb address whether it's enabled or not */
		WREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_GFX_RB_RPTR_ADDR_HI),
		       upper_32_bits(adev->wb.gpu_addr + wb_offset) & 0xFFFFFFFF);
		WREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_GFX_RB_RPTR_ADDR_LO),
		       lower_32_bits(adev->wb.gpu_addr + wb_offset) & 0xFFFFFFFC);

		rb_cntl = REG_SET_FIELD(rb_cntl, SDMA0_GFX_RB_CNTL, RPTR_WRITEBACK_ENABLE, 1);

		WREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_GFX_RB_BASE), ring->gpu_addr >> 8);
		WREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_GFX_RB_BASE_HI), ring->gpu_addr >> 40);

		ring->wptr = 0;

		/* before programing wptr to a less value, need set minor_ptr_update first */
		WREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_GFX_MINOR_PTR_UPDATE), 1);

		if (!amdgpu_sriov_vf(adev)) { /* only bare-metal use register write for wptr */
			WREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_GFX_RB_WPTR), lower_32_bits(ring->wptr) << 2);
			WREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_GFX_RB_WPTR_HI), upper_32_bits(ring->wptr) << 2);
		}

		doorbell = RREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_GFX_DOORBELL));
		doorbell_offset = RREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_GFX_DOORBELL_OFFSET));

		if (ring->use_doorbell) {
			doorbell = REG_SET_FIELD(doorbell, SDMA0_GFX_DOORBELL, ENABLE, 1);
			doorbell_offset = REG_SET_FIELD(doorbell_offset, SDMA0_GFX_DOORBELL_OFFSET,
					OFFSET, ring->doorbell_index);
		} else {
			doorbell = REG_SET_FIELD(doorbell, SDMA0_GFX_DOORBELL, ENABLE, 0);
		}
		WREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_GFX_DOORBELL), doorbell);
		WREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_GFX_DOORBELL_OFFSET), doorbell_offset);

		adev->nbio_funcs->sdma_doorbell_range(adev, i, ring->use_doorbell,
						      ring->doorbell_index, 20);

		if (amdgpu_sriov_vf(adev))
			sdma_v5_0_ring_set_wptr(ring);

		/* set minor_ptr_update to 0 after wptr programed */
		WREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_GFX_MINOR_PTR_UPDATE), 0);

		/* set utc l1 enable flag always to 1 */
		temp = RREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_CNTL));
		temp = REG_SET_FIELD(temp, SDMA0_CNTL, UTC_L1_ENABLE, 1);

		/* enable MCBP */
		temp = REG_SET_FIELD(temp, SDMA0_CNTL, MIDCMD_PREEMPT_ENABLE, 1);
		WREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_CNTL), temp);

		/* Set up RESP_MODE to non-copy addresses */
		temp = RREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_UTCL1_CNTL));
		temp = REG_SET_FIELD(temp, SDMA0_UTCL1_CNTL, RESP_MODE, 3);
		temp = REG_SET_FIELD(temp, SDMA0_UTCL1_CNTL, REDO_DELAY, 9);
		WREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_UTCL1_CNTL), temp);

		/* program default cache read and write policy */
		temp = RREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_UTCL1_PAGE));
		/* clean read policy and write policy bits */
		temp &= 0xFF0FFF;
		temp |= ((CACHE_READ_POLICY_L2__DEFAULT << 12) | (CACHE_WRITE_POLICY_L2__DEFAULT << 14));
		WREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_UTCL1_PAGE), temp);

		if (!amdgpu_sriov_vf(adev)) {
			/* unhalt engine */
			temp = RREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_F32_CNTL));
			temp = REG_SET_FIELD(temp, SDMA0_F32_CNTL, HALT, 0);
			WREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_F32_CNTL), temp);
		}

		/* enable DMA RB */
		rb_cntl = REG_SET_FIELD(rb_cntl, SDMA0_GFX_RB_CNTL, RB_ENABLE, 1);
		WREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_GFX_RB_CNTL), rb_cntl);

		ib_cntl = RREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_GFX_IB_CNTL));
		ib_cntl = REG_SET_FIELD(ib_cntl, SDMA0_GFX_IB_CNTL, IB_ENABLE, 1);
#ifdef __BIG_ENDIAN
		ib_cntl = REG_SET_FIELD(ib_cntl, SDMA0_GFX_IB_CNTL, IB_SWAP_ENABLE, 1);
#endif
		/* enable DMA IBs */
		WREG32(sdma_v5_0_get_reg_offset(adev, i, mmSDMA0_GFX_IB_CNTL), ib_cntl);

		ring->sched.ready = true;

		if (amdgpu_sriov_vf(adev)) { /* bare-metal sequence doesn't need below to lines */
			sdma_v5_0_ctx_switch_enable(adev, true);
			sdma_v5_0_enable(adev, true);
		}

		r = amdgpu_ring_test_ring(ring);
		if (r) {
			ring->sched.ready = false;
			return r;
		}

		if (adev->mman.buffer_funcs_ring == ring)
			amdgpu_ttm_set_buffer_funcs_status(adev, true);
	}

	return 0;
}