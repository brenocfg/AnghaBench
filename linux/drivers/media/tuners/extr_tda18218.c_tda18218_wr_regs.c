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
typedef  int u8 ;
struct tda18218_priv {TYPE_2__* i2c; TYPE_1__* cfg; } ;
struct i2c_msg {int* buf; int len; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int i2c_wr_max; int /*<<< orphan*/  i2c_address; } ;

/* Variables and functions */
 int EINVAL ; 
 int EREMOTEIO ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int MAX_XFER_SIZE ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int,...) ; 
 int i2c_transfer (TYPE_2__*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static int tda18218_wr_regs(struct tda18218_priv *priv, u8 reg, u8 *val, u8 len)
{
	int ret = 0, len2, remaining;
	u8 buf[MAX_XFER_SIZE];
	struct i2c_msg msg[1] = {
		{
			.addr = priv->cfg->i2c_address,
			.flags = 0,
			.buf = buf,
		}
	};

	if (1 + len > sizeof(buf)) {
		dev_warn(&priv->i2c->dev,
			 "%s: i2c wr reg=%04x: len=%d is too big!\n",
			 KBUILD_MODNAME, reg, len);
		return -EINVAL;
	}

	for (remaining = len; remaining > 0;
			remaining -= (priv->cfg->i2c_wr_max - 1)) {
		len2 = remaining;
		if (len2 > (priv->cfg->i2c_wr_max - 1))
			len2 = (priv->cfg->i2c_wr_max - 1);

		msg[0].len = 1 + len2;
		buf[0] = reg + len - remaining;
		memcpy(&buf[1], &val[len - remaining], len2);

		ret = i2c_transfer(priv->i2c, msg, 1);
		if (ret != 1)
			break;
	}

	if (ret == 1) {
		ret = 0;
	} else {
		dev_warn(&priv->i2c->dev, "%s: i2c wr failed=%d reg=%02x " \
				"len=%d\n", KBUILD_MODNAME, ret, reg, len);
		ret = -EREMOTEIO;
	}

	return ret;
}