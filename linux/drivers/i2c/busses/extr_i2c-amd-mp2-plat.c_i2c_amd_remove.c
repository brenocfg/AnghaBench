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
struct platform_device {int dummy; } ;
struct amd_i2c_common {int /*<<< orphan*/ * mp2_dev; } ;
struct amd_i2c_dev {int /*<<< orphan*/  adap; struct amd_i2c_common common; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_LOCK_ROOT_ADAPTER ; 
 int /*<<< orphan*/  amd_mp2_unregister_cb (struct amd_i2c_common*) ; 
 int /*<<< orphan*/  i2c_amd_enable_set (struct amd_i2c_dev*,int) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_lock_bus (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_unlock_bus (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct amd_i2c_dev* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int i2c_amd_remove(struct platform_device *pdev)
{
	struct amd_i2c_dev *i2c_dev = platform_get_drvdata(pdev);
	struct amd_i2c_common *i2c_common = &i2c_dev->common;

	i2c_lock_bus(&i2c_dev->adap, I2C_LOCK_ROOT_ADAPTER);

	i2c_amd_enable_set(i2c_dev, false);
	amd_mp2_unregister_cb(i2c_common);
	i2c_common->mp2_dev = NULL;

	i2c_unlock_bus(&i2c_dev->adap, I2C_LOCK_ROOT_ADAPTER);

	i2c_del_adapter(&i2c_dev->adap);
	return 0;
}