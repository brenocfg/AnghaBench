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
struct cik_mqd {scalar_t__ cp_mqd_base_addr_lo; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_PQ_WPTR_POLL_CNTL ; 
 int /*<<< orphan*/  EN ; 
 scalar_t__ REG_SET_FIELD (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RREG32 (scalar_t__) ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,scalar_t__) ; 
 scalar_t__ mmCP_HQD_ACTIVE ; 
 scalar_t__ mmCP_HQD_VMID ; 
 scalar_t__ mmCP_MQD_BASE_ADDR ; 
 scalar_t__ mmCP_MQD_CONTROL ; 
 scalar_t__ mmCP_PQ_WPTR_POLL_CNTL ; 

int gfx_v7_0_mqd_commit(struct amdgpu_device *adev, struct cik_mqd *mqd)
{
	uint32_t tmp;
	uint32_t mqd_reg;
	uint32_t *mqd_data;

	/* HQD registers extend from mmCP_MQD_BASE_ADDR to mmCP_MQD_CONTROL */
	mqd_data = &mqd->cp_mqd_base_addr_lo;

	/* disable wptr polling */
	tmp = RREG32(mmCP_PQ_WPTR_POLL_CNTL);
	tmp = REG_SET_FIELD(tmp, CP_PQ_WPTR_POLL_CNTL, EN, 0);
	WREG32(mmCP_PQ_WPTR_POLL_CNTL, tmp);

	/* program all HQD registers */
	for (mqd_reg = mmCP_HQD_VMID; mqd_reg <= mmCP_MQD_CONTROL; mqd_reg++)
		WREG32(mqd_reg, mqd_data[mqd_reg - mmCP_MQD_BASE_ADDR]);

	/* activate the HQD */
	for (mqd_reg = mmCP_MQD_BASE_ADDR; mqd_reg <= mmCP_HQD_ACTIVE; mqd_reg++)
		WREG32(mqd_reg, mqd_data[mqd_reg - mmCP_MQD_BASE_ADDR]);

	return 0;
}