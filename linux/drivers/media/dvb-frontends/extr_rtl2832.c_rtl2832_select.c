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
struct rtl2832_dev {int /*<<< orphan*/  regmap; int /*<<< orphan*/  i2c_gate_work; struct i2c_client* client; } ;
struct i2c_mux_core {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 struct rtl2832_dev* i2c_mux_priv (struct i2c_mux_core*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int rtl2832_select(struct i2c_mux_core *muxc, u32 chan_id)
{
	struct rtl2832_dev *dev = i2c_mux_priv(muxc);
	struct i2c_client *client = dev->client;
	int ret;

	/* terminate possible gate closing */
	cancel_delayed_work(&dev->i2c_gate_work);

	/* open gate */
	ret = regmap_update_bits(dev->regmap, 0x101, 0x08, 0x08);
	if (ret)
		goto err;

	return 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}