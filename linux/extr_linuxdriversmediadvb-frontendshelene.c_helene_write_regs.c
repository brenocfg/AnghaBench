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
typedef  int /*<<< orphan*/  u32 ;
struct i2c_msg {int /*<<< orphan*/ * buf; int /*<<< orphan*/  len; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct helene_priv {TYPE_1__* i2c; int /*<<< orphan*/  i2c_address; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int E2BIG ; 
 int EREMOTEIO ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  MAX_WRITE_REGSIZE ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int,...) ; 
 int /*<<< orphan*/  helene_i2c_debug (struct helene_priv*,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int i2c_transfer (TYPE_1__*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int helene_write_regs(struct helene_priv *priv,
		u8 reg, const u8 *data, u32 len)
{
	int ret;
	u8 buf[MAX_WRITE_REGSIZE + 1];
	struct i2c_msg msg[1] = {
		{
			.addr = priv->i2c_address,
			.flags = 0,
			.len = len + 1,
			.buf = buf,
		}
	};

	if (len + 1 > sizeof(buf)) {
		dev_warn(&priv->i2c->dev,
				"wr reg=%04x: len=%d vs %zu is too big!\n",
				reg, len + 1, sizeof(buf));
		return -E2BIG;
	}

	helene_i2c_debug(priv, reg, 1, data, len);
	buf[0] = reg;
	memcpy(&buf[1], data, len);
	ret = i2c_transfer(priv->i2c, msg, 1);
	if (ret >= 0 && ret != 1)
		ret = -EREMOTEIO;
	if (ret < 0) {
		dev_warn(&priv->i2c->dev,
				"%s: i2c wr failed=%d reg=%02x len=%d\n",
				KBUILD_MODNAME, ret, reg, len);
		return ret;
	}
	return 0;
}