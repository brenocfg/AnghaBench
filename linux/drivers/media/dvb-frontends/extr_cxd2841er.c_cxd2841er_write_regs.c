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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct i2c_msg {scalar_t__ addr; scalar_t__* buf; int /*<<< orphan*/  len; int /*<<< orphan*/  flags; } ;
struct cxd2841er_priv {scalar_t__ i2c_addr_slvx; scalar_t__ i2c_addr_slvt; TYPE_1__* i2c; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int E2BIG ; 
 int EIO ; 
 scalar_t__ I2C_SLVX ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  MAX_WRITE_REGSIZE ; 
 int /*<<< orphan*/  cxd2841er_i2c_debug (struct cxd2841er_priv*,scalar_t__,scalar_t__,int,scalar_t__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,scalar_t__,int,...) ; 
 int i2c_transfer (TYPE_1__*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__ const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cxd2841er_write_regs(struct cxd2841er_priv *priv,
				u8 addr, u8 reg, const u8 *data, u32 len)
{
	int ret;
	u8 buf[MAX_WRITE_REGSIZE + 1];
	u8 i2c_addr = (addr == I2C_SLVX ?
		priv->i2c_addr_slvx : priv->i2c_addr_slvt);
	struct i2c_msg msg[1] = {
		{
			.addr = i2c_addr,
			.flags = 0,
			.len = len + 1,
			.buf = buf,
		}
	};

	if (len + 1 >= sizeof(buf)) {
		dev_warn(&priv->i2c->dev, "wr reg=%04x: len=%d is too big!\n",
			 reg, len + 1);
		return -E2BIG;
	}

	cxd2841er_i2c_debug(priv, i2c_addr, reg, 1, data, len);
	buf[0] = reg;
	memcpy(&buf[1], data, len);

	ret = i2c_transfer(priv->i2c, msg, 1);
	if (ret >= 0 && ret != 1)
		ret = -EIO;
	if (ret < 0) {
		dev_warn(&priv->i2c->dev,
			"%s: i2c wr failed=%d addr=%02x reg=%02x len=%d\n",
			KBUILD_MODNAME, ret, i2c_addr, reg, len);
		return ret;
	}
	return 0;
}