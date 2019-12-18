#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_12__ {int len; TYPE_5__* stat; } ;
struct TYPE_10__ {int len; TYPE_3__* stat; } ;
struct TYPE_8__ {int len; TYPE_1__* stat; } ;
struct dtv_frontend_properties {TYPE_6__ post_bit_error; TYPE_4__ cnr; TYPE_2__ strength; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct cxd2820r_priv* demodulator_priv; } ;
struct cxd2820r_priv {unsigned int post_bit_error; int /*<<< orphan*/ * regmap; struct i2c_client** client; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;
struct TYPE_11__ {unsigned int uvalue; void* scale; } ;
struct TYPE_9__ {unsigned int svalue; void* scale; } ;
struct TYPE_7__ {unsigned int uvalue; void* scale; } ;

/* Variables and functions */
 scalar_t__ CXD2820R_LOG10_8_24 ; 
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 void* FE_SCALE_COUNTER ; 
 void* FE_SCALE_DECIBEL ; 
 void* FE_SCALE_NOT_AVAILABLE ; 
 void* FE_SCALE_RELATIVE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 unsigned int div_u64 (int,int) ; 
 scalar_t__ intlog10 (unsigned int) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int,int*,int) ; 

int cxd2820r_read_status_t2(struct dvb_frontend *fe, enum fe_status *status)
{
	struct cxd2820r_priv *priv = fe->demodulator_priv;
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	struct i2c_client *client = priv->client[0];
	int ret;
	unsigned int utmp, utmp1, utmp2;
	u8 buf[4];

	/* Lock detection */
	ret = regmap_bulk_read(priv->regmap[0], 0x2010, &buf[0], 1);
	if (ret)
		goto error;

	utmp1 = (buf[0] >> 0) & 0x07;
	utmp2 = (buf[0] >> 5) & 0x01;

	if (utmp1 == 6 && utmp2 == 1) {
		*status = FE_HAS_SIGNAL | FE_HAS_CARRIER |
			  FE_HAS_VITERBI | FE_HAS_SYNC | FE_HAS_LOCK;
	} else if (utmp1 == 6 || utmp2 == 1) {
		*status = FE_HAS_SIGNAL | FE_HAS_CARRIER |
			  FE_HAS_VITERBI | FE_HAS_SYNC;
	} else {
		*status = 0;
	}

	dev_dbg(&client->dev, "status=%02x raw=%*ph sync=%u ts=%u\n",
		*status, 1, buf, utmp1, utmp2);

	/* Signal strength */
	if (*status & FE_HAS_SIGNAL) {
		unsigned int strength;

		ret = regmap_bulk_read(priv->regmap[0], 0x2026, buf, 2);
		if (ret)
			goto error;

		utmp = buf[0] << 8 | buf[1] << 0;
		utmp = ~utmp & 0x0fff;
		/* Scale value to 0x0000-0xffff */
		strength = utmp << 4 | utmp >> 8;

		c->strength.len = 1;
		c->strength.stat[0].scale = FE_SCALE_RELATIVE;
		c->strength.stat[0].uvalue = strength;
	} else {
		c->strength.len = 1;
		c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	}

	/* CNR */
	if (*status & FE_HAS_VITERBI) {
		unsigned int cnr;

		ret = regmap_bulk_read(priv->regmap[0], 0x2028, buf, 2);
		if (ret)
			goto error;

		utmp = buf[0] << 8 | buf[1] << 0;
		utmp = utmp & 0x0fff;
		#define CXD2820R_LOG10_8_24 15151336 /* log10(8) << 24 */
		if (utmp)
			cnr = div_u64((u64)(intlog10(utmp)
				      - CXD2820R_LOG10_8_24) * 10000,
				      (1 << 24));
		else
			cnr = 0;

		c->cnr.len = 1;
		c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
		c->cnr.stat[0].svalue = cnr;
	} else {
		c->cnr.len = 1;
		c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	}

	/* BER */
	if (*status & FE_HAS_SYNC) {
		unsigned int post_bit_error;

		ret = regmap_bulk_read(priv->regmap[0], 0x2039, buf, 4);
		if (ret)
			goto error;

		if ((buf[0] >> 4) & 0x01) {
			post_bit_error = buf[0] << 24 | buf[1] << 16 |
					 buf[2] << 8 | buf[3] << 0;
			post_bit_error &= 0x0fffffff;
		} else {
			post_bit_error = 0;
		}

		priv->post_bit_error += post_bit_error;

		c->post_bit_error.len = 1;
		c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_error.stat[0].uvalue = priv->post_bit_error;
	} else {
		c->post_bit_error.len = 1;
		c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	}

	return ret;
error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}