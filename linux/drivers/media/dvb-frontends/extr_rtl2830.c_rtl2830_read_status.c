#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_18__ {TYPE_8__* stat; } ;
struct TYPE_16__ {TYPE_6__* stat; } ;
struct TYPE_14__ {TYPE_4__* stat; } ;
struct TYPE_12__ {TYPE_2__* stat; } ;
struct dtv_frontend_properties {TYPE_9__ post_bit_count; TYPE_7__ post_bit_error; TYPE_5__ cnr; TYPE_3__ strength; } ;
struct TYPE_10__ {struct dtv_frontend_properties dtv_property_cache; } ;
struct rtl2830_dev {int fe_status; unsigned int post_bit_error; int post_bit_count; scalar_t__ sleeping; TYPE_1__ fe; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dvb_frontend {struct i2c_client* demodulator_priv; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;
struct TYPE_17__ {int uvalue; void* scale; } ;
struct TYPE_15__ {unsigned int uvalue; void* scale; } ;
struct TYPE_13__ {int svalue; void* scale; } ;
struct TYPE_11__ {unsigned int uvalue; void* scale; } ;

/* Variables and functions */
 int CONSTELLATION_NUM ; 
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 void* FE_SCALE_COUNTER ; 
 void* FE_SCALE_DECIBEL ; 
 void* FE_SCALE_NOT_AVAILABLE ; 
 void* FE_SCALE_RELATIVE ; 
 int HIERARCHY_NUM ; 
 unsigned int clamp_val (int,int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 struct rtl2830_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int const intlog10 (unsigned int) ; 
 int rtl2830_bulk_read (struct i2c_client*,int,int*,int) ; 
 int sign_extend32 (int,int) ; 

__attribute__((used)) static int rtl2830_read_status(struct dvb_frontend *fe, enum fe_status *status)
{
	struct i2c_client *client = fe->demodulator_priv;
	struct rtl2830_dev *dev = i2c_get_clientdata(client);
	struct dtv_frontend_properties *c = &dev->fe.dtv_property_cache;
	int ret, stmp;
	unsigned int utmp;
	u8 u8tmp, buf[2];

	*status = 0;

	if (dev->sleeping)
		return 0;

	ret = rtl2830_bulk_read(client, 0x351, &u8tmp, 1);
	if (ret)
		goto err;

	u8tmp = (u8tmp >> 3) & 0x0f; /* [6:3] */
	if (u8tmp == 11) {
		*status |= FE_HAS_SIGNAL | FE_HAS_CARRIER |
			FE_HAS_VITERBI | FE_HAS_SYNC | FE_HAS_LOCK;
	} else if (u8tmp == 10) {
		*status |= FE_HAS_SIGNAL | FE_HAS_CARRIER |
			FE_HAS_VITERBI;
	}

	dev->fe_status = *status;

	/* Signal strength */
	if (dev->fe_status & FE_HAS_SIGNAL) {
		/* Read IF AGC */
		ret = rtl2830_bulk_read(client, 0x359, buf, 2);
		if (ret)
			goto err;

		stmp = buf[0] << 8 | buf[1] << 0;
		stmp = sign_extend32(stmp, 13);
		utmp = clamp_val(-4 * stmp + 32767, 0x0000, 0xffff);

		dev_dbg(&client->dev, "IF AGC=%d\n", stmp);

		c->strength.stat[0].scale = FE_SCALE_RELATIVE;
		c->strength.stat[0].uvalue = utmp;
	} else {
		c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	}

	/* CNR */
	if (dev->fe_status & FE_HAS_VITERBI) {
		unsigned int hierarchy, constellation;
		#define CONSTELLATION_NUM 3
		#define HIERARCHY_NUM 4
		static const u32 constant[CONSTELLATION_NUM][HIERARCHY_NUM] = {
			{70705899, 70705899, 70705899, 70705899},
			{82433173, 82433173, 87483115, 94445660},
			{92888734, 92888734, 95487525, 99770748},
		};

		ret = rtl2830_bulk_read(client, 0x33c, &u8tmp, 1);
		if (ret)
			goto err;

		constellation = (u8tmp >> 2) & 0x03; /* [3:2] */
		if (constellation > CONSTELLATION_NUM - 1)
			goto err;

		hierarchy = (u8tmp >> 4) & 0x07; /* [6:4] */
		if (hierarchy > HIERARCHY_NUM - 1)
			goto err;

		ret = rtl2830_bulk_read(client, 0x40c, buf, 2);
		if (ret)
			goto err;

		utmp = buf[0] << 8 | buf[1] << 0;
		if (utmp)
			stmp = (constant[constellation][hierarchy] -
			       intlog10(utmp)) / ((1 << 24) / 10000);
		else
			stmp = 0;

		dev_dbg(&client->dev, "CNR raw=%u\n", utmp);

		c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
		c->cnr.stat[0].svalue = stmp;
	} else {
		c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	}

	/* BER */
	if (dev->fe_status & FE_HAS_LOCK) {
		ret = rtl2830_bulk_read(client, 0x34e, buf, 2);
		if (ret)
			goto err;

		utmp = buf[0] << 8 | buf[1] << 0;
		dev->post_bit_error += utmp;
		dev->post_bit_count += 1000000;

		dev_dbg(&client->dev, "BER errors=%u total=1000000\n", utmp);

		c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_error.stat[0].uvalue = dev->post_bit_error;
		c->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_count.stat[0].uvalue = dev->post_bit_count;
	} else {
		c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	}


	return ret;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}