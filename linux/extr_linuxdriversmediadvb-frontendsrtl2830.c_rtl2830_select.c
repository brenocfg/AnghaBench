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
typedef  int /*<<< orphan*/  u32 ;
struct rtl2830_dev {int /*<<< orphan*/  regmap; } ;
struct i2c_mux_core {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 struct rtl2830_dev* i2c_get_clientdata (struct i2c_client*) ; 
 struct i2c_client* i2c_mux_priv (struct i2c_mux_core*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int rtl2830_select(struct i2c_mux_core *muxc, u32 chan_id)
{
	struct i2c_client *client = i2c_mux_priv(muxc);
	struct rtl2830_dev *dev = i2c_get_clientdata(client);
	int ret;

	dev_dbg(&client->dev, "\n");

	/* open I2C repeater for 1 transfer, closes automatically */
	/* XXX: regmap_update_bits() does not lock I2C adapter */
	ret = regmap_update_bits(dev->regmap, 0x101, 0x08, 0x08);
	if (ret)
		goto err;

	return 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}