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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct amdgpu_ring {int ring_size; int wptr; int rptr_offs; int gpu_addr; } ;
struct TYPE_4__ {scalar_t__ gpu_addr; } ;
struct TYPE_3__ {struct amdgpu_ring* gfx_ring; } ;
struct amdgpu_device {TYPE_2__ wb; TYPE_1__ gfx; } ;

/* Variables and functions */
 int AMDGPU_GPU_PAGE_SIZE ; 
 int BUF_SWAP_32BIT ; 
 int CP_RB0_CNTL__RB_RPTR_WR_ENA_MASK ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int amdgpu_ring_test_helper (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  gfx_v6_0_cp_gfx_start (struct amdgpu_device*) ; 
 int lower_32_bits (scalar_t__) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mmCP_DEBUG ; 
 int /*<<< orphan*/  mmCP_RB0_BASE ; 
 int /*<<< orphan*/  mmCP_RB0_CNTL ; 
 int /*<<< orphan*/  mmCP_RB0_RPTR_ADDR ; 
 int /*<<< orphan*/  mmCP_RB0_RPTR_ADDR_HI ; 
 int /*<<< orphan*/  mmCP_RB0_WPTR ; 
 int /*<<< orphan*/  mmCP_RB_WPTR_DELAY ; 
 int /*<<< orphan*/  mmCP_SEM_INCOMPLETE_TIMER_CNTL ; 
 int /*<<< orphan*/  mmCP_SEM_WAIT_TIMER ; 
 int /*<<< orphan*/  mmSCRATCH_ADDR ; 
 int /*<<< orphan*/  mmSCRATCH_UMSK ; 
 int order_base_2 (int) ; 
 int upper_32_bits (scalar_t__) ; 

__attribute__((used)) static int gfx_v6_0_cp_gfx_resume(struct amdgpu_device *adev)
{
	struct amdgpu_ring *ring;
	u32 tmp;
	u32 rb_bufsz;
	int r;
	u64 rptr_addr;

	WREG32(mmCP_SEM_WAIT_TIMER, 0x0);
	WREG32(mmCP_SEM_INCOMPLETE_TIMER_CNTL, 0x0);

	/* Set the write pointer delay */
	WREG32(mmCP_RB_WPTR_DELAY, 0);

	WREG32(mmCP_DEBUG, 0);
	WREG32(mmSCRATCH_ADDR, 0);

	/* ring 0 - compute and gfx */
	/* Set ring buffer size */
	ring = &adev->gfx.gfx_ring[0];
	rb_bufsz = order_base_2(ring->ring_size / 8);
	tmp = (order_base_2(AMDGPU_GPU_PAGE_SIZE/8) << 8) | rb_bufsz;

#ifdef __BIG_ENDIAN
	tmp |= BUF_SWAP_32BIT;
#endif
	WREG32(mmCP_RB0_CNTL, tmp);

	/* Initialize the ring buffer's read and write pointers */
	WREG32(mmCP_RB0_CNTL, tmp | CP_RB0_CNTL__RB_RPTR_WR_ENA_MASK);
	ring->wptr = 0;
	WREG32(mmCP_RB0_WPTR, ring->wptr);

	/* set the wb address whether it's enabled or not */
	rptr_addr = adev->wb.gpu_addr + (ring->rptr_offs * 4);
	WREG32(mmCP_RB0_RPTR_ADDR, lower_32_bits(rptr_addr));
	WREG32(mmCP_RB0_RPTR_ADDR_HI, upper_32_bits(rptr_addr) & 0xFF);

	WREG32(mmSCRATCH_UMSK, 0);

	mdelay(1);
	WREG32(mmCP_RB0_CNTL, tmp);

	WREG32(mmCP_RB0_BASE, ring->gpu_addr >> 8);

	/* start the rings */
	gfx_v6_0_cp_gfx_start(adev);
	r = amdgpu_ring_test_helper(ring);
	if (r)
		return r;

	return 0;
}