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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dvb_frontend {struct cxd2820r_priv* demodulator_priv; } ;
struct cxd2820r_priv {int /*<<< orphan*/ * regmap; struct i2c_client** client; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int regmap_write (int /*<<< orphan*/ ,int,int) ; 

int cxd2820r_init_c(struct dvb_frontend *fe)
{
	struct cxd2820r_priv *priv = fe->demodulator_priv;
	struct i2c_client *client = priv->client[0];
	int ret;

	dev_dbg(&client->dev, "\n");

	ret = regmap_write(priv->regmap[0], 0x0085, 0x07);
	if (ret)
		goto error;

	return ret;
error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}