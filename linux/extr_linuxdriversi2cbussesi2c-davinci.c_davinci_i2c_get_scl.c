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
 int DAVINCI_I2C_DIN_PDIN0 ; 
 int /*<<< orphan*/  DAVINCI_I2C_DIN_REG ; 
 int davinci_i2c_read_reg (struct davinci_i2c_dev*,int /*<<< orphan*/ ) ; 
 struct davinci_i2c_dev* i2c_get_adapdata (struct i2c_adapter*) ; 

__attribute__((used)) static int davinci_i2c_get_scl(struct i2c_adapter *adap)
{
	struct davinci_i2c_dev *dev = i2c_get_adapdata(adap);
	int val;

	/* read the state of SCL */
	val = davinci_i2c_read_reg(dev, DAVINCI_I2C_DIN_REG);
	return val & DAVINCI_I2C_DIN_PDIN0;
}