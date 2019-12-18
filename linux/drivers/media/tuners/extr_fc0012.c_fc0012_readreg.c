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
typedef  int /*<<< orphan*/  u8 ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct fc0012_priv {TYPE_2__* i2c; TYPE_1__* cfg; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  i2c_address; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_transfer (TYPE_2__*,struct i2c_msg*,int) ; 

__attribute__((used)) static int fc0012_readreg(struct fc0012_priv *priv, u8 reg, u8 *val)
{
	struct i2c_msg msg[2] = {
		{ .addr = priv->cfg->i2c_address, .flags = 0,
			.buf = &reg, .len = 1 },
		{ .addr = priv->cfg->i2c_address, .flags = I2C_M_RD,
			.buf = val, .len = 1 },
	};

	if (i2c_transfer(priv->i2c, msg, 2) != 2) {
		dev_err(&priv->i2c->dev,
			"%s: I2C read reg failed, reg: %02x\n",
			KBUILD_MODNAME, reg);
		return -EREMOTEIO;
	}
	return 0;
}