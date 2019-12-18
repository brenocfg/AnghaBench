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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dvb_frontend {struct i2c_client* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int rtl2830_update_bits (struct i2c_client*,int,int,int) ; 

__attribute__((used)) static int rtl2830_pid_filter_ctrl(struct dvb_frontend *fe, int onoff)
{
	struct i2c_client *client = fe->demodulator_priv;
	int ret;
	u8 u8tmp;

	dev_dbg(&client->dev, "onoff=%d\n", onoff);

	/* enable / disable PID filter */
	if (onoff)
		u8tmp = 0x80;
	else
		u8tmp = 0x00;

	ret = rtl2830_update_bits(client, 0x061, 0x80, u8tmp);
	if (ret)
		goto err;

	return 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}