#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct rtl2832_reg_value {int member_1; int value; int /*<<< orphan*/  reg; int /*<<< orphan*/  member_0; } ;
struct TYPE_11__ {int len; TYPE_9__* stat; } ;
struct TYPE_19__ {int len; TYPE_7__* stat; } ;
struct TYPE_17__ {int len; TYPE_5__* stat; } ;
struct TYPE_15__ {int len; TYPE_3__* stat; } ;
struct dtv_frontend_properties {TYPE_10__ post_bit_count; TYPE_8__ post_bit_error; TYPE_6__ cnr; TYPE_4__ strength; } ;
struct TYPE_12__ {struct dtv_frontend_properties dtv_property_cache; } ;
struct rtl2832_dev {int sleeping; TYPE_2__* pdata; TYPE_1__ fe; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dvb_frontend {struct rtl2832_dev* demodulator_priv; } ;
struct TYPE_20__ {void* scale; } ;
struct TYPE_18__ {void* scale; } ;
struct TYPE_16__ {void* scale; } ;
struct TYPE_14__ {void* scale; } ;
struct TYPE_13__ {int tuner; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct rtl2832_reg_value*) ; 
 int /*<<< orphan*/  DVBT_AD_AV_REF ; 
 int /*<<< orphan*/  DVBT_AD_EN_REG ; 
 int /*<<< orphan*/  DVBT_AD_EN_REG1 ; 
 int /*<<< orphan*/  DVBT_CDIV_PH0 ; 
 int /*<<< orphan*/  DVBT_CDIV_PH1 ; 
 int /*<<< orphan*/  DVBT_CR_THD_SET2 ; 
 int /*<<< orphan*/  DVBT_EN_BK_TRK ; 
 int /*<<< orphan*/  DVBT_EN_CACQ_NOTCH ; 
 int /*<<< orphan*/  DVBT_K1_CR_STEP12 ; 
 int /*<<< orphan*/  DVBT_KB_P1 ; 
 int /*<<< orphan*/  DVBT_KB_P2 ; 
 int /*<<< orphan*/  DVBT_KB_P3 ; 
 int /*<<< orphan*/  DVBT_MGD_THD0 ; 
 int /*<<< orphan*/  DVBT_MGD_THD1 ; 
 int /*<<< orphan*/  DVBT_MGD_THD2 ; 
 int /*<<< orphan*/  DVBT_MGD_THD3 ; 
 int /*<<< orphan*/  DVBT_MGD_THD4 ; 
 int /*<<< orphan*/  DVBT_MGD_THD5 ; 
 int /*<<< orphan*/  DVBT_MGD_THD6 ; 
 int /*<<< orphan*/  DVBT_MGD_THD7 ; 
 int /*<<< orphan*/  DVBT_MPEG_IO_OPT_1_0 ; 
 int /*<<< orphan*/  DVBT_MPEG_IO_OPT_2_2 ; 
 int /*<<< orphan*/  DVBT_PIP_ON ; 
 int /*<<< orphan*/  DVBT_REG_GPE ; 
 int /*<<< orphan*/  DVBT_REG_PI ; 
 int /*<<< orphan*/  DVBT_RSD_BER_FAIL_VAL ; 
 int /*<<< orphan*/  DVBT_SCALE1_B92 ; 
 int /*<<< orphan*/  DVBT_SCALE1_B93 ; 
 int /*<<< orphan*/  DVBT_SCALE1_BA7 ; 
 int /*<<< orphan*/  DVBT_SCALE1_BA9 ; 
 int /*<<< orphan*/  DVBT_SCALE1_BAA ; 
 int /*<<< orphan*/  DVBT_SCALE1_BAB ; 
 int /*<<< orphan*/  DVBT_SCALE1_BAC ; 
 int /*<<< orphan*/  DVBT_SCALE1_BB0 ; 
 int /*<<< orphan*/  DVBT_SCALE1_BB1 ; 
 int /*<<< orphan*/  DVBT_SERIAL ; 
 int /*<<< orphan*/  DVBT_SOFT_RST ; 
 int /*<<< orphan*/  DVBT_TRK_KC_I2 ; 
 int /*<<< orphan*/  DVBT_TRK_KS_I2 ; 
 int /*<<< orphan*/  DVBT_TRK_KS_P2 ; 
 int /*<<< orphan*/  DVBT_TR_THD_SET2 ; 
 int EINVAL ; 
 void* FE_SCALE_NOT_AVAILABLE ; 
#define  RTL2832_TUNER_E4000 135 
#define  RTL2832_TUNER_FC0012 134 
#define  RTL2832_TUNER_FC0013 133 
#define  RTL2832_TUNER_FC2580 132 
#define  RTL2832_TUNER_R820T 131 
#define  RTL2832_TUNER_R828D 130 
#define  RTL2832_TUNER_SI2157 129 
#define  RTL2832_TUNER_TUA9001 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 struct rtl2832_reg_value* rtl2832_tuner_init_e4000 ; 
 struct rtl2832_reg_value* rtl2832_tuner_init_fc0012 ; 
 struct rtl2832_reg_value* rtl2832_tuner_init_fc2580 ; 
 struct rtl2832_reg_value* rtl2832_tuner_init_r820t ; 
 struct rtl2832_reg_value* rtl2832_tuner_init_si2157 ; 
 struct rtl2832_reg_value* rtl2832_tuner_init_tua9001 ; 
 int rtl2832_wr_demod_reg (struct rtl2832_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rtl2832_init(struct dvb_frontend *fe)
{
	struct rtl2832_dev *dev = fe->demodulator_priv;
	struct i2c_client *client = dev->client;
	struct dtv_frontend_properties *c = &dev->fe.dtv_property_cache;
	const struct rtl2832_reg_value *init;
	int i, ret, len;
	/* initialization values for the demodulator registers */
	struct rtl2832_reg_value rtl2832_initial_regs[] = {
		{DVBT_AD_EN_REG,		0x1},
		{DVBT_AD_EN_REG1,		0x1},
		{DVBT_RSD_BER_FAIL_VAL,		0x2800},
		{DVBT_MGD_THD0,			0x10},
		{DVBT_MGD_THD1,			0x20},
		{DVBT_MGD_THD2,			0x20},
		{DVBT_MGD_THD3,			0x40},
		{DVBT_MGD_THD4,			0x22},
		{DVBT_MGD_THD5,			0x32},
		{DVBT_MGD_THD6,			0x37},
		{DVBT_MGD_THD7,			0x39},
		{DVBT_EN_BK_TRK,		0x0},
		{DVBT_EN_CACQ_NOTCH,		0x0},
		{DVBT_AD_AV_REF,		0x2a},
		{DVBT_REG_PI,			0x6},
		{DVBT_PIP_ON,			0x0},
		{DVBT_CDIV_PH0,			0x8},
		{DVBT_CDIV_PH1,			0x8},
		{DVBT_SCALE1_B92,		0x4},
		{DVBT_SCALE1_B93,		0xb0},
		{DVBT_SCALE1_BA7,		0x78},
		{DVBT_SCALE1_BA9,		0x28},
		{DVBT_SCALE1_BAA,		0x59},
		{DVBT_SCALE1_BAB,		0x83},
		{DVBT_SCALE1_BAC,		0xd4},
		{DVBT_SCALE1_BB0,		0x65},
		{DVBT_SCALE1_BB1,		0x43},
		{DVBT_KB_P1,			0x1},
		{DVBT_KB_P2,			0x4},
		{DVBT_KB_P3,			0x7},
		{DVBT_K1_CR_STEP12,		0xa},
		{DVBT_REG_GPE,			0x1},
		{DVBT_SERIAL,			0x0},
		{DVBT_CDIV_PH0,			0x9},
		{DVBT_CDIV_PH1,			0x9},
		{DVBT_MPEG_IO_OPT_2_2,		0x0},
		{DVBT_MPEG_IO_OPT_1_0,		0x0},
		{DVBT_TRK_KS_P2,		0x4},
		{DVBT_TRK_KS_I2,		0x7},
		{DVBT_TR_THD_SET2,		0x6},
		{DVBT_TRK_KC_I2,		0x5},
		{DVBT_CR_THD_SET2,		0x1},
	};

	dev_dbg(&client->dev, "\n");

	ret = rtl2832_wr_demod_reg(dev, DVBT_SOFT_RST, 0x0);
	if (ret)
		goto err;

	for (i = 0; i < ARRAY_SIZE(rtl2832_initial_regs); i++) {
		ret = rtl2832_wr_demod_reg(dev, rtl2832_initial_regs[i].reg,
			rtl2832_initial_regs[i].value);
		if (ret)
			goto err;
	}

	/* load tuner specific settings */
	dev_dbg(&client->dev, "load settings for tuner=%02x\n",
		dev->pdata->tuner);
	switch (dev->pdata->tuner) {
	case RTL2832_TUNER_FC2580:
		len = ARRAY_SIZE(rtl2832_tuner_init_fc2580);
		init = rtl2832_tuner_init_fc2580;
		break;
	case RTL2832_TUNER_FC0012:
	case RTL2832_TUNER_FC0013:
		len = ARRAY_SIZE(rtl2832_tuner_init_fc0012);
		init = rtl2832_tuner_init_fc0012;
		break;
	case RTL2832_TUNER_TUA9001:
		len = ARRAY_SIZE(rtl2832_tuner_init_tua9001);
		init = rtl2832_tuner_init_tua9001;
		break;
	case RTL2832_TUNER_E4000:
		len = ARRAY_SIZE(rtl2832_tuner_init_e4000);
		init = rtl2832_tuner_init_e4000;
		break;
	case RTL2832_TUNER_R820T:
	case RTL2832_TUNER_R828D:
		len = ARRAY_SIZE(rtl2832_tuner_init_r820t);
		init = rtl2832_tuner_init_r820t;
		break;
	case RTL2832_TUNER_SI2157:
		len = ARRAY_SIZE(rtl2832_tuner_init_si2157);
		init = rtl2832_tuner_init_si2157;
		break;
	default:
		ret = -EINVAL;
		goto err;
	}

	for (i = 0; i < len; i++) {
		ret = rtl2832_wr_demod_reg(dev, init[i].reg, init[i].value);
		if (ret)
			goto err;
	}

	/* init stats here in order signal app which stats are supported */
	c->strength.len = 1;
	c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->cnr.len = 1;
	c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_error.len = 1;
	c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_count.len = 1;
	c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	dev->sleeping = false;

	return 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}