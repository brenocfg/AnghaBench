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
struct i2c_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct fc0011_priv {TYPE_1__* i2c; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int i2c_transfer (TYPE_1__*,struct i2c_msg*,int) ; 

__attribute__((used)) static int fc0011_readreg(struct fc0011_priv *priv, u8 reg, u8 *val)
{
	u8 dummy;
	struct i2c_msg msg[2] = {
		{ .addr = priv->addr,
		  .flags = 0, .buf = &reg, .len = 1 },
		{ .addr = priv->addr,
		  .flags = I2C_M_RD, .buf = val ? : &dummy, .len = 1 },
	};

	if (i2c_transfer(priv->i2c, msg, 2) != 2) {
		dev_err(&priv->i2c->dev,
			"I2C read failed, reg: %02x\n", reg);
		return -EIO;
	}

	return 0;
}