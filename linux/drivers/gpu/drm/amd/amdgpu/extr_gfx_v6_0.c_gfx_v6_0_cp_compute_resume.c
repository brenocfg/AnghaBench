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
struct TYPE_4__ {struct amdgpu_ring* compute_ring; } ;
struct TYPE_3__ {scalar_t__ gpu_addr; } ;
struct amdgpu_device {TYPE_2__ gfx; TYPE_1__ wb; } ;

/* Variables and functions */
 int AMDGPU_GPU_PAGE_SIZE ; 
 int BUF_SWAP_32BIT ; 
 int CP_RB1_CNTL__RB_RPTR_WR_ENA_MASK ; 
 int CP_RB2_CNTL__RB_RPTR_WR_ENA_MASK ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int amdgpu_ring_test_helper (struct amdgpu_ring*) ; 
 int lower_32_bits (scalar_t__) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mmCP_RB1_BASE ; 
 int /*<<< orphan*/  mmCP_RB1_CNTL ; 
 int /*<<< orphan*/  mmCP_RB1_RPTR_ADDR ; 
 int /*<<< orphan*/  mmCP_RB1_RPTR_ADDR_HI ; 
 int /*<<< orphan*/  mmCP_RB1_WPTR ; 
 int /*<<< orphan*/  mmCP_RB2_BASE ; 
 int /*<<< orphan*/  mmCP_RB2_CNTL ; 
 int /*<<< orphan*/  mmCP_RB2_RPTR_ADDR ; 
 int /*<<< orphan*/  mmCP_RB2_RPTR_ADDR_HI ; 
 int /*<<< orphan*/  mmCP_RB2_WPTR ; 
 int order_base_2 (int) ; 
 int upper_32_bits (scalar_t__) ; 

__attribute__((used)) static int gfx_v6_0_cp_compute_resume(struct amdgpu_device *adev)
{
	struct amdgpu_ring *ring;
	u32 tmp;
	u32 rb_bufsz;
	int i, r;
	u64 rptr_addr;

	/* ring1  - compute only */
	/* Set ring buffer size */

	ring = &adev->gfx.compute_ring[0];
	rb_bufsz = order_base_2(ring->ring_size / 8);
	tmp = (order_base_2(AMDGPU_GPU_PAGE_SIZE/8) << 8) | rb_bufsz;
#ifdef __BIG_ENDIAN
	tmp |= BUF_SWAP_32BIT;
#endif
	WREG32(mmCP_RB1_CNTL, tmp);

	WREG32(mmCP_RB1_CNTL, tmp | CP_RB1_CNTL__RB_RPTR_WR_ENA_MASK);
	ring->wptr = 0;
	WREG32(mmCP_RB1_WPTR, ring->wptr);

	rptr_addr = adev->wb.gpu_addr + (ring->rptr_offs * 4);
	WREG32(mmCP_RB1_RPTR_ADDR, lower_32_bits(rptr_addr));
	WREG32(mmCP_RB1_RPTR_ADDR_HI, upper_32_bits(rptr_addr) & 0xFF);

	mdelay(1);
	WREG32(mmCP_RB1_CNTL, tmp);
	WREG32(mmCP_RB1_BASE, ring->gpu_addr >> 8);

	ring = &adev->gfx.compute_ring[1];
	rb_bufsz = order_base_2(ring->ring_size / 8);
	tmp = (order_base_2(AMDGPU_GPU_PAGE_SIZE/8) << 8) | rb_bufsz;
#ifdef __BIG_ENDIAN
	tmp |= BUF_SWAP_32BIT;
#endif
	WREG32(mmCP_RB2_CNTL, tmp);

	WREG32(mmCP_RB2_CNTL, tmp | CP_RB2_CNTL__RB_RPTR_WR_ENA_MASK);
	ring->wptr = 0;
	WREG32(mmCP_RB2_WPTR, ring->wptr);
	rptr_addr = adev->wb.gpu_addr + (ring->rptr_offs * 4);
	WREG32(mmCP_RB2_RPTR_ADDR, lower_32_bits(rptr_addr));
	WREG32(mmCP_RB2_RPTR_ADDR_HI, upper_32_bits(rptr_addr) & 0xFF);

	mdelay(1);
	WREG32(mmCP_RB2_CNTL, tmp);
	WREG32(mmCP_RB2_BASE, ring->gpu_addr >> 8);


	for (i = 0; i < 2; i++) {
		r = amdgpu_ring_test_helper(&adev->gfx.compute_ring[i]);
		if (r)
			return r;
	}

	return 0;
}