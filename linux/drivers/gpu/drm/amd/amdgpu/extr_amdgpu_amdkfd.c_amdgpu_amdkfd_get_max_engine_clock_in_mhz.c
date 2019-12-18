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
struct kgd_dev {int dummy; } ;
struct TYPE_4__ {scalar_t__ pp_funcs; } ;
struct TYPE_3__ {int default_sclk; } ;
struct amdgpu_device {TYPE_2__ powerplay; TYPE_1__ clock; } ;

/* Variables and functions */
 int amdgpu_dpm_get_sclk (struct amdgpu_device*,int) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 

uint32_t amdgpu_amdkfd_get_max_engine_clock_in_mhz(struct kgd_dev *kgd)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)kgd;

	/* the sclk is in quantas of 10kHz */
	if (amdgpu_sriov_vf(adev))
		return adev->clock.default_sclk / 100;
	else if (adev->powerplay.pp_funcs)
		return amdgpu_dpm_get_sclk(adev, false) / 100;
	else
		return 100;
}