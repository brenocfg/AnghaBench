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
struct amdgpu_device {int /*<<< orphan*/ ** i2c_bus; } ;

/* Variables and functions */
 int AMDGPU_MAX_I2C_BUS ; 
 int /*<<< orphan*/  amdgpu_i2c_destroy (int /*<<< orphan*/ *) ; 

void amdgpu_i2c_fini(struct amdgpu_device *adev)
{
	int i;

	for (i = 0; i < AMDGPU_MAX_I2C_BUS; i++) {
		if (adev->i2c_bus[i]) {
			amdgpu_i2c_destroy(adev->i2c_bus[i]);
			adev->i2c_bus[i] = NULL;
		}
	}
}