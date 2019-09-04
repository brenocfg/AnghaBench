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
typedef  scalar_t__ u32 ;
struct amdgpu_device {int cg_flags; } ;

/* Variables and functions */
 int AMD_CG_SUPPORT_BIF_LS ; 
 int /*<<< orphan*/  MST_MEM_LS_EN ; 
 int /*<<< orphan*/  PCIE_CNTL2 ; 
 scalar_t__ REG_SET_FIELD (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REPLAY_MEM_LS_EN ; 
 scalar_t__ RREG32_PCIE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLV_MEM_AGGRESSIVE_LS_EN ; 
 int /*<<< orphan*/  SLV_MEM_LS_EN ; 
 int /*<<< orphan*/  WREG32_PCIE (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ixPCIE_CNTL2 ; 

__attribute__((used)) static void gmc_v7_0_enable_bif_mgls(struct amdgpu_device *adev,
				     bool enable)
{
	u32 orig, data;

	orig = data = RREG32_PCIE(ixPCIE_CNTL2);

	if (enable && (adev->cg_flags & AMD_CG_SUPPORT_BIF_LS)) {
		data = REG_SET_FIELD(data, PCIE_CNTL2, SLV_MEM_LS_EN, 1);
		data = REG_SET_FIELD(data, PCIE_CNTL2, MST_MEM_LS_EN, 1);
		data = REG_SET_FIELD(data, PCIE_CNTL2, REPLAY_MEM_LS_EN, 1);
		data = REG_SET_FIELD(data, PCIE_CNTL2, SLV_MEM_AGGRESSIVE_LS_EN, 1);
	} else {
		data = REG_SET_FIELD(data, PCIE_CNTL2, SLV_MEM_LS_EN, 0);
		data = REG_SET_FIELD(data, PCIE_CNTL2, MST_MEM_LS_EN, 0);
		data = REG_SET_FIELD(data, PCIE_CNTL2, REPLAY_MEM_LS_EN, 0);
		data = REG_SET_FIELD(data, PCIE_CNTL2, SLV_MEM_AGGRESSIVE_LS_EN, 0);
	}

	if (orig != data)
		WREG32_PCIE(ixPCIE_CNTL2, data);
}