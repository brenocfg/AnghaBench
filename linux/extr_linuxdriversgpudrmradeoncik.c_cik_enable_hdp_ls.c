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
struct radeon_device {int cg_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDP_LS_ENABLE ; 
 int /*<<< orphan*/  HDP_MEM_POWER_LS ; 
 int RADEON_CG_SUPPORT_HDP_LS ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cik_enable_hdp_ls(struct radeon_device *rdev,
			      bool enable)
{
	u32 orig, data;

	orig = data = RREG32(HDP_MEM_POWER_LS);

	if (enable && (rdev->cg_flags & RADEON_CG_SUPPORT_HDP_LS))
		data |= HDP_LS_ENABLE;
	else
		data &= ~HDP_LS_ENABLE;

	if (orig != data)
		WREG32(HDP_MEM_POWER_LS, data);
}