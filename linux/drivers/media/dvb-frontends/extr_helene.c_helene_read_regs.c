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
typedef  int u32 ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct helene_priv {int /*<<< orphan*/  i2c_address; TYPE_1__* i2c; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  helene_i2c_debug (struct helene_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int i2c_transfer (TYPE_1__*,struct i2c_msg*,int) ; 

__attribute__((used)) static int helene_read_regs(struct helene_priv *priv,
		u8 reg, u8 *val, u32 len)
{
	int ret;
	struct i2c_msg msg[2] = {
		{
			.addr = priv->i2c_address,
			.flags = 0,
			.len = 1,
			.buf = &reg,
		}, {
			.addr = priv->i2c_address,
			.flags = I2C_M_RD,
			.len = len,
			.buf = val,
		}
	};

	ret = i2c_transfer(priv->i2c, &msg[0], 1);
	if (ret >= 0 && ret != 1)
		ret = -EREMOTEIO;
	if (ret < 0) {
		dev_warn(&priv->i2c->dev,
				"%s: I2C rw failed=%d addr=%02x reg=%02x\n",
				KBUILD_MODNAME, ret, priv->i2c_address, reg);
		return ret;
	}
	ret = i2c_transfer(priv->i2c, &msg[1], 1);
	if (ret >= 0 && ret != 1)
		ret = -EREMOTEIO;
	if (ret < 0) {
		dev_warn(&priv->i2c->dev,
				"%s: i2c rd failed=%d addr=%02x reg=%02x\n",
				KBUILD_MODNAME, ret, priv->i2c_address, reg);
		return ret;
	}
	helene_i2c_debug(priv, reg, 0, val, len);
	return 0;
}