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
struct i2c_bus_recovery_info {struct gpio_desc* sda_gpiod; int /*<<< orphan*/  unprepare_recovery; int /*<<< orphan*/  prepare_recovery; int /*<<< orphan*/  recover_bus; struct gpio_desc* scl_gpiod; } ;
struct i2c_adapter {struct i2c_bus_recovery_info* bus_recovery_info; } ;
struct gpio_desc {int dummy; } ;
struct dw_i2c_dev {int /*<<< orphan*/  dev; struct i2c_adapter adapter; struct i2c_bus_recovery_info rinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 scalar_t__ IS_ERR_OR_NULL (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int PTR_ERR_OR_ZERO (struct gpio_desc*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,char*) ; 
 struct gpio_desc* devm_gpiod_get_optional (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_dw_prepare_recovery ; 
 int /*<<< orphan*/  i2c_dw_unprepare_recovery ; 
 int /*<<< orphan*/  i2c_generic_scl_recovery ; 

__attribute__((used)) static int i2c_dw_init_recovery_info(struct dw_i2c_dev *dev)
{
	struct i2c_bus_recovery_info *rinfo = &dev->rinfo;
	struct i2c_adapter *adap = &dev->adapter;
	struct gpio_desc *gpio;

	gpio = devm_gpiod_get_optional(dev->dev, "scl", GPIOD_OUT_HIGH);
	if (IS_ERR_OR_NULL(gpio))
		return PTR_ERR_OR_ZERO(gpio);

	rinfo->scl_gpiod = gpio;

	gpio = devm_gpiod_get_optional(dev->dev, "sda", GPIOD_IN);
	if (IS_ERR(gpio))
		return PTR_ERR(gpio);
	rinfo->sda_gpiod = gpio;

	rinfo->recover_bus = i2c_generic_scl_recovery;
	rinfo->prepare_recovery = i2c_dw_prepare_recovery;
	rinfo->unprepare_recovery = i2c_dw_unprepare_recovery;
	adap->bus_recovery_info = rinfo;

	dev_info(dev->dev, "running with gpio recovery mode! scl%s",
		 rinfo->sda_gpiod ? ",sda" : "");

	return 0;
}