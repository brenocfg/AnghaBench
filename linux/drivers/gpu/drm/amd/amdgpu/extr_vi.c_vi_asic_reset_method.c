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
struct amdgpu_device {int dummy; } ;
typedef  enum amd_reset_method { ____Placeholder_amd_reset_method } amd_reset_method ;

/* Variables and functions */
 int AMD_RESET_METHOD_LEGACY ; 

__attribute__((used)) static enum amd_reset_method
vi_asic_reset_method(struct amdgpu_device *adev)
{
	return AMD_RESET_METHOD_LEGACY;
}