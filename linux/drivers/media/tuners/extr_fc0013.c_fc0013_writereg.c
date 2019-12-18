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
typedef  int /*<<< orphan*/  u8 ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct fc0013_priv {int /*<<< orphan*/  i2c; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int fc0013_writereg(struct fc0013_priv *priv, u8 reg, u8 val)
{
	u8 buf[2] = {reg, val};
	struct i2c_msg msg = {
		.addr = priv->addr, .flags = 0, .buf = buf, .len = 2
	};

	if (i2c_transfer(priv->i2c, &msg, 1) != 1) {
		err("I2C write reg failed, reg: %02x, val: %02x", reg, val);
		return -EREMOTEIO;
	}
	return 0;
}