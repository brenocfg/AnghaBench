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

/* Variables and functions */
 int kv_force_dpm_lowest (struct amdgpu_device*) ; 

__attribute__((used)) static int kv_force_lowest_valid(struct amdgpu_device *adev)
{
	return kv_force_dpm_lowest(adev);
}