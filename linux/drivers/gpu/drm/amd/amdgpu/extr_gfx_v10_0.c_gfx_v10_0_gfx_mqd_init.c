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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct v10_gfx_mqd {int cp_mqd_base_addr; int cp_mqd_base_addr_hi; int cp_gfx_mqd_control; int cp_gfx_hqd_queue_priority; int cp_gfx_hqd_quantum; int cp_gfx_hqd_base; int cp_gfx_hqd_base_hi; int cp_gfx_hqd_rptr_addr; int cp_gfx_hqd_rptr_addr_hi; int cp_rb_wptr_poll_addr_lo; int cp_rb_wptr_poll_addr_hi; int cp_gfx_hqd_cntl; int cp_rb_doorbell_control; int cp_gfx_hqd_active; void* cp_gfx_hqd_rptr; scalar_t__ cp_gfx_hqd_vmid; scalar_t__ cp_gfx_hqd_wptr_hi; scalar_t__ cp_gfx_hqd_wptr; } ;
struct amdgpu_ring {int mqd_gpu_addr; int gpu_addr; int rptr_offs; int wptr_offs; int ring_size; int doorbell_index; scalar_t__ wptr; scalar_t__ use_doorbell; struct v10_gfx_mqd* mqd_ptr; struct amdgpu_device* adev; } ;
struct TYPE_2__ {int gpu_addr; } ;
struct amdgpu_device {TYPE_1__ wb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_SWAP ; 
 int /*<<< orphan*/  CACHE_POLICY ; 
 int /*<<< orphan*/  CP_GFX_HQD_CNTL ; 
 int /*<<< orphan*/  CP_GFX_HQD_QUANTUM ; 
 int /*<<< orphan*/  CP_GFX_HQD_QUEUE_PRIORITY ; 
 int /*<<< orphan*/  CP_GFX_HQD_VMID ; 
 int /*<<< orphan*/  CP_GFX_MQD_CONTROL ; 
 int /*<<< orphan*/  CP_RB_DOORBELL_CONTROL ; 
 int /*<<< orphan*/  DOORBELL_EN ; 
 int /*<<< orphan*/  DOORBELL_OFFSET ; 
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  PRIORITY_LEVEL ; 
 int /*<<< orphan*/  PRIV_STATE ; 
 int /*<<< orphan*/  QUANTUM_EN ; 
 int /*<<< orphan*/  RB_BLKSZ ; 
 int /*<<< orphan*/  RB_BUFSZ ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMID ; 
 int /*<<< orphan*/  mmCP_GFX_HQD_CNTL ; 
 int /*<<< orphan*/  mmCP_GFX_HQD_QUANTUM ; 
 int /*<<< orphan*/  mmCP_GFX_HQD_QUEUE_PRIORITY ; 
 int /*<<< orphan*/  mmCP_GFX_HQD_RPTR ; 
 int /*<<< orphan*/  mmCP_GFX_HQD_VMID ; 
 int /*<<< orphan*/  mmCP_GFX_MQD_CONTROL ; 
 int /*<<< orphan*/  mmCP_RB_DOORBELL_CONTROL ; 
 int order_base_2 (int) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static int gfx_v10_0_gfx_mqd_init(struct amdgpu_ring *ring)
{
	struct amdgpu_device *adev = ring->adev;
	struct v10_gfx_mqd *mqd = ring->mqd_ptr;
	uint64_t hqd_gpu_addr, wb_gpu_addr;
	uint32_t tmp;
	uint32_t rb_bufsz;

	/* set up gfx hqd wptr */
	mqd->cp_gfx_hqd_wptr = 0;
	mqd->cp_gfx_hqd_wptr_hi = 0;

	/* set the pointer to the MQD */
	mqd->cp_mqd_base_addr = ring->mqd_gpu_addr & 0xfffffffc;
	mqd->cp_mqd_base_addr_hi = upper_32_bits(ring->mqd_gpu_addr);

	/* set up mqd control */
	tmp = RREG32_SOC15(GC, 0, mmCP_GFX_MQD_CONTROL);
	tmp = REG_SET_FIELD(tmp, CP_GFX_MQD_CONTROL, VMID, 0);
	tmp = REG_SET_FIELD(tmp, CP_GFX_MQD_CONTROL, PRIV_STATE, 1);
	tmp = REG_SET_FIELD(tmp, CP_GFX_MQD_CONTROL, CACHE_POLICY, 0);
	mqd->cp_gfx_mqd_control = tmp;

	/* set up gfx_hqd_vimd with 0x0 to indicate the ring buffer's vmid */
	tmp = RREG32_SOC15(GC, 0, mmCP_GFX_HQD_VMID);
	tmp = REG_SET_FIELD(tmp, CP_GFX_HQD_VMID, VMID, 0);
	mqd->cp_gfx_hqd_vmid = 0;

	/* set up default queue priority level
	 * 0x0 = low priority, 0x1 = high priority */
	tmp = RREG32_SOC15(GC, 0, mmCP_GFX_HQD_QUEUE_PRIORITY);
	tmp = REG_SET_FIELD(tmp, CP_GFX_HQD_QUEUE_PRIORITY, PRIORITY_LEVEL, 0);
	mqd->cp_gfx_hqd_queue_priority = tmp;

	/* set up time quantum */
	tmp = RREG32_SOC15(GC, 0, mmCP_GFX_HQD_QUANTUM);
	tmp = REG_SET_FIELD(tmp, CP_GFX_HQD_QUANTUM, QUANTUM_EN, 1);
	mqd->cp_gfx_hqd_quantum = tmp;

	/* set up gfx hqd base. this is similar as CP_RB_BASE */
	hqd_gpu_addr = ring->gpu_addr >> 8;
	mqd->cp_gfx_hqd_base = hqd_gpu_addr;
	mqd->cp_gfx_hqd_base_hi = upper_32_bits(hqd_gpu_addr);

	/* set up hqd_rptr_addr/_hi, similar as CP_RB_RPTR */
	wb_gpu_addr = adev->wb.gpu_addr + (ring->rptr_offs * 4);
	mqd->cp_gfx_hqd_rptr_addr = wb_gpu_addr & 0xfffffffc;
	mqd->cp_gfx_hqd_rptr_addr_hi =
		upper_32_bits(wb_gpu_addr) & 0xffff;

	/* set up rb_wptr_poll addr */
	wb_gpu_addr = adev->wb.gpu_addr + (ring->wptr_offs * 4);
	mqd->cp_rb_wptr_poll_addr_lo = wb_gpu_addr & 0xfffffffc;
	mqd->cp_rb_wptr_poll_addr_hi = upper_32_bits(wb_gpu_addr) & 0xffff;

	/* set up the gfx_hqd_control, similar as CP_RB0_CNTL */
	rb_bufsz = order_base_2(ring->ring_size / 4) - 1;
	tmp = RREG32_SOC15(GC, 0, mmCP_GFX_HQD_CNTL);
	tmp = REG_SET_FIELD(tmp, CP_GFX_HQD_CNTL, RB_BUFSZ, rb_bufsz);
	tmp = REG_SET_FIELD(tmp, CP_GFX_HQD_CNTL, RB_BLKSZ, rb_bufsz - 2);
#ifdef __BIG_ENDIAN
	tmp = REG_SET_FIELD(tmp, CP_GFX_HQD_CNTL, BUF_SWAP, 1);
#endif
	mqd->cp_gfx_hqd_cntl = tmp;

	/* set up cp_doorbell_control */
	tmp = RREG32_SOC15(GC, 0, mmCP_RB_DOORBELL_CONTROL);
	if (ring->use_doorbell) {
		tmp = REG_SET_FIELD(tmp, CP_RB_DOORBELL_CONTROL,
				    DOORBELL_OFFSET, ring->doorbell_index);
		tmp = REG_SET_FIELD(tmp, CP_RB_DOORBELL_CONTROL,
				    DOORBELL_EN, 1);
	} else
		tmp = REG_SET_FIELD(tmp, CP_RB_DOORBELL_CONTROL,
				    DOORBELL_EN, 0);
	mqd->cp_rb_doorbell_control = tmp;

	/* reset read and write pointers, similar to CP_RB0_WPTR/_RPTR */
	ring->wptr = 0;
	mqd->cp_gfx_hqd_rptr = RREG32_SOC15(GC, 0, mmCP_GFX_HQD_RPTR);

	/* active the queue */
	mqd->cp_gfx_hqd_active = 1;

	return 0;
}