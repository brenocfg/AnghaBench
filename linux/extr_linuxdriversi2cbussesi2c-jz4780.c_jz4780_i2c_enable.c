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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct jz4780_i2c {TYPE_1__ adap; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  JZ4780_I2C_ENB ; 
 unsigned short JZ4780_I2C_ENB_I2C ; 
 int /*<<< orphan*/  JZ4780_I2C_ENSTA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned short) ; 
 unsigned short jz4780_i2c_readw (struct jz4780_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jz4780_i2c_writew (struct jz4780_i2c*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int jz4780_i2c_enable(struct jz4780_i2c *i2c)
{
	unsigned short regval;
	unsigned long loops = 5;

	jz4780_i2c_writew(i2c, JZ4780_I2C_ENB, 1);

	do {
		regval = jz4780_i2c_readw(i2c, JZ4780_I2C_ENSTA);
		if (regval & JZ4780_I2C_ENB_I2C)
			return 0;

		usleep_range(5000, 15000);
	} while (--loops);

	dev_err(&i2c->adap.dev, "enable failed: ENSTA=0x%04x\n", regval);
	return -ETIMEDOUT;
}