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
typedef  int /*<<< orphan*/  u8 ;
struct amdgpu_device {int dummy; } ;
typedef  int /*<<< orphan*/  ATOM_GPIO_I2C_ASSIGMENT ;

/* Variables and functions */

__attribute__((used)) static void amdgpu_atombios_lookup_i2c_gpio_quirks(struct amdgpu_device *adev,
					  ATOM_GPIO_I2C_ASSIGMENT *gpio,
					  u8 index)
{

}