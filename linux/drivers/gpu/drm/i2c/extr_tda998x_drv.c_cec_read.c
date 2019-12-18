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
struct tda998x_priv {TYPE_1__* hdmi; int /*<<< orphan*/  cec_addr; } ;
struct i2c_msg {int len; scalar_t__* buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct i2c_msg*) ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,scalar_t__) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8
cec_read(struct tda998x_priv *priv, u8 addr)
{
	u8 val;
	struct i2c_msg msg[2] = {
		{
			.addr = priv->cec_addr,
			.len = 1,
			.buf = &addr,
		}, {
			.addr = priv->cec_addr,
			.flags = I2C_M_RD,
			.len = 1,
			.buf = &val,
		},
	};
	int ret;

	ret = i2c_transfer(priv->hdmi->adapter, msg, ARRAY_SIZE(msg));
	if (ret < 0) {
		dev_err(&priv->hdmi->dev, "Error %d reading from cec:0x%x\n",
			ret, addr);
		val = 0;
	}

	return val;
}