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
typedef  int u16 ;
struct rtl2832_dev {int filters; int /*<<< orphan*/  regmap; scalar_t__ slave_ts; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dvb_frontend {struct rtl2832_dev* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int,int*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int,int*,int) ; 
 int /*<<< orphan*/  set_bit (int,int*) ; 

__attribute__((used)) static int rtl2832_pid_filter(struct dvb_frontend *fe, u8 index, u16 pid,
			      int onoff)
{
	struct rtl2832_dev *dev = fe->demodulator_priv;
	struct i2c_client *client = dev->client;
	int ret;
	u8 buf[4];

	dev_dbg(&client->dev, "index=%d pid=%04x onoff=%d slave_ts=%d\n",
		index, pid, onoff, dev->slave_ts);

	/* skip invalid PIDs (0x2000) */
	if (pid > 0x1fff || index > 32)
		return 0;

	if (onoff)
		set_bit(index, &dev->filters);
	else
		clear_bit(index, &dev->filters);

	/* enable / disable PIDs */
	buf[0] = (dev->filters >>  0) & 0xff;
	buf[1] = (dev->filters >>  8) & 0xff;
	buf[2] = (dev->filters >> 16) & 0xff;
	buf[3] = (dev->filters >> 24) & 0xff;

	if (dev->slave_ts)
		ret = regmap_bulk_write(dev->regmap, 0x022, buf, 4);
	else
		ret = regmap_bulk_write(dev->regmap, 0x062, buf, 4);
	if (ret)
		goto err;

	/* add PID */
	buf[0] = (pid >> 8) & 0xff;
	buf[1] = (pid >> 0) & 0xff;

	if (dev->slave_ts)
		ret = regmap_bulk_write(dev->regmap, 0x026 + 2 * index, buf, 2);
	else
		ret = regmap_bulk_write(dev->regmap, 0x066 + 2 * index, buf, 2);
	if (ret)
		goto err;

	return 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}