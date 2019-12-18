#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct st_sensors_platform_data {int drdy_int_pin; } ;
struct st_lsm6dsx_hw {struct device* dev; TYPE_1__* settings; } ;
struct device {scalar_t__ platform_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  int2_addr; int /*<<< orphan*/  int1_addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ st_lsm6dsx_of_get_drdy_pin (struct st_lsm6dsx_hw*,int*) ; 

__attribute__((used)) static int st_lsm6dsx_get_drdy_reg(struct st_lsm6dsx_hw *hw, u8 *drdy_reg)
{
	int err = 0, drdy_pin;

	if (st_lsm6dsx_of_get_drdy_pin(hw, &drdy_pin) < 0) {
		struct st_sensors_platform_data *pdata;
		struct device *dev = hw->dev;

		pdata = (struct st_sensors_platform_data *)dev->platform_data;
		drdy_pin = pdata ? pdata->drdy_int_pin : 1;
	}

	switch (drdy_pin) {
	case 1:
		*drdy_reg = hw->settings->int1_addr;
		break;
	case 2:
		*drdy_reg = hw->settings->int2_addr;
		break;
	default:
		dev_err(hw->dev, "unsupported data ready pin\n");
		err = -EINVAL;
		break;
	}

	return err;
}