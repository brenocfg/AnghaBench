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
struct amdgpu_device {int flags; } ;

/* Variables and functions */
 int AMD_IS_APU ; 
 int /*<<< orphan*/  ixCG_DCLK_CNTL ; 
 int /*<<< orphan*/  ixCG_DCLK_STATUS ; 
 int /*<<< orphan*/  ixCG_VCLK_CNTL ; 
 int /*<<< orphan*/  ixCG_VCLK_STATUS ; 
 int /*<<< orphan*/  ixGNB_CLK1_DFS_CNTL ; 
 int /*<<< orphan*/  ixGNB_CLK1_STATUS ; 
 int /*<<< orphan*/  ixGNB_CLK2_DFS_CNTL ; 
 int /*<<< orphan*/  ixGNB_CLK2_STATUS ; 
 int vi_set_uvd_clock (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vi_set_uvd_clocks(struct amdgpu_device *adev, u32 vclk, u32 dclk)
{
	int r;

	if (adev->flags & AMD_IS_APU) {
		r = vi_set_uvd_clock(adev, vclk, ixGNB_CLK2_DFS_CNTL, ixGNB_CLK2_STATUS);
		if (r)
			return r;

		r = vi_set_uvd_clock(adev, dclk, ixGNB_CLK1_DFS_CNTL, ixGNB_CLK1_STATUS);
		if (r)
			return r;
	} else {
		r = vi_set_uvd_clock(adev, vclk, ixCG_VCLK_CNTL, ixCG_VCLK_STATUS);
		if (r)
			return r;

		r = vi_set_uvd_clock(adev, dclk, ixCG_DCLK_CNTL, ixCG_DCLK_STATUS);
		if (r)
			return r;
	}

	return 0;
}