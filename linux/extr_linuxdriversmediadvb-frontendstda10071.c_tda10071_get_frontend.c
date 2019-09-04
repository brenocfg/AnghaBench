#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct tda10071_dev {int fe_status; int /*<<< orphan*/  regmap; int /*<<< orphan*/  warm; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dvb_frontend {struct tda10071_dev* demodulator_priv; } ;
struct dtv_frontend_properties {int frequency; int symbol_rate; int /*<<< orphan*/  pilot; int /*<<< orphan*/  inversion; int /*<<< orphan*/  delivery_system; int /*<<< orphan*/  fec_inner; int /*<<< orphan*/  modulation; } ;
struct TYPE_3__ {int val; int /*<<< orphan*/  delivery_system; int /*<<< orphan*/  fec; int /*<<< orphan*/  modulation; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int FE_HAS_LOCK ; 
 int /*<<< orphan*/  INVERSION_OFF ; 
 int /*<<< orphan*/  INVERSION_ON ; 
 int /*<<< orphan*/  PILOT_OFF ; 
 int /*<<< orphan*/  PILOT_ON ; 
 TYPE_1__* TDA10071_MODCOD ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int,int*,int) ; 

__attribute__((used)) static int tda10071_get_frontend(struct dvb_frontend *fe,
				 struct dtv_frontend_properties *c)
{
	struct tda10071_dev *dev = fe->demodulator_priv;
	struct i2c_client *client = dev->client;
	int ret, i;
	u8 buf[5], tmp;

	if (!dev->warm || !(dev->fe_status & FE_HAS_LOCK)) {
		ret = 0;
		goto error;
	}

	ret = regmap_bulk_read(dev->regmap, 0x30, buf, 5);
	if (ret)
		goto error;

	tmp = buf[0] & 0x3f;
	for (i = 0; i < ARRAY_SIZE(TDA10071_MODCOD); i++) {
		if (tmp == TDA10071_MODCOD[i].val) {
			c->modulation = TDA10071_MODCOD[i].modulation;
			c->fec_inner = TDA10071_MODCOD[i].fec;
			c->delivery_system = TDA10071_MODCOD[i].delivery_system;
		}
	}

	switch ((buf[1] >> 0) & 0x01) {
	case 0:
		c->inversion = INVERSION_ON;
		break;
	case 1:
		c->inversion = INVERSION_OFF;
		break;
	}

	switch ((buf[1] >> 7) & 0x01) {
	case 0:
		c->pilot = PILOT_OFF;
		break;
	case 1:
		c->pilot = PILOT_ON;
		break;
	}

	c->frequency = (buf[2] << 16) | (buf[3] << 8) | (buf[4] << 0);

	ret = regmap_bulk_read(dev->regmap, 0x52, buf, 3);
	if (ret)
		goto error;

	c->symbol_rate = ((buf[0] << 16) | (buf[1] << 8) | (buf[2] << 0)) * 1000;

	return ret;
error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}