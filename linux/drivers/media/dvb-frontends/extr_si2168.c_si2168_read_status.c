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
struct si2168_dev {int fe_status; int /*<<< orphan*/  active; } ;
struct si2168_cmd {int* args; int /*<<< orphan*/  rlen; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_16__ {TYPE_7__* stat; } ;
struct TYPE_14__ {TYPE_5__* stat; } ;
struct TYPE_12__ {TYPE_3__* stat; } ;
struct TYPE_10__ {int len; TYPE_1__* stat; } ;
struct dtv_frontend_properties {int delivery_system; TYPE_8__ block_error; TYPE_6__ post_bit_count; TYPE_4__ post_bit_error; TYPE_2__ cnr; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct i2c_client* demodulator_priv; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;
struct TYPE_15__ {unsigned int uvalue; void* scale; } ;
struct TYPE_13__ {unsigned int uvalue; void* scale; } ;
struct TYPE_11__ {unsigned int uvalue; void* scale; } ;
struct TYPE_9__ {int svalue; void* scale; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 void* FE_SCALE_COUNTER ; 
 void* FE_SCALE_DECIBEL ; 
 void* FE_SCALE_NOT_AVAILABLE ; 
#define  SYS_DVBC_ANNEX_A 130 
#define  SYS_DVBT 129 
#define  SYS_DVBT2 128 
 unsigned int clamp (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cmd_init (struct si2168_cmd*,char*,int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 struct si2168_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int si2168_cmd_execute (struct i2c_client*,struct si2168_cmd*) ; 

__attribute__((used)) static int si2168_read_status(struct dvb_frontend *fe, enum fe_status *status)
{
	struct i2c_client *client = fe->demodulator_priv;
	struct si2168_dev *dev = i2c_get_clientdata(client);
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	int ret, i;
	unsigned int utmp, utmp1, utmp2;
	struct si2168_cmd cmd;

	*status = 0;

	if (!dev->active) {
		ret = -EAGAIN;
		goto err;
	}

	switch (c->delivery_system) {
	case SYS_DVBT:
		cmd_init(&cmd, "\xa0\x01", 2, 13);
		break;
	case SYS_DVBC_ANNEX_A:
		cmd_init(&cmd, "\x90\x01", 2, 9);
		break;
	case SYS_DVBT2:
		cmd_init(&cmd, "\x50\x01", 2, 14);
		break;
	default:
		ret = -EINVAL;
		goto err;
	}

	ret = si2168_cmd_execute(client, &cmd);
	if (ret)
		goto err;

	switch ((cmd.args[2] >> 1) & 0x03) {
	case 0x01:
		*status = FE_HAS_SIGNAL | FE_HAS_CARRIER;
		break;
	case 0x03:
		*status = FE_HAS_SIGNAL | FE_HAS_CARRIER | FE_HAS_VITERBI |
				FE_HAS_SYNC | FE_HAS_LOCK;
		break;
	}

	dev->fe_status = *status;

	if (*status & FE_HAS_LOCK) {
		c->cnr.len = 1;
		c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
		c->cnr.stat[0].svalue = cmd.args[3] * 1000 / 4;
	} else {
		c->cnr.len = 1;
		c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	}

	dev_dbg(&client->dev, "status=%02x args=%*ph\n",
			*status, cmd.rlen, cmd.args);

	/* BER */
	if (*status & FE_HAS_VITERBI) {
		cmd_init(&cmd, "\x82\x00", 2, 3);
		ret = si2168_cmd_execute(client, &cmd);
		if (ret)
			goto err;

		/*
		 * Firmware returns [0, 255] mantissa and [0, 8] exponent.
		 * Convert to DVB API: mantissa * 10^(8 - exponent) / 10^8
		 */
		utmp = clamp(8 - cmd.args[1], 0, 8);
		for (i = 0, utmp1 = 1; i < utmp; i++)
			utmp1 = utmp1 * 10;

		utmp1 = cmd.args[2] * utmp1;
		utmp2 = 100000000; /* 10^8 */

		dev_dbg(&client->dev,
			"post_bit_error=%u post_bit_count=%u ber=%u*10^-%u\n",
			utmp1, utmp2, cmd.args[2], cmd.args[1]);

		c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_error.stat[0].uvalue += utmp1;
		c->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_count.stat[0].uvalue += utmp2;
	} else {
		c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	}

	/* UCB */
	if (*status & FE_HAS_SYNC) {
		cmd_init(&cmd, "\x84\x01", 2, 3);
		ret = si2168_cmd_execute(client, &cmd);
		if (ret)
			goto err;

		utmp1 = cmd.args[2] << 8 | cmd.args[1] << 0;
		dev_dbg(&client->dev, "block_error=%u\n", utmp1);

		/* Sometimes firmware returns bogus value */
		if (utmp1 == 0xffff)
			utmp1 = 0;

		c->block_error.stat[0].scale = FE_SCALE_COUNTER;
		c->block_error.stat[0].uvalue += utmp1;
	} else {
		c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	}

	return 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}