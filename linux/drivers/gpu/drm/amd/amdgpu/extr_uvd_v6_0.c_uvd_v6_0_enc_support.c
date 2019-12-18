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
struct TYPE_2__ {scalar_t__ fw_version; } ;
struct amdgpu_device {scalar_t__ asic_type; TYPE_1__ uvd; } ;

/* Variables and functions */
 scalar_t__ CHIP_POLARIS10 ; 
 scalar_t__ CHIP_VEGAM ; 
 scalar_t__ FW_1_130_16 ; 

__attribute__((used)) static inline bool uvd_v6_0_enc_support(struct amdgpu_device *adev)
{
	return ((adev->asic_type >= CHIP_POLARIS10) &&
			(adev->asic_type <= CHIP_VEGAM) &&
			(!adev->uvd.fw_version || adev->uvd.fw_version >= FW_1_130_16));
}