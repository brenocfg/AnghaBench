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
struct rtl2832_dev {int sleeping; scalar_t__ fe_status; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dvb_frontend {struct rtl2832_dev* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVBT_SOFT_RST ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int rtl2832_wr_demod_reg (struct rtl2832_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rtl2832_sleep(struct dvb_frontend *fe)
{
	struct rtl2832_dev *dev = fe->demodulator_priv;
	struct i2c_client *client = dev->client;
	int ret;

	dev_dbg(&client->dev, "\n");

	dev->sleeping = true;
	dev->fe_status = 0;

	ret = rtl2832_wr_demod_reg(dev, DVBT_SOFT_RST, 0x1);
	if (ret)
		goto err;

	return 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}