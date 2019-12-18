#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int u32 ;
struct TYPE_9__ {int ready; } ;
struct amdgpu_ring {int ring_size; int rptr_offs; int gpu_addr; TYPE_4__ sched; scalar_t__ wptr; } ;
struct TYPE_10__ {struct amdgpu_ring* buffer_funcs_ring; } ;
struct TYPE_8__ {scalar_t__ gpu_addr; } ;
struct TYPE_7__ {int num_instances; TYPE_1__* instance; } ;
struct amdgpu_device {TYPE_5__ mman; TYPE_3__ wb; TYPE_2__ sdma; } ;
struct TYPE_6__ {struct amdgpu_ring ring; } ;

/* Variables and functions */
 int CMD_VMID_FORCE ; 
 int CTXEMPTY_INT_ENABLE ; 
 scalar_t__ DMA_CNTL ; 
 scalar_t__ DMA_IB_CNTL ; 
 int DMA_IB_ENABLE ; 
 int DMA_IB_SWAP_ENABLE ; 
 scalar_t__ DMA_RB_BASE ; 
 scalar_t__ DMA_RB_CNTL ; 
 int DMA_RB_ENABLE ; 
 scalar_t__ DMA_RB_RPTR ; 
 scalar_t__ DMA_RB_RPTR_ADDR_HI ; 
 scalar_t__ DMA_RB_RPTR_ADDR_LO ; 
 int DMA_RB_SWAP_ENABLE ; 
 scalar_t__ DMA_RB_WPTR ; 
 int DMA_RPTR_WRITEBACK_ENABLE ; 
 int DMA_RPTR_WRITEBACK_SWAP_ENABLE ; 
 scalar_t__ DMA_SEM_INCOMPLETE_TIMER_CNTL ; 
 scalar_t__ DMA_SEM_WAIT_FAIL_TIMER_CNTL ; 
 int RREG32 (scalar_t__) ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 int amdgpu_ring_test_helper (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  amdgpu_ttm_set_buffer_funcs_status (struct amdgpu_device*,int) ; 
 int lower_32_bits (scalar_t__) ; 
 int order_base_2 (int) ; 
 scalar_t__* sdma_offsets ; 
 int upper_32_bits (scalar_t__) ; 

__attribute__((used)) static int si_dma_start(struct amdgpu_device *adev)
{
	struct amdgpu_ring *ring;
	u32 rb_cntl, dma_cntl, ib_cntl, rb_bufsz;
	int i, r;
	uint64_t rptr_addr;

	for (i = 0; i < adev->sdma.num_instances; i++) {
		ring = &adev->sdma.instance[i].ring;

		WREG32(DMA_SEM_INCOMPLETE_TIMER_CNTL + sdma_offsets[i], 0);
		WREG32(DMA_SEM_WAIT_FAIL_TIMER_CNTL + sdma_offsets[i], 0);

		/* Set ring buffer size in dwords */
		rb_bufsz = order_base_2(ring->ring_size / 4);
		rb_cntl = rb_bufsz << 1;
#ifdef __BIG_ENDIAN
		rb_cntl |= DMA_RB_SWAP_ENABLE | DMA_RPTR_WRITEBACK_SWAP_ENABLE;
#endif
		WREG32(DMA_RB_CNTL + sdma_offsets[i], rb_cntl);

		/* Initialize the ring buffer's read and write pointers */
		WREG32(DMA_RB_RPTR + sdma_offsets[i], 0);
		WREG32(DMA_RB_WPTR + sdma_offsets[i], 0);

		rptr_addr = adev->wb.gpu_addr + (ring->rptr_offs * 4);

		WREG32(DMA_RB_RPTR_ADDR_LO + sdma_offsets[i], lower_32_bits(rptr_addr));
		WREG32(DMA_RB_RPTR_ADDR_HI + sdma_offsets[i], upper_32_bits(rptr_addr) & 0xFF);

		rb_cntl |= DMA_RPTR_WRITEBACK_ENABLE;

		WREG32(DMA_RB_BASE + sdma_offsets[i], ring->gpu_addr >> 8);

		/* enable DMA IBs */
		ib_cntl = DMA_IB_ENABLE | CMD_VMID_FORCE;
#ifdef __BIG_ENDIAN
		ib_cntl |= DMA_IB_SWAP_ENABLE;
#endif
		WREG32(DMA_IB_CNTL + sdma_offsets[i], ib_cntl);

		dma_cntl = RREG32(DMA_CNTL + sdma_offsets[i]);
		dma_cntl &= ~CTXEMPTY_INT_ENABLE;
		WREG32(DMA_CNTL + sdma_offsets[i], dma_cntl);

		ring->wptr = 0;
		WREG32(DMA_RB_WPTR + sdma_offsets[i], lower_32_bits(ring->wptr) << 2);
		WREG32(DMA_RB_CNTL + sdma_offsets[i], rb_cntl | DMA_RB_ENABLE);

		ring->sched.ready = true;

		r = amdgpu_ring_test_helper(ring);
		if (r)
			return r;

		if (adev->mman.buffer_funcs_ring == ring)
			amdgpu_ttm_set_buffer_funcs_status(adev, true);
	}

	return 0;
}