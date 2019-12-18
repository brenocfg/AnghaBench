#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dvb_frontend {struct af9033_dev* demodulator_priv; } ;
struct TYPE_6__ {TYPE_2__* stat; } ;
struct dtv_frontend_properties {TYPE_3__ cnr; } ;
struct TYPE_4__ {struct dtv_frontend_properties dtv_property_cache; } ;
struct af9033_dev {int /*<<< orphan*/  regmap; scalar_t__ is_af9035; TYPE_1__ fe; struct i2c_client* client; } ;
struct TYPE_5__ {scalar_t__ scale; int /*<<< orphan*/  svalue; } ;

/* Variables and functions */
 scalar_t__ FE_SCALE_DECIBEL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int div_s64 (int /*<<< orphan*/ ,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 

__attribute__((used)) static int af9033_read_snr(struct dvb_frontend *fe, u16 *snr)
{
	struct af9033_dev *dev = fe->demodulator_priv;
	struct i2c_client *client = dev->client;
	struct dtv_frontend_properties *c = &dev->fe.dtv_property_cache;
	int ret;
	unsigned int utmp;

	dev_dbg(&client->dev, "\n");

	/* Use DVBv5 CNR */
	if (c->cnr.stat[0].scale == FE_SCALE_DECIBEL) {
		/* Return 0.1 dB for AF9030 and 0-0xffff for IT9130. */
		if (dev->is_af9035) {
			/* 1000x => 10x (0.1 dB) */
			*snr = div_s64(c->cnr.stat[0].svalue, 100);
		} else {
			/* 1000x => 1x (1 dB) */
			*snr = div_s64(c->cnr.stat[0].svalue, 1000);

			/* Read current modulation */
			ret = regmap_read(dev->regmap, 0x80f903, &utmp);
			if (ret)
				goto err;

			/* scale value to 0x0000-0xffff */
			switch ((utmp >> 0) & 3) {
			case 0:
				*snr = *snr * 0xffff / 23;
				break;
			case 1:
				*snr = *snr * 0xffff / 26;
				break;
			case 2:
				*snr = *snr * 0xffff / 32;
				break;
			default:
				goto err;
			}
		}
	} else {
		*snr = 0;
	}

	return 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}