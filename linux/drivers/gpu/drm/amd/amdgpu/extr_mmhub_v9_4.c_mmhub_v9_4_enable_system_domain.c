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
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENABLE_CONTEXT ; 
 int /*<<< orphan*/  MMHUB ; 
 int MMHUB_INSTANCE_REGISTER_OFFSET ; 
 int /*<<< orphan*/  PAGE_TABLE_DEPTH ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RREG32_SOC15_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VML2VC0_VM_CONTEXT0_CNTL ; 
 int /*<<< orphan*/  WREG32_SOC15_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmVML2VC0_VM_CONTEXT0_CNTL ; 

__attribute__((used)) static void mmhub_v9_4_enable_system_domain(struct amdgpu_device *adev,
					    int hubid)
{
	uint32_t tmp;

	tmp = RREG32_SOC15_OFFSET(MMHUB, 0, mmVML2VC0_VM_CONTEXT0_CNTL,
				  hubid * MMHUB_INSTANCE_REGISTER_OFFSET);
	tmp = REG_SET_FIELD(tmp, VML2VC0_VM_CONTEXT0_CNTL, ENABLE_CONTEXT, 1);
	tmp = REG_SET_FIELD(tmp, VML2VC0_VM_CONTEXT0_CNTL, PAGE_TABLE_DEPTH, 0);
	WREG32_SOC15_OFFSET(MMHUB, 0, mmVML2VC0_VM_CONTEXT0_CNTL,
			    hubid * MMHUB_INSTANCE_REGISTER_OFFSET, tmp);
}