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
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_6__ {int ready; } ;
struct amdgpu_ring {int ring_size; int wptr; int rptr_offs; int wptr_offs; int gpu_addr; TYPE_3__ sched; } ;
struct TYPE_5__ {int gpu_addr; } ;
struct TYPE_4__ {struct amdgpu_ring* gfx_ring; } ;
struct amdgpu_device {TYPE_2__ wb; TYPE_1__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_SWAP ; 
 int /*<<< orphan*/  CP_RB0_CNTL ; 
 int CP_RB0_CNTL__RB_RPTR_WR_ENA_MASK ; 
 int /*<<< orphan*/  MIN_IB_AVAILSZ ; 
 int /*<<< orphan*/  MTYPE ; 
 int /*<<< orphan*/  RB_BLKSZ ; 
 int /*<<< orphan*/  RB_BUFSZ ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  amdgpu_ring_clear_ring (struct amdgpu_ring*) ; 
 int /*<<< orphan*/  gfx_v8_0_cp_gfx_start (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v8_0_set_cpg_door_bell (struct amdgpu_device*,struct amdgpu_ring*) ; 
 int lower_32_bits (int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mmCP_RB0_BASE ; 
 int /*<<< orphan*/  mmCP_RB0_BASE_HI ; 
 int /*<<< orphan*/  mmCP_RB0_CNTL ; 
 int /*<<< orphan*/  mmCP_RB0_RPTR_ADDR ; 
 int /*<<< orphan*/  mmCP_RB0_RPTR_ADDR_HI ; 
 int /*<<< orphan*/  mmCP_RB0_WPTR ; 
 int /*<<< orphan*/  mmCP_RB_VMID ; 
 int /*<<< orphan*/  mmCP_RB_WPTR_DELAY ; 
 int /*<<< orphan*/  mmCP_RB_WPTR_POLL_ADDR_HI ; 
 int /*<<< orphan*/  mmCP_RB_WPTR_POLL_ADDR_LO ; 
 int order_base_2 (int) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static int gfx_v8_0_cp_gfx_resume(struct amdgpu_device *adev)
{
	struct amdgpu_ring *ring;
	u32 tmp;
	u32 rb_bufsz;
	u64 rb_addr, rptr_addr, wptr_gpu_addr;

	/* Set the write pointer delay */
	WREG32(mmCP_RB_WPTR_DELAY, 0);

	/* set the RB to use vmid 0 */
	WREG32(mmCP_RB_VMID, 0);

	/* Set ring buffer size */
	ring = &adev->gfx.gfx_ring[0];
	rb_bufsz = order_base_2(ring->ring_size / 8);
	tmp = REG_SET_FIELD(0, CP_RB0_CNTL, RB_BUFSZ, rb_bufsz);
	tmp = REG_SET_FIELD(tmp, CP_RB0_CNTL, RB_BLKSZ, rb_bufsz - 2);
	tmp = REG_SET_FIELD(tmp, CP_RB0_CNTL, MTYPE, 3);
	tmp = REG_SET_FIELD(tmp, CP_RB0_CNTL, MIN_IB_AVAILSZ, 1);
#ifdef __BIG_ENDIAN
	tmp = REG_SET_FIELD(tmp, CP_RB0_CNTL, BUF_SWAP, 1);
#endif
	WREG32(mmCP_RB0_CNTL, tmp);

	/* Initialize the ring buffer's read and write pointers */
	WREG32(mmCP_RB0_CNTL, tmp | CP_RB0_CNTL__RB_RPTR_WR_ENA_MASK);
	ring->wptr = 0;
	WREG32(mmCP_RB0_WPTR, lower_32_bits(ring->wptr));

	/* set the wb address wether it's enabled or not */
	rptr_addr = adev->wb.gpu_addr + (ring->rptr_offs * 4);
	WREG32(mmCP_RB0_RPTR_ADDR, lower_32_bits(rptr_addr));
	WREG32(mmCP_RB0_RPTR_ADDR_HI, upper_32_bits(rptr_addr) & 0xFF);

	wptr_gpu_addr = adev->wb.gpu_addr + (ring->wptr_offs * 4);
	WREG32(mmCP_RB_WPTR_POLL_ADDR_LO, lower_32_bits(wptr_gpu_addr));
	WREG32(mmCP_RB_WPTR_POLL_ADDR_HI, upper_32_bits(wptr_gpu_addr));
	mdelay(1);
	WREG32(mmCP_RB0_CNTL, tmp);

	rb_addr = ring->gpu_addr >> 8;
	WREG32(mmCP_RB0_BASE, rb_addr);
	WREG32(mmCP_RB0_BASE_HI, upper_32_bits(rb_addr));

	gfx_v8_0_set_cpg_door_bell(adev, ring);
	/* start the ring */
	amdgpu_ring_clear_ring(ring);
	gfx_v8_0_cp_gfx_start(adev);
	ring->sched.ready = true;

	return 0;
}