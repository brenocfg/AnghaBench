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
typedef  int u8 ;
struct rtl2832_dev {int /*<<< orphan*/  regmap; scalar_t__ slave_ts; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dvb_frontend {struct rtl2832_dev* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int rtl2832_pid_filter_ctrl(struct dvb_frontend *fe, int onoff)
{
	struct rtl2832_dev *dev = fe->demodulator_priv;
	struct i2c_client *client = dev->client;
	int ret;
	u8 u8tmp;

	dev_dbg(&client->dev, "onoff=%d, slave_ts=%d\n", onoff, dev->slave_ts);

	/* enable / disable PID filter */
	if (onoff)
		u8tmp = 0x80;
	else
		u8tmp = 0x00;

	if (dev->slave_ts)
		ret = regmap_update_bits(dev->regmap, 0x021, 0xc0, u8tmp);
	else
		ret = regmap_update_bits(dev->regmap, 0x061, 0xc0, u8tmp);
	if (ret)
		goto err;

	return 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}