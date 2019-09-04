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
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_transfer (TYPE_1__*,struct i2c_msg*,int) ; 

__attribute__((used)) static int fc0011_writereg(struct fc0011_priv *priv, u8 reg, u8 val)
{
	u8 buf[2] = { reg, val };
	struct i2c_msg msg = { .addr = priv->addr,
		.flags = 0, .buf = buf, .len = 2 };

	if (i2c_transfer(priv->i2c, &msg, 1) != 1) {
		dev_err(&priv->i2c->dev,
			"I2C write reg failed, reg: %02x, val: %02x\n",
			reg, val);
		return -EIO;
	}

	return 0;
}