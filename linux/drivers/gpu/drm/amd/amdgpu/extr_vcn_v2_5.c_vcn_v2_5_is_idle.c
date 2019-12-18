#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int num_vcn_inst; int harvest_config; } ;
struct amdgpu_device {TYPE_1__ vcn; } ;

/* Variables and functions */
 scalar_t__ RREG32_SOC15 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ UVD_STATUS__IDLE ; 
 int /*<<< orphan*/  VCN ; 
 int /*<<< orphan*/  mmUVD_STATUS ; 

__attribute__((used)) static bool vcn_v2_5_is_idle(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	int i, ret = 1;

	for (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
		if (adev->vcn.harvest_config & (1 << i))
			continue;
		ret &= (RREG32_SOC15(VCN, i, mmUVD_STATUS) == UVD_STATUS__IDLE);
	}

	return ret;
}