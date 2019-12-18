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
struct smu_context {int dummy; } ;
struct amdgpu_device {struct smu_context smu; } ;
typedef  enum amd_reset_method { ____Placeholder_amd_reset_method } amd_reset_method ;

/* Variables and functions */
 int AMD_RESET_METHOD_BACO ; 
 int AMD_RESET_METHOD_MODE1 ; 
 scalar_t__ smu_baco_is_support (struct smu_context*) ; 

__attribute__((used)) static enum amd_reset_method
nv_asic_reset_method(struct amdgpu_device *adev)
{
	struct smu_context *smu = &adev->smu;

	if (smu_baco_is_support(smu))
		return AMD_RESET_METHOD_BACO;
	else
		return AMD_RESET_METHOD_MODE1;
}