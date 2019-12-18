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
struct TYPE_5__ {int num_gfx_rings; struct amdgpu_ring* gfx_ring; } ;
struct TYPE_4__ {int gpu_addr; } ;
struct amdgpu_device {TYPE_2__ gfx; int /*<<< orphan*/  srbm_mutex; TYPE_1__ wb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_SWAP ; 
 int /*<<< orphan*/  CP_RB0_CNTL ; 
 int /*<<< orphan*/  CP_RB1_CNTL ; 
 int CP_RB1_RPTR_ADDR_HI__RB_RPTR_ADDR_HI_MASK ; 
 int CP_RB_RPTR_ADDR_HI__RB_RPTR_ADDR_HI_MASK ; 
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  PIPE_ID0 ; 
 int /*<<< orphan*/  PIPE_ID1 ; 
 int /*<<< orphan*/  RB_BLKSZ ; 
 int /*<<< orphan*/  RB_BUFSZ ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gfx_v10_0_cp_gfx_set_doorbell (struct amdgpu_device*,struct amdgpu_ring*) ; 
 int /*<<< orphan*/  gfx_v10_0_cp_gfx_start (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v10_0_cp_gfx_switch_pipe (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int lower_32_bits (int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mmCP_RB0_BASE ; 
 int /*<<< orphan*/  mmCP_RB0_BASE_HI ; 
 int /*<<< orphan*/  mmCP_RB0_CNTL ; 
 int /*<<< orphan*/  mmCP_RB0_RPTR_ADDR ; 
 int /*<<< orphan*/  mmCP_RB0_RPTR_ADDR_HI ; 
 int /*<<< orphan*/  mmCP_RB0_WPTR ; 
 int /*<<< orphan*/  mmCP_RB0_WPTR_HI ; 
 int /*<<< orphan*/  mmCP_RB1_ACTIVE ; 
 int /*<<< orphan*/  mmCP_RB1_BASE ; 
 int /*<<< orphan*/  mmCP_RB1_BASE_HI ; 
 int /*<<< orphan*/  mmCP_RB1_CNTL ; 
 int /*<<< orphan*/  mmCP_RB1_RPTR_ADDR ; 
 int /*<<< orphan*/  mmCP_RB1_RPTR_ADDR_HI ; 
 int /*<<< orphan*/  mmCP_RB1_WPTR ; 
 int /*<<< orphan*/  mmCP_RB1_WPTR_HI ; 
 int /*<<< orphan*/  mmCP_RB_ACTIVE ; 
 int /*<<< orphan*/  mmCP_RB_VMID ; 
 int /*<<< orphan*/  mmCP_RB_WPTR_DELAY ; 
 int /*<<< orphan*/  mmCP_RB_WPTR_POLL_ADDR_HI ; 
 int /*<<< orphan*/  mmCP_RB_WPTR_POLL_ADDR_LO ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int order_base_2 (int) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static int gfx_v10_0_cp_gfx_resume(struct amdgpu_device *adev)
{
	struct amdgpu_ring *ring;
	u32 tmp;
	u32 rb_bufsz;
	u64 rb_addr, rptr_addr, wptr_gpu_addr;
	u32 i;

	/* Set the write pointer delay */
	WREG32_SOC15(GC, 0, mmCP_RB_WPTR_DELAY, 0);

	/* set the RB to use vmid 0 */
	WREG32_SOC15(GC, 0, mmCP_RB_VMID, 0);

	/* Init gfx ring 0 for pipe 0 */
	mutex_lock(&adev->srbm_mutex);
	gfx_v10_0_cp_gfx_switch_pipe(adev, PIPE_ID0);
	mutex_unlock(&adev->srbm_mutex);
	/* Set ring buffer size */
	ring = &adev->gfx.gfx_ring[0];
	rb_bufsz = order_base_2(ring->ring_size / 8);
	tmp = REG_SET_FIELD(0, CP_RB0_CNTL, RB_BUFSZ, rb_bufsz);
	tmp = REG_SET_FIELD(tmp, CP_RB0_CNTL, RB_BLKSZ, rb_bufsz - 2);
#ifdef __BIG_ENDIAN
	tmp = REG_SET_FIELD(tmp, CP_RB0_CNTL, BUF_SWAP, 1);
#endif
	WREG32_SOC15(GC, 0, mmCP_RB0_CNTL, tmp);

	/* Initialize the ring buffer's write pointers */
	ring->wptr = 0;
	WREG32_SOC15(GC, 0, mmCP_RB0_WPTR, lower_32_bits(ring->wptr));
	WREG32_SOC15(GC, 0, mmCP_RB0_WPTR_HI, upper_32_bits(ring->wptr));

	/* set the wb address wether it's enabled or not */
	rptr_addr = adev->wb.gpu_addr + (ring->rptr_offs * 4);
	WREG32_SOC15(GC, 0, mmCP_RB0_RPTR_ADDR, lower_32_bits(rptr_addr));
	WREG32_SOC15(GC, 0, mmCP_RB0_RPTR_ADDR_HI, upper_32_bits(rptr_addr) &
		     CP_RB_RPTR_ADDR_HI__RB_RPTR_ADDR_HI_MASK);

	wptr_gpu_addr = adev->wb.gpu_addr + (ring->wptr_offs * 4);
	WREG32_SOC15(GC, 0, mmCP_RB_WPTR_POLL_ADDR_LO,
		     lower_32_bits(wptr_gpu_addr));
	WREG32_SOC15(GC, 0, mmCP_RB_WPTR_POLL_ADDR_HI,
		     upper_32_bits(wptr_gpu_addr));

	mdelay(1);
	WREG32_SOC15(GC, 0, mmCP_RB0_CNTL, tmp);

	rb_addr = ring->gpu_addr >> 8;
	WREG32_SOC15(GC, 0, mmCP_RB0_BASE, rb_addr);
	WREG32_SOC15(GC, 0, mmCP_RB0_BASE_HI, upper_32_bits(rb_addr));

	WREG32_SOC15(GC, 0, mmCP_RB_ACTIVE, 1);

	gfx_v10_0_cp_gfx_set_doorbell(adev, ring);

	/* Init gfx ring 1 for pipe 1 */
	mutex_lock(&adev->srbm_mutex);
	gfx_v10_0_cp_gfx_switch_pipe(adev, PIPE_ID1);
	mutex_unlock(&adev->srbm_mutex);
	ring = &adev->gfx.gfx_ring[1];
	rb_bufsz = order_base_2(ring->ring_size / 8);
	tmp = REG_SET_FIELD(0, CP_RB1_CNTL, RB_BUFSZ, rb_bufsz);
	tmp = REG_SET_FIELD(tmp, CP_RB1_CNTL, RB_BLKSZ, rb_bufsz - 2);
	WREG32_SOC15(GC, 0, mmCP_RB1_CNTL, tmp);
	/* Initialize the ring buffer's write pointers */
	ring->wptr = 0;
	WREG32_SOC15(GC, 0, mmCP_RB1_WPTR, lower_32_bits(ring->wptr));
	WREG32_SOC15(GC, 0, mmCP_RB1_WPTR_HI, upper_32_bits(ring->wptr));
	/* Set the wb address wether it's enabled or not */
	rptr_addr = adev->wb.gpu_addr + (ring->rptr_offs * 4);
	WREG32_SOC15(GC, 0, mmCP_RB1_RPTR_ADDR, lower_32_bits(rptr_addr));
	WREG32_SOC15(GC, 0, mmCP_RB1_RPTR_ADDR_HI, upper_32_bits(rptr_addr) &
		CP_RB1_RPTR_ADDR_HI__RB_RPTR_ADDR_HI_MASK);
	wptr_gpu_addr = adev->wb.gpu_addr + (ring->wptr_offs * 4);
	WREG32_SOC15(GC, 0, mmCP_RB_WPTR_POLL_ADDR_LO,
		lower_32_bits(wptr_gpu_addr));
	WREG32_SOC15(GC, 0, mmCP_RB_WPTR_POLL_ADDR_HI,
		upper_32_bits(wptr_gpu_addr));

	mdelay(1);
	WREG32_SOC15(GC, 0, mmCP_RB1_CNTL, tmp);

	rb_addr = ring->gpu_addr >> 8;
	WREG32_SOC15(GC, 0, mmCP_RB1_BASE, rb_addr);
	WREG32_SOC15(GC, 0, mmCP_RB1_BASE_HI, upper_32_bits(rb_addr));
	WREG32_SOC15(GC, 0, mmCP_RB1_ACTIVE, 1);

	gfx_v10_0_cp_gfx_set_doorbell(adev, ring);

	/* Switch to pipe 0 */
	mutex_lock(&adev->srbm_mutex);
	gfx_v10_0_cp_gfx_switch_pipe(adev, PIPE_ID0);
	mutex_unlock(&adev->srbm_mutex);

	/* start the ring */
	gfx_v10_0_cp_gfx_start(adev);

	for (i = 0; i < adev->gfx.num_gfx_rings; i++) {
		ring = &adev->gfx.gfx_ring[i];
		ring->sched.ready = true;
	}

	return 0;
}