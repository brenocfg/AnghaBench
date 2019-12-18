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
typedef  int u32 ;
struct radeon_device {int cg_flags; } ;

/* Variables and functions */
 int MST_MEM_LS_EN ; 
 int /*<<< orphan*/  PCIE_CNTL2 ; 
 int RADEON_CG_SUPPORT_BIF_LS ; 
 int REPLAY_MEM_LS_EN ; 
 int RREG32_PCIE (int /*<<< orphan*/ ) ; 
 int SLV_MEM_AGGRESSIVE_LS_EN ; 
 int SLV_MEM_LS_EN ; 
 int /*<<< orphan*/  WREG32_PCIE (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void si_enable_bif_mgls(struct radeon_device *rdev,
			       bool enable)
{
	u32 orig, data;

	orig = data = RREG32_PCIE(PCIE_CNTL2);

	if (enable && (rdev->cg_flags & RADEON_CG_SUPPORT_BIF_LS))
		data |= SLV_MEM_LS_EN | MST_MEM_LS_EN |
			REPLAY_MEM_LS_EN | SLV_MEM_AGGRESSIVE_LS_EN;
	else
		data &= ~(SLV_MEM_LS_EN | MST_MEM_LS_EN |
			  REPLAY_MEM_LS_EN | SLV_MEM_AGGRESSIVE_LS_EN);

	if (orig != data)
		WREG32_PCIE(PCIE_CNTL2, data);
}