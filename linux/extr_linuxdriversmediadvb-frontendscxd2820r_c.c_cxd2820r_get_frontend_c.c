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
struct dvb_frontend {struct cxd2820r_priv* demodulator_priv; } ;
struct dtv_frontend_properties {int symbol_rate; int /*<<< orphan*/  inversion; int /*<<< orphan*/  modulation; } ;
struct cxd2820r_priv {int /*<<< orphan*/ * regmap; struct i2c_client** client; } ;

/* Variables and functions */
 int /*<<< orphan*/  INVERSION_OFF ; 
 int /*<<< orphan*/  INVERSION_ON ; 
 int /*<<< orphan*/  QAM_128 ; 
 int /*<<< orphan*/  QAM_16 ; 
 int /*<<< orphan*/  QAM_256 ; 
 int /*<<< orphan*/  QAM_32 ; 
 int /*<<< orphan*/  QAM_64 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int,int*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 

int cxd2820r_get_frontend_c(struct dvb_frontend *fe,
			    struct dtv_frontend_properties *c)
{
	struct cxd2820r_priv *priv = fe->demodulator_priv;
	struct i2c_client *client = priv->client[0];
	int ret;
	unsigned int utmp;
	u8 buf[2];

	dev_dbg(&client->dev, "\n");

	ret = regmap_bulk_read(priv->regmap[1], 0x001a, buf, 2);
	if (ret)
		goto error;

	c->symbol_rate = 2500 * ((buf[0] & 0x0f) << 8 | buf[1]);

	ret = regmap_read(priv->regmap[1], 0x0019, &utmp);
	if (ret)
		goto error;

	switch ((utmp >> 0) & 0x07) {
	case 0:
		c->modulation = QAM_16;
		break;
	case 1:
		c->modulation = QAM_32;
		break;
	case 2:
		c->modulation = QAM_64;
		break;
	case 3:
		c->modulation = QAM_128;
		break;
	case 4:
		c->modulation = QAM_256;
		break;
	}

	switch ((utmp >> 7) & 0x01) {
	case 0:
		c->inversion = INVERSION_OFF;
		break;
	case 1:
		c->inversion = INVERSION_ON;
		break;
	}

	return ret;
error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}