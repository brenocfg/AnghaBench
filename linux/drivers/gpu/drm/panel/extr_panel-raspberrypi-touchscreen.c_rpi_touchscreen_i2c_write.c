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
struct rpi_touchscreen {TYPE_1__* dsi; int /*<<< orphan*/  i2c; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rpi_touchscreen_i2c_write(struct rpi_touchscreen *ts,
				      u8 reg, u8 val)
{
	int ret;

	ret = i2c_smbus_write_byte_data(ts->i2c, reg, val);
	if (ret)
		dev_err(&ts->dsi->dev, "I2C write failed: %d\n", ret);
}