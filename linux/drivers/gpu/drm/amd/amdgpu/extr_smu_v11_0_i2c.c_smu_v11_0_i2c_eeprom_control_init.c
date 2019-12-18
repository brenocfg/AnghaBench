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
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct i2c_adapter {int /*<<< orphan*/ * lock_ops; int /*<<< orphan*/  name; int /*<<< orphan*/ * algo; TYPE_2__ dev; int /*<<< orphan*/  class; int /*<<< orphan*/  owner; } ;
struct amdgpu_device {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  I2C_CLASS_SPD ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int i2c_add_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  smu_v11_0_i2c_eeprom_i2c_algo ; 
 int /*<<< orphan*/  smu_v11_0_i2c_i2c_lock_ops ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*) ; 
 struct amdgpu_device* to_amdgpu_device (struct i2c_adapter*) ; 

int smu_v11_0_i2c_eeprom_control_init(struct i2c_adapter *control)
{
	struct amdgpu_device *adev = to_amdgpu_device(control);
	int res;

	control->owner = THIS_MODULE;
	control->class = I2C_CLASS_SPD;
	control->dev.parent = &adev->pdev->dev;
	control->algo = &smu_v11_0_i2c_eeprom_i2c_algo;
	snprintf(control->name, sizeof(control->name), "RAS EEPROM");
	control->lock_ops = &smu_v11_0_i2c_i2c_lock_ops;

	res = i2c_add_adapter(control);
	if (res)
		DRM_ERROR("Failed to register hw i2c, err: %d\n", res);

	return res;
}