#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct vi_mqd {scalar_t__ cp_mqd_base_addr_lo; scalar_t__ cp_hqd_eop_rptr; scalar_t__ cp_hqd_eop_wptr; scalar_t__ cp_hqd_eop_wptr_mem; } ;
struct amdgpu_device {scalar_t__ asic_type; } ;

/* Variables and functions */
 scalar_t__ CHIP_TONGA ; 
 int /*<<< orphan*/  CP_PQ_WPTR_POLL_CNTL ; 
 int /*<<< orphan*/  EN ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  WREG32_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mmCP_HQD_ACTIVE ; 
 scalar_t__ mmCP_HQD_EOP_CONTROL ; 
 scalar_t__ mmCP_HQD_EOP_EVENTS ; 
 scalar_t__ mmCP_HQD_EOP_RPTR ; 
 scalar_t__ mmCP_HQD_EOP_WPTR ; 
 scalar_t__ mmCP_HQD_EOP_WPTR_MEM ; 
 scalar_t__ mmCP_HQD_ERROR ; 
 scalar_t__ mmCP_HQD_VMID ; 
 scalar_t__ mmCP_MQD_BASE_ADDR ; 

int gfx_v8_0_mqd_commit(struct amdgpu_device *adev,
			struct vi_mqd *mqd)
{
	uint32_t mqd_reg;
	uint32_t *mqd_data;

	/* HQD registers extend from mmCP_MQD_BASE_ADDR to mmCP_HQD_ERROR */
	mqd_data = &mqd->cp_mqd_base_addr_lo;

	/* disable wptr polling */
	WREG32_FIELD(CP_PQ_WPTR_POLL_CNTL, EN, 0);

	/* program all HQD registers */
	for (mqd_reg = mmCP_HQD_VMID; mqd_reg <= mmCP_HQD_EOP_CONTROL; mqd_reg++)
		WREG32(mqd_reg, mqd_data[mqd_reg - mmCP_MQD_BASE_ADDR]);

	/* Tonga errata: EOP RPTR/WPTR should be left unmodified.
	 * This is safe since EOP RPTR==WPTR for any inactive HQD
	 * on ASICs that do not support context-save.
	 * EOP writes/reads can start anywhere in the ring.
	 */
	if (adev->asic_type != CHIP_TONGA) {
		WREG32(mmCP_HQD_EOP_RPTR, mqd->cp_hqd_eop_rptr);
		WREG32(mmCP_HQD_EOP_WPTR, mqd->cp_hqd_eop_wptr);
		WREG32(mmCP_HQD_EOP_WPTR_MEM, mqd->cp_hqd_eop_wptr_mem);
	}

	for (mqd_reg = mmCP_HQD_EOP_EVENTS; mqd_reg <= mmCP_HQD_ERROR; mqd_reg++)
		WREG32(mqd_reg, mqd_data[mqd_reg - mmCP_MQD_BASE_ADDR]);

	/* activate the HQD */
	for (mqd_reg = mmCP_MQD_BASE_ADDR; mqd_reg <= mmCP_HQD_ACTIVE; mqd_reg++)
		WREG32(mqd_reg, mqd_data[mqd_reg - mmCP_MQD_BASE_ADDR]);

	return 0;
}