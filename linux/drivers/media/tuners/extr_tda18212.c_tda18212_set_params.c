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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  if_dvbc; int /*<<< orphan*/  if_dvbt2_8; int /*<<< orphan*/  if_dvbt2_7; int /*<<< orphan*/  if_dvbt2_6; int /*<<< orphan*/  if_dvbt_8; int /*<<< orphan*/  if_dvbt_7; int /*<<< orphan*/  if_dvbt_6; int /*<<< orphan*/  if_atsc_qam; int /*<<< orphan*/  if_atsc_vsb; } ;
struct tda18212_dev {int if_frequency; TYPE_3__* client; int /*<<< orphan*/  regmap; TYPE_1__ cfg; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dtv_frontend_properties {int delivery_system; int frequency; int /*<<< orphan*/  bandwidth_hz; } ;
struct dvb_frontend {TYPE_2__ ops; struct dtv_frontend_properties dtv_property_cache; struct tda18212_dev* tuner_priv; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  ATSC_QAM 143 
#define  ATSC_VSB 142 
 int DIV_ROUND_CLOSEST (int /*<<< orphan*/ ,int) ; 
#define  DVBC_6 141 
#define  DVBC_8 140 
#define  DVBT2_6 139 
#define  DVBT2_7 138 
#define  DVBT2_8 137 
#define  DVBT_6 136 
#define  DVBT_7 135 
#define  DVBT_8 134 
 int EINVAL ; 
#define  SYS_ATSC 133 
#define  SYS_DVBC_ANNEX_A 132 
#define  SYS_DVBC_ANNEX_B 131 
#define  SYS_DVBC_ANNEX_C 130 
#define  SYS_DVBT 129 
#define  SYS_DVBT2 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int,int*,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int,int const) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 

__attribute__((used)) static int tda18212_set_params(struct dvb_frontend *fe)
{
	struct tda18212_dev *dev = fe->tuner_priv;
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	int ret, i;
	u32 if_khz;
	u8 buf[9];
	#define DVBT_6   0
	#define DVBT_7   1
	#define DVBT_8   2
	#define DVBT2_6  3
	#define DVBT2_7  4
	#define DVBT2_8  5
	#define DVBC_6   6
	#define DVBC_8   7
	#define ATSC_VSB 8
	#define ATSC_QAM 9
	static const u8 bw_params[][3] = {
		     /* reg:   0f    13    23 */
		[DVBT_6]  = { 0xb3, 0x20, 0x03 },
		[DVBT_7]  = { 0xb3, 0x31, 0x01 },
		[DVBT_8]  = { 0xb3, 0x22, 0x01 },
		[DVBT2_6] = { 0xbc, 0x20, 0x03 },
		[DVBT2_7] = { 0xbc, 0x72, 0x03 },
		[DVBT2_8] = { 0xbc, 0x22, 0x01 },
		[DVBC_6]  = { 0x92, 0x50, 0x03 },
		[DVBC_8]  = { 0x92, 0x53, 0x03 },
		[ATSC_VSB] = { 0x7d, 0x20, 0x63 },
		[ATSC_QAM] = { 0x7d, 0x20, 0x63 },
	};

	dev_dbg(&dev->client->dev,
			"delivery_system=%d frequency=%d bandwidth_hz=%d\n",
			c->delivery_system, c->frequency,
			c->bandwidth_hz);

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* open I2C-gate */

	switch (c->delivery_system) {
	case SYS_ATSC:
		if_khz = dev->cfg.if_atsc_vsb;
		i = ATSC_VSB;
		break;
	case SYS_DVBC_ANNEX_B:
		if_khz = dev->cfg.if_atsc_qam;
		i = ATSC_QAM;
		break;
	case SYS_DVBT:
		switch (c->bandwidth_hz) {
		case 6000000:
			if_khz = dev->cfg.if_dvbt_6;
			i = DVBT_6;
			break;
		case 7000000:
			if_khz = dev->cfg.if_dvbt_7;
			i = DVBT_7;
			break;
		case 8000000:
			if_khz = dev->cfg.if_dvbt_8;
			i = DVBT_8;
			break;
		default:
			ret = -EINVAL;
			goto error;
		}
		break;
	case SYS_DVBT2:
		switch (c->bandwidth_hz) {
		case 6000000:
			if_khz = dev->cfg.if_dvbt2_6;
			i = DVBT2_6;
			break;
		case 7000000:
			if_khz = dev->cfg.if_dvbt2_7;
			i = DVBT2_7;
			break;
		case 8000000:
			if_khz = dev->cfg.if_dvbt2_8;
			i = DVBT2_8;
			break;
		default:
			ret = -EINVAL;
			goto error;
		}
		break;
	case SYS_DVBC_ANNEX_A:
	case SYS_DVBC_ANNEX_C:
		if_khz = dev->cfg.if_dvbc;
		i = DVBC_8;
		break;
	default:
		ret = -EINVAL;
		goto error;
	}

	ret = regmap_write(dev->regmap, 0x23, bw_params[i][2]);
	if (ret)
		goto error;

	ret = regmap_write(dev->regmap, 0x06, 0x00);
	if (ret)
		goto error;

	ret = regmap_write(dev->regmap, 0x0f, bw_params[i][0]);
	if (ret)
		goto error;

	buf[0] = 0x02;
	buf[1] = bw_params[i][1];
	buf[2] = 0x03; /* default value */
	buf[3] = DIV_ROUND_CLOSEST(if_khz, 50);
	buf[4] = ((c->frequency / 1000) >> 16) & 0xff;
	buf[5] = ((c->frequency / 1000) >>  8) & 0xff;
	buf[6] = ((c->frequency / 1000) >>  0) & 0xff;
	buf[7] = 0xc1;
	buf[8] = 0x01;
	ret = regmap_bulk_write(dev->regmap, 0x12, buf, sizeof(buf));
	if (ret)
		goto error;

	/* actual IF rounded as it is on register */
	dev->if_frequency = buf[3] * 50 * 1000;

exit:
	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* close I2C-gate */

	return ret;

error:
	dev_dbg(&dev->client->dev, "failed=%d\n", ret);
	goto exit;
}