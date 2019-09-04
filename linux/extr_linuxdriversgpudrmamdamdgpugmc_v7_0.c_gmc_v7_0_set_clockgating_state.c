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
struct amdgpu_device {int flags; } ;
typedef  enum amd_clockgating_state { ____Placeholder_amd_clockgating_state } amd_clockgating_state ;

/* Variables and functions */
 int AMD_CG_STATE_GATE ; 
 int AMD_IS_APU ; 
 int /*<<< orphan*/  gmc_v7_0_enable_bif_mgls (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gmc_v7_0_enable_hdp_ls (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gmc_v7_0_enable_hdp_mgcg (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gmc_v7_0_enable_mc_ls (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gmc_v7_0_enable_mc_mgcg (struct amdgpu_device*,int) ; 

__attribute__((used)) static int gmc_v7_0_set_clockgating_state(void *handle,
					  enum amd_clockgating_state state)
{
	bool gate = false;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	if (state == AMD_CG_STATE_GATE)
		gate = true;

	if (!(adev->flags & AMD_IS_APU)) {
		gmc_v7_0_enable_mc_mgcg(adev, gate);
		gmc_v7_0_enable_mc_ls(adev, gate);
	}
	gmc_v7_0_enable_bif_mgls(adev, gate);
	gmc_v7_0_enable_hdp_mgcg(adev, gate);
	gmc_v7_0_enable_hdp_ls(adev, gate);

	return 0;
}