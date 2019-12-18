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
 int DCM ; 
 int RADEON_CG_SUPPORT_UVD_MGCG ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int RREG32_UVD_CTX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UVD_CGC_CTRL ; 
 int /*<<< orphan*/  UVD_CGC_MEM_CTRL ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_UVD_CTX (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cik_enable_uvd_mgcg(struct radeon_device *rdev,
				bool enable)
{
	u32 orig, data;

	if (enable && (rdev->cg_flags & RADEON_CG_SUPPORT_UVD_MGCG)) {
		data = RREG32_UVD_CTX(UVD_CGC_MEM_CTRL);
		data = 0xfff;
		WREG32_UVD_CTX(UVD_CGC_MEM_CTRL, data);

		orig = data = RREG32(UVD_CGC_CTRL);
		data |= DCM;
		if (orig != data)
			WREG32(UVD_CGC_CTRL, data);
	} else {
		data = RREG32_UVD_CTX(UVD_CGC_MEM_CTRL);
		data &= ~0xfff;
		WREG32_UVD_CTX(UVD_CGC_MEM_CTRL, data);

		orig = data = RREG32(UVD_CGC_CTRL);
		data &= ~DCM;
		if (orig != data)
			WREG32(UVD_CGC_CTRL, data);
	}
}