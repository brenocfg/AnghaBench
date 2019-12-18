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
struct dtv_frontend_properties {int /*<<< orphan*/  inversion; void* code_rate_LP; void* code_rate_HP; int /*<<< orphan*/  hierarchy; int /*<<< orphan*/  guard_interval; int /*<<< orphan*/  transmission_mode; int /*<<< orphan*/  modulation; } ;
struct cxd2820r_priv {int /*<<< orphan*/ * regmap; struct i2c_client** client; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 void* FEC_1_2 ; 
 void* FEC_2_3 ; 
 void* FEC_3_4 ; 
 void* FEC_5_6 ; 
 void* FEC_7_8 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_16 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_32 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_4 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_8 ; 
 int /*<<< orphan*/  HIERARCHY_1 ; 
 int /*<<< orphan*/  HIERARCHY_2 ; 
 int /*<<< orphan*/  HIERARCHY_4 ; 
 int /*<<< orphan*/  HIERARCHY_NONE ; 
 int /*<<< orphan*/  INVERSION_OFF ; 
 int /*<<< orphan*/  INVERSION_ON ; 
 int /*<<< orphan*/  QAM_16 ; 
 int /*<<< orphan*/  QAM_64 ; 
 int /*<<< orphan*/  QPSK ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_2K ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_8K ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int,int*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 

int cxd2820r_get_frontend_t(struct dvb_frontend *fe,
			    struct dtv_frontend_properties *c)
{
	struct cxd2820r_priv *priv = fe->demodulator_priv;
	struct i2c_client *client = priv->client[0];
	int ret;
	unsigned int utmp;
	u8 buf[2];

	dev_dbg(&client->dev, "\n");

	ret = regmap_bulk_read(priv->regmap[0], 0x002f, buf, sizeof(buf));
	if (ret)
		goto error;

	switch ((buf[0] >> 6) & 0x03) {
	case 0:
		c->modulation = QPSK;
		break;
	case 1:
		c->modulation = QAM_16;
		break;
	case 2:
		c->modulation = QAM_64;
		break;
	}

	switch ((buf[1] >> 1) & 0x03) {
	case 0:
		c->transmission_mode = TRANSMISSION_MODE_2K;
		break;
	case 1:
		c->transmission_mode = TRANSMISSION_MODE_8K;
		break;
	}

	switch ((buf[1] >> 3) & 0x03) {
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
	}

	switch ((buf[0] >> 3) & 0x07) {
	case 0:
		c->hierarchy = HIERARCHY_NONE;
		break;
	case 1:
		c->hierarchy = HIERARCHY_1;
		break;
	case 2:
		c->hierarchy = HIERARCHY_2;
		break;
	case 3:
		c->hierarchy = HIERARCHY_4;
		break;
	}

	switch ((buf[0] >> 0) & 0x07) {
	case 0:
		c->code_rate_HP = FEC_1_2;
		break;
	case 1:
		c->code_rate_HP = FEC_2_3;
		break;
	case 2:
		c->code_rate_HP = FEC_3_4;
		break;
	case 3:
		c->code_rate_HP = FEC_5_6;
		break;
	case 4:
		c->code_rate_HP = FEC_7_8;
		break;
	}

	switch ((buf[1] >> 5) & 0x07) {
	case 0:
		c->code_rate_LP = FEC_1_2;
		break;
	case 1:
		c->code_rate_LP = FEC_2_3;
		break;
	case 2:
		c->code_rate_LP = FEC_3_4;
		break;
	case 3:
		c->code_rate_LP = FEC_5_6;
		break;
	case 4:
		c->code_rate_LP = FEC_7_8;
		break;
	}

	ret = regmap_read(priv->regmap[0], 0x07c6, &utmp);
	if (ret)
		goto error;

	switch ((utmp >> 0) & 0x01) {
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