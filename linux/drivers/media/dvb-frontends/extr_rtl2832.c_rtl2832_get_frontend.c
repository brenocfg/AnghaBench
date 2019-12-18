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
struct rtl2832_dev {int /*<<< orphan*/  regmap; scalar_t__ sleeping; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dvb_frontend {struct rtl2832_dev* demodulator_priv; } ;
struct dtv_frontend_properties {void* code_rate_LP; void* code_rate_HP; int /*<<< orphan*/  hierarchy; int /*<<< orphan*/  guard_interval; int /*<<< orphan*/  transmission_mode; int /*<<< orphan*/  modulation; } ;

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
 int /*<<< orphan*/  QAM_16 ; 
 int /*<<< orphan*/  QAM_64 ; 
 int /*<<< orphan*/  QPSK ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_2K ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_8K ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int,int*,int) ; 

__attribute__((used)) static int rtl2832_get_frontend(struct dvb_frontend *fe,
				struct dtv_frontend_properties *c)
{
	struct rtl2832_dev *dev = fe->demodulator_priv;
	struct i2c_client *client = dev->client;
	int ret;
	u8 buf[3];

	if (dev->sleeping)
		return 0;

	ret = regmap_bulk_read(dev->regmap, 0x33c, buf, 2);
	if (ret)
		goto err;

	ret = regmap_bulk_read(dev->regmap, 0x351, &buf[2], 1);
	if (ret)
		goto err;

	dev_dbg(&client->dev, "TPS=%*ph\n", 3, buf);

	switch ((buf[0] >> 2) & 3) {
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

	switch ((buf[2] >> 2) & 1) {
	case 0:
		c->transmission_mode = TRANSMISSION_MODE_2K;
		break;
	case 1:
		c->transmission_mode = TRANSMISSION_MODE_8K;
	}

	switch ((buf[2] >> 0) & 3) {
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

	switch ((buf[0] >> 4) & 7) {
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

	switch ((buf[1] >> 3) & 7) {
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

	switch ((buf[1] >> 0) & 7) {
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

	return 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}