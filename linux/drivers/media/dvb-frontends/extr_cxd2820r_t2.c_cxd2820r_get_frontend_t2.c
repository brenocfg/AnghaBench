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
struct dtv_frontend_properties {int /*<<< orphan*/  inversion; int /*<<< orphan*/  modulation; int /*<<< orphan*/  fec_inner; int /*<<< orphan*/  guard_interval; int /*<<< orphan*/  transmission_mode; } ;
struct cxd2820r_priv {int /*<<< orphan*/ * regmap; struct i2c_client** client; } ;

/* Variables and functions */
 int /*<<< orphan*/  FEC_1_2 ; 
 int /*<<< orphan*/  FEC_2_3 ; 
 int /*<<< orphan*/  FEC_3_4 ; 
 int /*<<< orphan*/  FEC_3_5 ; 
 int /*<<< orphan*/  FEC_4_5 ; 
 int /*<<< orphan*/  FEC_5_6 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_19_128 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_19_256 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_128 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_16 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_32 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_4 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_8 ; 
 int /*<<< orphan*/  INVERSION_OFF ; 
 int /*<<< orphan*/  INVERSION_ON ; 
 int /*<<< orphan*/  QAM_16 ; 
 int /*<<< orphan*/  QAM_256 ; 
 int /*<<< orphan*/  QAM_64 ; 
 int /*<<< orphan*/  QPSK ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_16K ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_1K ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_2K ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_32K ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_4K ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_8K ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int,int*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 

int cxd2820r_get_frontend_t2(struct dvb_frontend *fe,
			     struct dtv_frontend_properties *c)
{
	struct cxd2820r_priv *priv = fe->demodulator_priv;
	struct i2c_client *client = priv->client[0];
	int ret;
	unsigned int utmp;
	u8 buf[2];

	dev_dbg(&client->dev, "\n");

	ret = regmap_bulk_read(priv->regmap[0], 0x205c, buf, 2);
	if (ret)
		goto error;

	switch ((buf[0] >> 0) & 0x07) {
	case 0:
		c->transmission_mode = TRANSMISSION_MODE_2K;
		break;
	case 1:
		c->transmission_mode = TRANSMISSION_MODE_8K;
		break;
	case 2:
		c->transmission_mode = TRANSMISSION_MODE_4K;
		break;
	case 3:
		c->transmission_mode = TRANSMISSION_MODE_1K;
		break;
	case 4:
		c->transmission_mode = TRANSMISSION_MODE_16K;
		break;
	case 5:
		c->transmission_mode = TRANSMISSION_MODE_32K;
		break;
	}

	switch ((buf[1] >> 4) & 0x07) {
	case 0:
		c->guard_interval = GUARD_INTERVAL_1_32;
		break;
	case 1:
		c->guard_interval = GUARD_INTERVAL_1_16;
		break;
	case 2:
		c->guard_interval = GUARD_INTERVAL_1_8;
		break;
	case 3:
		c->guard_interval = GUARD_INTERVAL_1_4;
		break;
	case 4:
		c->guard_interval = GUARD_INTERVAL_1_128;
		break;
	case 5:
		c->guard_interval = GUARD_INTERVAL_19_128;
		break;
	case 6:
		c->guard_interval = GUARD_INTERVAL_19_256;
		break;
	}

	ret = regmap_bulk_read(priv->regmap[0], 0x225b, buf, 2);
	if (ret)
		goto error;

	switch ((buf[0] >> 0) & 0x07) {
	case 0:
		c->fec_inner = FEC_1_2;
		break;
	case 1:
		c->fec_inner = FEC_3_5;
		break;
	case 2:
		c->fec_inner = FEC_2_3;
		break;
	case 3:
		c->fec_inner = FEC_3_4;
		break;
	case 4:
		c->fec_inner = FEC_4_5;
		break;
	case 5:
		c->fec_inner = FEC_5_6;
		break;
	}

	switch ((buf[1] >> 0) & 0x07) {
	case 0:
		c->modulation = QPSK;
		break;
	case 1:
		c->modulation = QAM_16;
		break;
	case 2:
		c->modulation = QAM_64;
		break;
	case 3:
		c->modulation = QAM_256;
		break;
	}

	ret = regmap_read(priv->regmap[0], 0x20b5, &utmp);
	if (ret)
		goto error;

	switch ((utmp >> 4) & 0x01) {
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