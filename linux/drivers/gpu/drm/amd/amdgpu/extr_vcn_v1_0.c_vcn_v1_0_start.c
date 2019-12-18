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
struct amdgpu_device {int pg_flags; } ;

/* Variables and functions */
 int AMD_PG_SUPPORT_VCN_DPG ; 
 int vcn_v1_0_start_dpg_mode (struct amdgpu_device*) ; 
 int vcn_v1_0_start_spg_mode (struct amdgpu_device*) ; 

__attribute__((used)) static int vcn_v1_0_start(struct amdgpu_device *adev)
{
	int r;

	if (adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG)
		r = vcn_v1_0_start_dpg_mode(adev);
	else
		r = vcn_v1_0_start_spg_mode(adev);
	return r;
}