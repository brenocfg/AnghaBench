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
struct mn88472_dev {int /*<<< orphan*/ * regmap; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dvb_frontend {struct i2c_client* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 struct mn88472_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int regmap_write (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int mn88472_sleep(struct dvb_frontend *fe)
{
	struct i2c_client *client = fe->demodulator_priv;
	struct mn88472_dev *dev = i2c_get_clientdata(client);
	int ret;

	dev_dbg(&client->dev, "\n");

	/* Power down */
	ret = regmap_write(dev->regmap[2], 0x0c, 0x30);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap[2], 0x0b, 0x30);
	if (ret)
		goto err;
	ret = regmap_write(dev->regmap[2], 0x05, 0x3e);
	if (ret)
		goto err;

	return 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}