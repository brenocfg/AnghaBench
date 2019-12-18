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
struct m88ds3103_dev {int fe_status; unsigned int post_bit_error; unsigned int post_bit_count; unsigned int dvbv3_ber; int /*<<< orphan*/  regmap; int /*<<< orphan*/  warm; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {TYPE_3__* stat; } ;
struct TYPE_8__ {TYPE_1__* stat; } ;
struct TYPE_11__ {TYPE_6__* stat; } ;
struct dtv_frontend_properties {int delivery_system; TYPE_4__ post_bit_count; TYPE_2__ post_bit_error; TYPE_5__ cnr; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct m88ds3103_dev* demodulator_priv; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;
struct TYPE_12__ {unsigned int svalue; void* scale; } ;
struct TYPE_9__ {unsigned int uvalue; void* scale; } ;
struct TYPE_7__ {unsigned int uvalue; void* scale; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int) ; 
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
 int M88DS3103_SNR_ITERATIONS ; 
#define  SYS_DVBS 129 
#define  SYS_DVBS2 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 unsigned int div_u64 (int,int) ; 
 int intlog10 (int) ; 
 int intlog2 (int) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int,int*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int m88ds3103_read_status(struct dvb_frontend *fe,
				 enum fe_status *status)
{
	struct m88ds3103_dev *dev = fe->demodulator_priv;
	struct i2c_client *client = dev->client;
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	int ret, i, itmp;
	unsigned int utmp;
	u8 buf[3];

	*status = 0;

	if (!dev->warm) {
		ret = -EAGAIN;
		goto err;
	}

	switch (c->delivery_system) {
	case SYS_DVBS:
		ret = regmap_read(dev->regmap, 0xd1, &utmp);
		if (ret)
			goto err;

		if ((utmp & 0x07) == 0x07)
			*status = FE_HAS_SIGNAL | FE_HAS_CARRIER |
					FE_HAS_VITERBI | FE_HAS_SYNC |
					FE_HAS_LOCK;
		break;
	case SYS_DVBS2:
		ret = regmap_read(dev->regmap, 0x0d, &utmp);
		if (ret)
			goto err;

		if ((utmp & 0x8f) == 0x8f)
			*status = FE_HAS_SIGNAL | FE_HAS_CARRIER |
					FE_HAS_VITERBI | FE_HAS_SYNC |
					FE_HAS_LOCK;
		break;
	default:
		dev_dbg(&client->dev, "invalid delivery_system\n");
		ret = -EINVAL;
		goto err;
	}

	dev->fe_status = *status;
	dev_dbg(&client->dev, "lock=%02x status=%02x\n", utmp, *status);

	/* CNR */
	if (dev->fe_status & FE_HAS_VITERBI) {
		unsigned int cnr, noise, signal, noise_tot, signal_tot;

		cnr = 0;
		/* more iterations for more accurate estimation */
		#define M88DS3103_SNR_ITERATIONS 3

		switch (c->delivery_system) {
		case SYS_DVBS:
			itmp = 0;

			for (i = 0; i < M88DS3103_SNR_ITERATIONS; i++) {
				ret = regmap_read(dev->regmap, 0xff, &utmp);
				if (ret)
					goto err;

				itmp += utmp;
			}

			/* use of single register limits max value to 15 dB */
			/* SNR(X) dB = 10 * ln(X) / ln(10) dB */
			itmp = DIV_ROUND_CLOSEST(itmp, 8 * M88DS3103_SNR_ITERATIONS);
			if (itmp)
				cnr = div_u64((u64) 10000 * intlog2(itmp), intlog2(10));
			break;
		case SYS_DVBS2:
			noise_tot = 0;
			signal_tot = 0;

			for (i = 0; i < M88DS3103_SNR_ITERATIONS; i++) {
				ret = regmap_bulk_read(dev->regmap, 0x8c, buf, 3);
				if (ret)
					goto err;

				noise = buf[1] << 6;    /* [13:6] */
				noise |= buf[0] & 0x3f; /*  [5:0] */
				noise >>= 2;
				signal = buf[2] * buf[2];
				signal >>= 1;

				noise_tot += noise;
				signal_tot += signal;
			}

			noise = noise_tot / M88DS3103_SNR_ITERATIONS;
			signal = signal_tot / M88DS3103_SNR_ITERATIONS;

			/* SNR(X) dB = 10 * log10(X) dB */
			if (signal > noise) {
				itmp = signal / noise;
				cnr = div_u64((u64) 10000 * intlog10(itmp), (1 << 24));
			}
			break;
		default:
			dev_dbg(&client->dev, "invalid delivery_system\n");
			ret = -EINVAL;
			goto err;
		}

		if (cnr) {
			c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
			c->cnr.stat[0].svalue = cnr;
		} else {
			c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		}
	} else {
		c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	}

	/* BER */
	if (dev->fe_status & FE_HAS_LOCK) {
		unsigned int utmp, post_bit_error, post_bit_count;

		switch (c->delivery_system) {
		case SYS_DVBS:
			ret = regmap_write(dev->regmap, 0xf9, 0x04);
			if (ret)
				goto err;

			ret = regmap_read(dev->regmap, 0xf8, &utmp);
			if (ret)
				goto err;

			/* measurement ready? */
			if (!(utmp & 0x10)) {
				ret = regmap_bulk_read(dev->regmap, 0xf6, buf, 2);
				if (ret)
					goto err;

				post_bit_error = buf[1] << 8 | buf[0] << 0;
				post_bit_count = 0x800000;
				dev->post_bit_error += post_bit_error;
				dev->post_bit_count += post_bit_count;
				dev->dvbv3_ber = post_bit_error;

				/* restart measurement */
				utmp |= 0x10;
				ret = regmap_write(dev->regmap, 0xf8, utmp);
				if (ret)
					goto err;
			}
			break;
		case SYS_DVBS2:
			ret = regmap_bulk_read(dev->regmap, 0xd5, buf, 3);
			if (ret)
				goto err;

			utmp = buf[2] << 16 | buf[1] << 8 | buf[0] << 0;

			/* enough data? */
			if (utmp > 4000) {
				ret = regmap_bulk_read(dev->regmap, 0xf7, buf, 2);
				if (ret)
					goto err;

				post_bit_error = buf[1] << 8 | buf[0] << 0;
				post_bit_count = 32 * utmp; /* TODO: FEC */
				dev->post_bit_error += post_bit_error;
				dev->post_bit_count += post_bit_count;
				dev->dvbv3_ber = post_bit_error;

				/* restart measurement */
				ret = regmap_write(dev->regmap, 0xd1, 0x01);
				if (ret)
					goto err;

				ret = regmap_write(dev->regmap, 0xf9, 0x01);
				if (ret)
					goto err;

				ret = regmap_write(dev->regmap, 0xf9, 0x00);
				if (ret)
					goto err;

				ret = regmap_write(dev->regmap, 0xd1, 0x00);
				if (ret)
					goto err;
			}
			break;
		default:
			dev_dbg(&client->dev, "invalid delivery_system\n");
			ret = -EINVAL;
			goto err;
		}

		c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_error.stat[0].uvalue = dev->post_bit_error;
		c->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_count.stat[0].uvalue = dev->post_bit_count;
	} else {
		c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	}

	return 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}