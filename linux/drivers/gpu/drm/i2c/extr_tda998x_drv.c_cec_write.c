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
typedef  int /*<<< orphan*/  u16 ;
struct tda998x_priv {TYPE_1__* hdmi; int /*<<< orphan*/  cec_addr; } ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static void
cec_write(struct tda998x_priv *priv, u16 addr, u8 val)
{
	u8 buf[] = {addr, val};
	struct i2c_msg msg = {
		.addr = priv->cec_addr,
		.len = 2,
		.buf = buf,
	};
	int ret;

	ret = i2c_transfer(priv->hdmi->adapter, &msg, 1);
	if (ret < 0)
		dev_err(&priv->hdmi->dev, "Error %d writing to cec:0x%x\n",
			ret, addr);
}