#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct tda10071_dev {int fe_status; int delivery_system; unsigned int meas_count; int dvbv3_ber; int post_bit_error; int block_error; int /*<<< orphan*/  regmap; int /*<<< orphan*/  warm; struct i2c_client* client; } ;
struct tda10071_cmd {int* args; int len; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_12__ {TYPE_3__* stat; } ;
struct TYPE_10__ {TYPE_1__* stat; } ;
struct TYPE_16__ {TYPE_7__* stat; } ;
struct TYPE_14__ {TYPE_5__* stat; } ;
struct dtv_frontend_properties {TYPE_4__ block_error; TYPE_2__ post_bit_error; TYPE_8__ cnr; TYPE_6__ strength; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct tda10071_dev* demodulator_priv; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;
struct TYPE_15__ {int svalue; void* scale; } ;
struct TYPE_13__ {int svalue; void* scale; } ;
struct TYPE_11__ {int uvalue; void* scale; } ;
struct TYPE_9__ {int uvalue; void* scale; } ;

/* Variables and functions */
 int CMD_BER_UPDATE_COUNTERS ; 
 int CMD_GET_AGCACC ; 
 int EINVAL ; 
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 void* FE_SCALE_COUNTER ; 
 void* FE_SCALE_DECIBEL ; 
 void* FE_SCALE_NOT_AVAILABLE ; 
#define  SYS_DVBS 129 
#define  SYS_DVBS2 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int,int*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 
 int tda10071_cmd_execute (struct tda10071_dev*,struct tda10071_cmd*) ; 

__attribute__((used)) static int tda10071_read_status(struct dvb_frontend *fe, enum fe_status *status)
{
	struct tda10071_dev *dev = fe->demodulator_priv;
	struct i2c_client *client = dev->client;
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	struct tda10071_cmd cmd;
	int ret;
	unsigned int uitmp;
	u8 buf[8];

	*status = 0;

	if (!dev->warm) {
		ret = 0;
		goto error;
	}

	ret = regmap_read(dev->regmap, 0x39, &uitmp);
	if (ret)
		goto error;

	/* 0x39[0] tuner PLL */
	if (uitmp & 0x02) /* demod PLL */
		*status |= FE_HAS_SIGNAL | FE_HAS_CARRIER;
	if (uitmp & 0x04) /* viterbi or LDPC*/
		*status |= FE_HAS_VITERBI;
	if (uitmp & 0x08) /* RS or BCH */
		*status |= FE_HAS_SYNC | FE_HAS_LOCK;

	dev->fe_status = *status;

	/* signal strength */
	if (dev->fe_status & FE_HAS_SIGNAL) {
		cmd.args[0] = CMD_GET_AGCACC;
		cmd.args[1] = 0;
		cmd.len = 2;
		ret = tda10071_cmd_execute(dev, &cmd);
		if (ret)
			goto error;

		/* input power estimate dBm */
		ret = regmap_read(dev->regmap, 0x50, &uitmp);
		if (ret)
			goto error;

		c->strength.stat[0].scale = FE_SCALE_DECIBEL;
		c->strength.stat[0].svalue = (int) (uitmp - 256) * 1000;
	} else {
		c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	}

	/* CNR */
	if (dev->fe_status & FE_HAS_VITERBI) {
		/* Es/No */
		ret = regmap_bulk_read(dev->regmap, 0x3a, buf, 2);
		if (ret)
			goto error;

		c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
		c->cnr.stat[0].svalue = (buf[0] << 8 | buf[1] << 0) * 100;
	} else {
		c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	}

	/* UCB/PER/BER */
	if (dev->fe_status & FE_HAS_LOCK) {
		/* TODO: report total bits/packets */
		u8 delivery_system, reg, len;

		switch (dev->delivery_system) {
		case SYS_DVBS:
			reg = 0x4c;
			len = 8;
			delivery_system = 1;
			break;
		case SYS_DVBS2:
			reg = 0x4d;
			len = 4;
			delivery_system = 0;
			break;
		default:
			ret = -EINVAL;
			goto error;
		}

		ret = regmap_read(dev->regmap, reg, &uitmp);
		if (ret)
			goto error;

		if (dev->meas_count == uitmp) {
			dev_dbg(&client->dev, "meas not ready=%02x\n", uitmp);
			ret = 0;
			goto error;
		} else {
			dev->meas_count = uitmp;
		}

		cmd.args[0] = CMD_BER_UPDATE_COUNTERS;
		cmd.args[1] = 0;
		cmd.args[2] = delivery_system;
		cmd.len = 3;
		ret = tda10071_cmd_execute(dev, &cmd);
		if (ret)
			goto error;

		ret = regmap_bulk_read(dev->regmap, cmd.len, buf, len);
		if (ret)
			goto error;

		if (dev->delivery_system == SYS_DVBS) {
			dev->dvbv3_ber = buf[0] << 24 | buf[1] << 16 |
					 buf[2] << 8 | buf[3] << 0;
			dev->post_bit_error += buf[0] << 24 | buf[1] << 16 |
					       buf[2] << 8 | buf[3] << 0;
			c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
			c->post_bit_error.stat[0].uvalue = dev->post_bit_error;
			dev->block_error += buf[4] << 8 | buf[5] << 0;
			c->block_error.stat[0].scale = FE_SCALE_COUNTER;
			c->block_error.stat[0].uvalue = dev->block_error;
		} else {
			dev->dvbv3_ber = buf[0] << 8 | buf[1] << 0;
			dev->post_bit_error += buf[0] << 8 | buf[1] << 0;
			c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
			c->post_bit_error.stat[0].uvalue = dev->post_bit_error;
			c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		}
	} else {
		c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	}

	return ret;
error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}