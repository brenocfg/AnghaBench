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
struct i2c_adapter {int dummy; } ;
struct davinci_i2c_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAVINCI_I2C_FUNC_REG ; 
 int /*<<< orphan*/  davinci_i2c_unprepare_recovery (struct i2c_adapter*) ; 
 int /*<<< orphan*/  davinci_i2c_write_reg (struct davinci_i2c_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct davinci_i2c_dev* i2c_get_adapdata (struct i2c_adapter*) ; 

__attribute__((used)) static void davinci_i2c_scl_unprepare_recovery(struct i2c_adapter *adap)
{
	struct davinci_i2c_dev *dev = i2c_get_adapdata(adap);

	/* change back to I2C mode */
	davinci_i2c_write_reg(dev, DAVINCI_I2C_FUNC_REG, 0);

	davinci_i2c_unprepare_recovery(adap);
}