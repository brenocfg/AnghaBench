#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  pp_handle; TYPE_1__* pp_funcs; } ;
struct amdgpu_device {TYPE_2__ powerplay; int /*<<< orphan*/  smu; } ;
struct TYPE_3__ {int (* get_sclk ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SMU_GFXCLK ; 
 scalar_t__ is_support_sw_smu (struct amdgpu_device*) ; 
 int smu_get_dpm_freq_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

int amdgpu_dpm_get_sclk(struct amdgpu_device *adev, bool low)
{
	uint32_t clk_freq;
	int ret = 0;
	if (is_support_sw_smu(adev)) {
		ret = smu_get_dpm_freq_range(&adev->smu, SMU_GFXCLK,
					     low ? &clk_freq : NULL,
					     !low ? &clk_freq : NULL);
		if (ret)
			return 0;
		return clk_freq * 100;

	} else {
		return (adev)->powerplay.pp_funcs->get_sclk((adev)->powerplay.pp_handle, (low));
	}
}