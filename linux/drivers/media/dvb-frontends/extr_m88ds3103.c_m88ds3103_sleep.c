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
struct m88ds3103_dev {scalar_t__ chip_id; int /*<<< orphan*/  delivery_system; scalar_t__ fe_status; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dvb_frontend {struct m88ds3103_dev* demodulator_priv; } ;

/* Variables and functions */
 scalar_t__ M88RS6000_CHIP_ID ; 
 int /*<<< orphan*/  SYS_UNDEFINED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int m88ds3103_update_bits (struct m88ds3103_dev*,int,int,int) ; 

__attribute__((used)) static int m88ds3103_sleep(struct dvb_frontend *fe)
{
	struct m88ds3103_dev *dev = fe->demodulator_priv;
	struct i2c_client *client = dev->client;
	int ret;
	unsigned int utmp;

	dev_dbg(&client->dev, "\n");

	dev->fe_status = 0;
	dev->delivery_system = SYS_UNDEFINED;

	/* TS Hi-Z */
	if (dev->chip_id == M88RS6000_CHIP_ID)
		utmp = 0x29;
	else
		utmp = 0x27;
	ret = m88ds3103_update_bits(dev, utmp, 0x01, 0x00);
	if (ret)
		goto err;

	/* sleep */
	ret = m88ds3103_update_bits(dev, 0x08, 0x01, 0x00);
	if (ret)
		goto err;
	ret = m88ds3103_update_bits(dev, 0x04, 0x01, 0x01);
	if (ret)
		goto err;
	ret = m88ds3103_update_bits(dev, 0x23, 0x10, 0x10);
	if (ret)
		goto err;

	return 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}