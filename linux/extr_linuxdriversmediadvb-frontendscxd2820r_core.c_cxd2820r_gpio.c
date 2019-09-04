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
struct dtv_frontend_properties {int delivery_system; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct cxd2820r_priv* demodulator_priv; } ;
struct cxd2820r_priv {int /*<<< orphan*/  gpio; int /*<<< orphan*/ * regmap; struct i2c_client** client; } ;

/* Variables and functions */
 int CXD2820R_GPIO_E ; 
 int CXD2820R_GPIO_H ; 
 int CXD2820R_GPIO_I ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  memcmp (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int,int,int) ; 

int cxd2820r_gpio(struct dvb_frontend *fe, u8 *gpio)
{
	struct cxd2820r_priv *priv = fe->demodulator_priv;
	struct i2c_client *client = priv->client[0];
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	int ret, i;
	u8 tmp0, tmp1;

	dev_dbg(&client->dev, "delivery_system=%d\n", c->delivery_system);

	/* update GPIOs only when needed */
	if (!memcmp(gpio, priv->gpio, sizeof(priv->gpio)))
		return 0;

	tmp0 = 0x00;
	tmp1 = 0x00;
	for (i = 0; i < sizeof(priv->gpio); i++) {
		/* enable / disable */
		if (gpio[i] & CXD2820R_GPIO_E)
			tmp0 |= (2 << 6) >> (2 * i);
		else
			tmp0 |= (1 << 6) >> (2 * i);

		/* input / output */
		if (gpio[i] & CXD2820R_GPIO_I)
			tmp1 |= (1 << (3 + i));
		else
			tmp1 |= (0 << (3 + i));

		/* high / low */
		if (gpio[i] & CXD2820R_GPIO_H)
			tmp1 |= (1 << (0 + i));
		else
			tmp1 |= (0 << (0 + i));

		dev_dbg(&client->dev, "gpio i=%d %02x %02x\n", i, tmp0, tmp1);
	}

	dev_dbg(&client->dev, "wr gpio=%02x %02x\n", tmp0, tmp1);

	/* write bits [7:2] */
	ret = regmap_update_bits(priv->regmap[0], 0x0089, 0xfc, tmp0);
	if (ret)
		goto error;

	/* write bits [5:0] */
	ret = regmap_update_bits(priv->regmap[0], 0x008e, 0x3f, tmp1);
	if (ret)
		goto error;

	memcpy(priv->gpio, gpio, sizeof(priv->gpio));

	return ret;
error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}