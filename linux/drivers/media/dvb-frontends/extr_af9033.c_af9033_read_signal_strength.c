#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u8 ;
typedef  int u16 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dvb_frontend {struct af9033_dev* demodulator_priv; } ;
struct dtv_frontend_properties {int frequency; } ;
struct TYPE_2__ {struct dtv_frontend_properties dtv_property_cache; } ;
struct af9033_dev {int /*<<< orphan*/  regmap; scalar_t__ is_af9035; TYPE_1__ fe; struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 unsigned int** power_reference ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int,unsigned int*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 

__attribute__((used)) static int af9033_read_signal_strength(struct dvb_frontend *fe, u16 *strength)
{
	struct af9033_dev *dev = fe->demodulator_priv;
	struct i2c_client *client = dev->client;
	struct dtv_frontend_properties *c = &dev->fe.dtv_property_cache;
	int ret, tmp, power_real;
	unsigned int utmp;
	u8 gain_offset, buf[7];

	dev_dbg(&client->dev, "\n");

	if (dev->is_af9035) {
		/* Read signal strength of 0-100 scale */
		ret = regmap_read(dev->regmap, 0x800048, &utmp);
		if (ret)
			goto err;

		/* Scale value to 0x0000-0xffff */
		*strength = utmp * 0xffff / 100;
	} else {
		ret = regmap_read(dev->regmap, 0x8000f7, &utmp);
		if (ret)
			goto err;

		ret = regmap_bulk_read(dev->regmap, 0x80f900, buf, 7);
		if (ret)
			goto err;

		if (c->frequency <= 300000000)
			gain_offset = 7; /* VHF */
		else
			gain_offset = 4; /* UHF */

		power_real = (utmp - 100 - gain_offset) -
			power_reference[((buf[3] >> 0) & 3)][((buf[6] >> 0) & 7)];

		if (power_real < -15)
			tmp = 0;
		else if ((power_real >= -15) && (power_real < 0))
			tmp = (2 * (power_real + 15)) / 3;
		else if ((power_real >= 0) && (power_real < 20))
			tmp = 4 * power_real + 10;
		else if ((power_real >= 20) && (power_real < 35))
			tmp = (2 * (power_real - 20)) / 3 + 90;
		else
			tmp = 100;

		/* Scale value to 0x0000-0xffff */
		*strength = tmp * 0xffff / 100;
	}

	return 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}