#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_13__ {int len; TYPE_9__* stat; } ;
struct TYPE_23__ {int len; TYPE_7__* stat; } ;
struct TYPE_21__ {int len; TYPE_5__* stat; } ;
struct TYPE_19__ {int len; TYPE_3__* stat; } ;
struct TYPE_17__ {TYPE_1__* stat; } ;
struct TYPE_15__ {int len; TYPE_11__* stat; } ;
struct dtv_frontend_properties {TYPE_10__ post_bit_error; TYPE_8__ post_bit_count; TYPE_6__ block_error; TYPE_4__ block_count; TYPE_2__ cnr; TYPE_12__ strength; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct af9033_dev* demodulator_priv; } ;
struct af9033_dev {int fe_status; int error_block_count; int total_block_count; int post_bit_error; int post_bit_count; int /*<<< orphan*/  regmap; scalar_t__ is_af9035; struct i2c_client* client; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;
struct TYPE_24__ {int uvalue; void* scale; } ;
struct TYPE_22__ {int uvalue; void* scale; } ;
struct TYPE_20__ {int uvalue; void* scale; } ;
struct TYPE_18__ {int uvalue; void* scale; } ;
struct TYPE_16__ {unsigned int svalue; void* scale; } ;
struct TYPE_14__ {int svalue; void* scale; } ;

/* Variables and functions */
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 void* FE_SCALE_COUNTER ; 
 void* FE_SCALE_DECIBEL ; 
 void* FE_SCALE_NOT_AVAILABLE ; 
 unsigned int clamp (unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ intlog10 (int) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int,int*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 

__attribute__((used)) static int af9033_read_status(struct dvb_frontend *fe, enum fe_status *status)
{
	struct af9033_dev *dev = fe->demodulator_priv;
	struct i2c_client *client = dev->client;
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	int ret, tmp = 0;
	u8 buf[7];
	unsigned int utmp, utmp1;

	dev_dbg(&client->dev, "\n");

	*status = 0;

	/* Radio channel status: 0=no result, 1=has signal, 2=no signal */
	ret = regmap_read(dev->regmap, 0x800047, &utmp);
	if (ret)
		goto err;

	/* Has signal */
	if (utmp == 0x01)
		*status |= FE_HAS_SIGNAL;

	if (utmp != 0x02) {
		/* TPS lock */
		ret = regmap_read(dev->regmap, 0x80f5a9, &utmp);
		if (ret)
			goto err;

		if ((utmp >> 0) & 0x01)
			*status |= FE_HAS_SIGNAL | FE_HAS_CARRIER |
					FE_HAS_VITERBI;

		/* Full lock */
		ret = regmap_read(dev->regmap, 0x80f999, &utmp);
		if (ret)
			goto err;

		if ((utmp >> 0) & 0x01)
			*status |= FE_HAS_SIGNAL | FE_HAS_CARRIER |
					FE_HAS_VITERBI | FE_HAS_SYNC |
					FE_HAS_LOCK;
	}

	dev->fe_status = *status;

	/* Signal strength */
	if (dev->fe_status & FE_HAS_SIGNAL) {
		if (dev->is_af9035) {
			ret = regmap_read(dev->regmap, 0x80004a, &utmp);
			if (ret)
				goto err;
			tmp = -utmp * 1000;
		} else {
			ret = regmap_read(dev->regmap, 0x8000f7, &utmp);
			if (ret)
				goto err;
			tmp = (utmp - 100) * 1000;
		}

		c->strength.len = 1;
		c->strength.stat[0].scale = FE_SCALE_DECIBEL;
		c->strength.stat[0].svalue = tmp;
	} else {
		c->strength.len = 1;
		c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	}

	/* CNR */
	if (dev->fe_status & FE_HAS_VITERBI) {
		/* Read raw SNR value */
		ret = regmap_bulk_read(dev->regmap, 0x80002c, buf, 3);
		if (ret)
			goto err;

		utmp1 = buf[2] << 16 | buf[1] << 8 | buf[0] << 0;

		/* Read superframe number */
		ret = regmap_read(dev->regmap, 0x80f78b, &utmp);
		if (ret)
			goto err;

		if (utmp)
			utmp1 /= utmp;

		/* Read current transmission mode */
		ret = regmap_read(dev->regmap, 0x80f900, &utmp);
		if (ret)
			goto err;

		switch ((utmp >> 0) & 3) {
		case 0:
			/* 2k */
			utmp1 *= 4;
			break;
		case 1:
			/* 8k */
			utmp1 *= 1;
			break;
		case 2:
			/* 4k */
			utmp1 *= 2;
			break;
		default:
			utmp1 *= 0;
			break;
		}

		/* Read current modulation */
		ret = regmap_read(dev->regmap, 0x80f903, &utmp);
		if (ret)
			goto err;

		switch ((utmp >> 0) & 3) {
		case 0:
			/*
			 * QPSK
			 * CNR[dB] 13 * -log10((1690000 - value) / value) + 2.6
			 * value [653799, 1689999], 2.6 / 13 = 3355443
			 */
			utmp1 = clamp(utmp1, 653799U, 1689999U);
			utmp1 = ((u64)(intlog10(utmp1)
				 - intlog10(1690000 - utmp1)
				 + 3355443) * 13 * 1000) >> 24;
			break;
		case 1:
			/*
			 * QAM-16
			 * CNR[dB] 6 * log10((value - 370000) / (828000 - value)) + 15.7
			 * value [371105, 827999], 15.7 / 6 = 43900382
			 */
			utmp1 = clamp(utmp1, 371105U, 827999U);
			utmp1 = ((u64)(intlog10(utmp1 - 370000)
				 - intlog10(828000 - utmp1)
				 + 43900382) * 6 * 1000) >> 24;
			break;
		case 2:
			/*
			 * QAM-64
			 * CNR[dB] 8 * log10((value - 193000) / (425000 - value)) + 23.8
			 * value [193246, 424999], 23.8 / 8 = 49912218
			 */
			utmp1 = clamp(utmp1, 193246U, 424999U);
			utmp1 = ((u64)(intlog10(utmp1 - 193000)
				 - intlog10(425000 - utmp1)
				 + 49912218) * 8 * 1000) >> 24;
			break;
		default:
			utmp1 = 0;
			break;
		}

		dev_dbg(&client->dev, "cnr=%u\n", utmp1);

		c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
		c->cnr.stat[0].svalue = utmp1;
	} else {
		c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	}

	/* UCB/PER/BER */
	if (dev->fe_status & FE_HAS_LOCK) {
		/* Outer FEC, 204 byte packets */
		u16 abort_packet_count, rsd_packet_count;
		/* Inner FEC, bits */
		u32 rsd_bit_err_count;

		/*
		 * Packet count used for measurement is 10000
		 * (rsd_packet_count). Maybe it should be increased?
		 */

		ret = regmap_bulk_read(dev->regmap, 0x800032, buf, 7);
		if (ret)
			goto err;

		abort_packet_count = (buf[1] << 8) | (buf[0] << 0);
		rsd_bit_err_count = (buf[4] << 16) | (buf[3] << 8) | buf[2];
		rsd_packet_count = (buf[6] << 8) | (buf[5] << 0);

		dev->error_block_count += abort_packet_count;
		dev->total_block_count += rsd_packet_count;
		dev->post_bit_error += rsd_bit_err_count;
		dev->post_bit_count += rsd_packet_count * 204 * 8;

		c->block_count.len = 1;
		c->block_count.stat[0].scale = FE_SCALE_COUNTER;
		c->block_count.stat[0].uvalue = dev->total_block_count;

		c->block_error.len = 1;
		c->block_error.stat[0].scale = FE_SCALE_COUNTER;
		c->block_error.stat[0].uvalue = dev->error_block_count;

		c->post_bit_count.len = 1;
		c->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_count.stat[0].uvalue = dev->post_bit_count;

		c->post_bit_error.len = 1;
		c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_error.stat[0].uvalue = dev->post_bit_error;
	}

	return 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}