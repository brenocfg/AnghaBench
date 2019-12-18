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
struct v9_mqd {int cp_hqd_eop_base_addr_lo; int cp_hqd_eop_base_addr_hi; int cp_hqd_eop_control; int cp_hqd_pq_doorbell_control; int cp_hqd_dequeue_request; int cp_hqd_pq_rptr; int cp_hqd_pq_wptr_lo; int cp_hqd_pq_wptr_hi; int cp_mqd_base_addr_lo; int cp_mqd_base_addr_hi; int cp_mqd_control; int cp_hqd_pq_base_lo; int cp_hqd_pq_base_hi; int cp_hqd_pq_control; int cp_hqd_pq_rptr_report_addr_lo; int cp_hqd_pq_rptr_report_addr_hi; int cp_hqd_pq_wptr_poll_addr_lo; int cp_hqd_pq_wptr_poll_addr_hi; int cp_hqd_vmid; int cp_hqd_persistent_state; int cp_hqd_active; } ;
struct amdgpu_ring {scalar_t__ use_doorbell; struct v9_mqd* mqd_ptr; struct amdgpu_device* adev; } ;
struct TYPE_2__ {int kiq; int userqueue_end; } ;
struct amdgpu_device {int usec_timeout; TYPE_1__ doorbell_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_PQ_STATUS ; 
 int /*<<< orphan*/  CP_PQ_WPTR_POLL_CNTL ; 
 int /*<<< orphan*/  DOORBELL_ENABLE ; 
 int /*<<< orphan*/  EN ; 
 int /*<<< orphan*/  GC ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_FIELD15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_SOC15_RLC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmCP_HQD_ACTIVE ; 
 int /*<<< orphan*/  mmCP_HQD_DEQUEUE_REQUEST ; 
 int /*<<< orphan*/  mmCP_HQD_EOP_BASE_ADDR ; 
 int /*<<< orphan*/  mmCP_HQD_EOP_BASE_ADDR_HI ; 
 int /*<<< orphan*/  mmCP_HQD_EOP_CONTROL ; 
 int /*<<< orphan*/  mmCP_HQD_PERSISTENT_STATE ; 
 int /*<<< orphan*/  mmCP_HQD_PQ_BASE ; 
 int /*<<< orphan*/  mmCP_HQD_PQ_BASE_HI ; 
 int /*<<< orphan*/  mmCP_HQD_PQ_CONTROL ; 
 int /*<<< orphan*/  mmCP_HQD_PQ_DOORBELL_CONTROL ; 
 int /*<<< orphan*/  mmCP_HQD_PQ_RPTR ; 
 int /*<<< orphan*/  mmCP_HQD_PQ_RPTR_REPORT_ADDR ; 
 int /*<<< orphan*/  mmCP_HQD_PQ_RPTR_REPORT_ADDR_HI ; 
 int /*<<< orphan*/  mmCP_HQD_PQ_WPTR_HI ; 
 int /*<<< orphan*/  mmCP_HQD_PQ_WPTR_LO ; 
 int /*<<< orphan*/  mmCP_HQD_PQ_WPTR_POLL_ADDR ; 
 int /*<<< orphan*/  mmCP_HQD_PQ_WPTR_POLL_ADDR_HI ; 
 int /*<<< orphan*/  mmCP_HQD_VMID ; 
 int /*<<< orphan*/  mmCP_MEC_DOORBELL_RANGE_LOWER ; 
 int /*<<< orphan*/  mmCP_MEC_DOORBELL_RANGE_UPPER ; 
 int /*<<< orphan*/  mmCP_MQD_BASE_ADDR ; 
 int /*<<< orphan*/  mmCP_MQD_BASE_ADDR_HI ; 
 int /*<<< orphan*/  mmCP_MQD_CONTROL ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int gfx_v9_0_kiq_init_register(struct amdgpu_ring *ring)
{
	struct amdgpu_device *adev = ring->adev;
	struct v9_mqd *mqd = ring->mqd_ptr;
	int j;

	/* disable wptr polling */
	WREG32_FIELD15(GC, 0, CP_PQ_WPTR_POLL_CNTL, EN, 0);

	WREG32_SOC15_RLC(GC, 0, mmCP_HQD_EOP_BASE_ADDR,
	       mqd->cp_hqd_eop_base_addr_lo);
	WREG32_SOC15_RLC(GC, 0, mmCP_HQD_EOP_BASE_ADDR_HI,
	       mqd->cp_hqd_eop_base_addr_hi);

	/* set the EOP size, register value is 2^(EOP_SIZE+1) dwords */
	WREG32_SOC15_RLC(GC, 0, mmCP_HQD_EOP_CONTROL,
	       mqd->cp_hqd_eop_control);

	/* enable doorbell? */
	WREG32_SOC15_RLC(GC, 0, mmCP_HQD_PQ_DOORBELL_CONTROL,
	       mqd->cp_hqd_pq_doorbell_control);

	/* disable the queue if it's active */
	if (RREG32_SOC15(GC, 0, mmCP_HQD_ACTIVE) & 1) {
		WREG32_SOC15_RLC(GC, 0, mmCP_HQD_DEQUEUE_REQUEST, 1);
		for (j = 0; j < adev->usec_timeout; j++) {
			if (!(RREG32_SOC15(GC, 0, mmCP_HQD_ACTIVE) & 1))
				break;
			udelay(1);
		}
		WREG32_SOC15_RLC(GC, 0, mmCP_HQD_DEQUEUE_REQUEST,
		       mqd->cp_hqd_dequeue_request);
		WREG32_SOC15_RLC(GC, 0, mmCP_HQD_PQ_RPTR,
		       mqd->cp_hqd_pq_rptr);
		WREG32_SOC15_RLC(GC, 0, mmCP_HQD_PQ_WPTR_LO,
		       mqd->cp_hqd_pq_wptr_lo);
		WREG32_SOC15_RLC(GC, 0, mmCP_HQD_PQ_WPTR_HI,
		       mqd->cp_hqd_pq_wptr_hi);
	}

	/* set the pointer to the MQD */
	WREG32_SOC15_RLC(GC, 0, mmCP_MQD_BASE_ADDR,
	       mqd->cp_mqd_base_addr_lo);
	WREG32_SOC15_RLC(GC, 0, mmCP_MQD_BASE_ADDR_HI,
	       mqd->cp_mqd_base_addr_hi);

	/* set MQD vmid to 0 */
	WREG32_SOC15_RLC(GC, 0, mmCP_MQD_CONTROL,
	       mqd->cp_mqd_control);

	/* set the pointer to the HQD, this is similar CP_RB0_BASE/_HI */
	WREG32_SOC15_RLC(GC, 0, mmCP_HQD_PQ_BASE,
	       mqd->cp_hqd_pq_base_lo);
	WREG32_SOC15_RLC(GC, 0, mmCP_HQD_PQ_BASE_HI,
	       mqd->cp_hqd_pq_base_hi);

	/* set up the HQD, this is similar to CP_RB0_CNTL */
	WREG32_SOC15_RLC(GC, 0, mmCP_HQD_PQ_CONTROL,
	       mqd->cp_hqd_pq_control);

	/* set the wb address whether it's enabled or not */
	WREG32_SOC15_RLC(GC, 0, mmCP_HQD_PQ_RPTR_REPORT_ADDR,
				mqd->cp_hqd_pq_rptr_report_addr_lo);
	WREG32_SOC15_RLC(GC, 0, mmCP_HQD_PQ_RPTR_REPORT_ADDR_HI,
				mqd->cp_hqd_pq_rptr_report_addr_hi);

	/* only used if CP_PQ_WPTR_POLL_CNTL.CP_PQ_WPTR_POLL_CNTL__EN_MASK=1 */
	WREG32_SOC15_RLC(GC, 0, mmCP_HQD_PQ_WPTR_POLL_ADDR,
	       mqd->cp_hqd_pq_wptr_poll_addr_lo);
	WREG32_SOC15_RLC(GC, 0, mmCP_HQD_PQ_WPTR_POLL_ADDR_HI,
	       mqd->cp_hqd_pq_wptr_poll_addr_hi);

	/* enable the doorbell if requested */
	if (ring->use_doorbell) {
		WREG32_SOC15(GC, 0, mmCP_MEC_DOORBELL_RANGE_LOWER,
					(adev->doorbell_index.kiq * 2) << 2);
		WREG32_SOC15(GC, 0, mmCP_MEC_DOORBELL_RANGE_UPPER,
					(adev->doorbell_index.userqueue_end * 2) << 2);
	}

	WREG32_SOC15_RLC(GC, 0, mmCP_HQD_PQ_DOORBELL_CONTROL,
	       mqd->cp_hqd_pq_doorbell_control);

	/* reset read and write pointers, similar to CP_RB0_WPTR/_RPTR */
	WREG32_SOC15_RLC(GC, 0, mmCP_HQD_PQ_WPTR_LO,
	       mqd->cp_hqd_pq_wptr_lo);
	WREG32_SOC15_RLC(GC, 0, mmCP_HQD_PQ_WPTR_HI,
	       mqd->cp_hqd_pq_wptr_hi);

	/* set the vmid for the queue */
	WREG32_SOC15_RLC(GC, 0, mmCP_HQD_VMID, mqd->cp_hqd_vmid);

	WREG32_SOC15_RLC(GC, 0, mmCP_HQD_PERSISTENT_STATE,
	       mqd->cp_hqd_persistent_state);

	/* activate the queue */
	WREG32_SOC15_RLC(GC, 0, mmCP_HQD_ACTIVE,
	       mqd->cp_hqd_active);

	if (ring->use_doorbell)
		WREG32_FIELD15(GC, 0, CP_PQ_STATUS, DOORBELL_ENABLE, 1);

	return 0;
}