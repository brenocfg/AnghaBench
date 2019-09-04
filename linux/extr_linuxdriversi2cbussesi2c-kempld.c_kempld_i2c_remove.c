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
struct platform_device {int dummy; } ;
struct kempld_i2c_data {int /*<<< orphan*/  adap; int /*<<< orphan*/  was_active; struct kempld_device_data* pld; } ;
struct kempld_device_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_CTRL_EN ; 
 int /*<<< orphan*/  KEMPLD_I2C_CTRL ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kempld_get_mutex (struct kempld_device_data*) ; 
 int /*<<< orphan*/  kempld_read8 (struct kempld_device_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kempld_release_mutex (struct kempld_device_data*) ; 
 int /*<<< orphan*/  kempld_write8 (struct kempld_device_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct kempld_i2c_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int kempld_i2c_remove(struct platform_device *pdev)
{
	struct kempld_i2c_data *i2c = platform_get_drvdata(pdev);
	struct kempld_device_data *pld = i2c->pld;
	u8 ctrl;

	kempld_get_mutex(pld);
	/*
	 * Disable I2C logic if it was not activated before the
	 * driver loaded
	 */
	if (!i2c->was_active) {
		ctrl = kempld_read8(pld, KEMPLD_I2C_CTRL);
		ctrl &= ~I2C_CTRL_EN;
		kempld_write8(pld, KEMPLD_I2C_CTRL, ctrl);
	}
	kempld_release_mutex(pld);

	i2c_del_adapter(&i2c->adap);

	return 0;
}