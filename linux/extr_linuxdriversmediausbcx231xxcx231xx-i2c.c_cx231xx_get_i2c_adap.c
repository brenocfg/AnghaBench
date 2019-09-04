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
struct i2c_adapter {int dummy; } ;
struct cx231xx {TYPE_2__* muxc; TYPE_1__* i2c_bus; } ;
struct TYPE_4__ {struct i2c_adapter** adapter; } ;
struct TYPE_3__ {struct i2c_adapter i2c_adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  I2C_0 132 
#define  I2C_1 131 
#define  I2C_1_MUX_1 130 
#define  I2C_1_MUX_3 129 
#define  I2C_2 128 

struct i2c_adapter *cx231xx_get_i2c_adap(struct cx231xx *dev, int i2c_port)
{
	switch (i2c_port) {
	case I2C_0:
		return &dev->i2c_bus[0].i2c_adap;
	case I2C_1:
		return &dev->i2c_bus[1].i2c_adap;
	case I2C_2:
		return &dev->i2c_bus[2].i2c_adap;
	case I2C_1_MUX_1:
		return dev->muxc->adapter[0];
	case I2C_1_MUX_3:
		return dev->muxc->adapter[1];
	default:
		BUG();
	}
}