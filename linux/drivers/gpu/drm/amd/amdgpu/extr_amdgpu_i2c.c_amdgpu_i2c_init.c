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
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int /*<<< orphan*/  amdgpu_atombios_i2c_init (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_hw_i2c ; 

void amdgpu_i2c_init(struct amdgpu_device *adev)
{
	if (amdgpu_hw_i2c)
		DRM_INFO("hw_i2c forced on, you may experience display detection problems!\n");

	amdgpu_atombios_i2c_init(adev);
}