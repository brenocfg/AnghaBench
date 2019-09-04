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
struct amdgpu_device {int cg_flags; } ;

/* Variables and functions */
 int AMD_CG_SUPPORT_UVD_MGCG ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int RREG32_UVD_CTX (int /*<<< orphan*/ ) ; 
 int UVD_CGC_CTRL__DYN_CLOCK_MODE_MASK ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_UVD_CTX (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ixUVD_CGC_MEM_CTRL ; 
 int /*<<< orphan*/  mmUVD_CGC_CTRL ; 

__attribute__((used)) static void uvd_v5_0_enable_mgcg(struct amdgpu_device *adev,
				 bool enable)
{
	u32 orig, data;

	if (enable && (adev->cg_flags & AMD_CG_SUPPORT_UVD_MGCG)) {
		data = RREG32_UVD_CTX(ixUVD_CGC_MEM_CTRL);
		data |= 0xfff;
		WREG32_UVD_CTX(ixUVD_CGC_MEM_CTRL, data);

		orig = data = RREG32(mmUVD_CGC_CTRL);
		data |= UVD_CGC_CTRL__DYN_CLOCK_MODE_MASK;
		if (orig != data)
			WREG32(mmUVD_CGC_CTRL, data);
	} else {
		data = RREG32_UVD_CTX(ixUVD_CGC_MEM_CTRL);
		data &= ~0xfff;
		WREG32_UVD_CTX(ixUVD_CGC_MEM_CTRL, data);

		orig = data = RREG32(mmUVD_CGC_CTRL);
		data &= ~UVD_CGC_CTRL__DYN_CLOCK_MODE_MASK;
		if (orig != data)
			WREG32(mmUVD_CGC_CTRL, data);
	}
}