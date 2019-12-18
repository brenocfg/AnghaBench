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
typedef  int /*<<< orphan*/  u32 ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_CG_SUPPORT_BIF_LS ; 
 int /*<<< orphan*/  AMD_CG_SUPPORT_BIF_MGCG ; 
 int CPM_CONTROL__LCLK_DYN_GATE_ENABLE_MASK ; 
 int PCIE_CNTL2__SLV_MEM_LS_EN_MASK ; 
 int RREG32_PCIE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smnCPM_CONTROL ; 
 int /*<<< orphan*/  smnPCIE_CNTL2 ; 

__attribute__((used)) static void nbio_v7_0_get_clockgating_state(struct amdgpu_device *adev,
					    u32 *flags)
{
	int data;

	/* AMD_CG_SUPPORT_BIF_MGCG */
	data = RREG32_PCIE(smnCPM_CONTROL);
	if (data & CPM_CONTROL__LCLK_DYN_GATE_ENABLE_MASK)
		*flags |= AMD_CG_SUPPORT_BIF_MGCG;

	/* AMD_CG_SUPPORT_BIF_LS */
	data = RREG32_PCIE(smnPCIE_CNTL2);
	if (data & PCIE_CNTL2__SLV_MEM_LS_EN_MASK)
		*flags |= AMD_CG_SUPPORT_BIF_LS;
}