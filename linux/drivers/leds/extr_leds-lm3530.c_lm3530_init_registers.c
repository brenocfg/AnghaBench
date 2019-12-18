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
typedef  int u8 ;
struct lm3530_pwm_data {int /*<<< orphan*/  (* pwm_set_intensity ) (int,int) ;} ;
struct lm3530_platform_data {int brt_ramp_law; int max_current; int pwm_pol_hi; int brt_ramp_fall; int brt_ramp_rise; int brt_val; struct lm3530_pwm_data pwm_data; } ;
struct TYPE_2__ {int max_brightness; } ;
struct lm3530_data {int mode; int brightness; TYPE_1__ led_dev; struct i2c_client* client; struct lm3530_platform_data* pdata; } ;
struct lm3530_als_data {int config; int imp_sel; int* zones; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
#define  LM3530_BL_MODE_ALS 130 
#define  LM3530_BL_MODE_MANUAL 129 
#define  LM3530_BL_MODE_PWM 128 
 scalar_t__ LM3530_BRT_CTRL_REG ; 
 int LM3530_BRT_RAMP_FALL_SHIFT ; 
 int LM3530_BRT_RAMP_RISE_SHIFT ; 
 int LM3530_DEF_ZT_0 ; 
 int LM3530_DEF_ZT_1 ; 
 int LM3530_DEF_ZT_2 ; 
 int LM3530_DEF_ZT_3 ; 
 int LM3530_DEF_ZT_4 ; 
 int LM3530_ENABLE_I2C ; 
 int LM3530_ENABLE_PWM ; 
 int LM3530_ENABLE_PWM_SIMPLE ; 
 int LM3530_MAX_CURR_SHIFT ; 
 int LM3530_PWM_POL_SHIFT ; 
 int LM3530_RAMP_LAW_SHIFT ; 
 int LM3530_REG_MAX ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,scalar_t__,int) ; 
 int /*<<< orphan*/  lm3530_als_configure (struct lm3530_platform_data*,struct lm3530_als_data*) ; 
 int lm3530_led_enable (struct lm3530_data*) ; 
 scalar_t__* lm3530_reg ; 
 int /*<<< orphan*/  memset (struct lm3530_als_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int,int) ; 

__attribute__((used)) static int lm3530_init_registers(struct lm3530_data *drvdata)
{
	int ret = 0;
	int i;
	u8 gen_config;
	u8 brt_ramp;
	u8 brightness;
	u8 reg_val[LM3530_REG_MAX];
	struct lm3530_platform_data *pdata = drvdata->pdata;
	struct i2c_client *client = drvdata->client;
	struct lm3530_pwm_data *pwm = &pdata->pwm_data;
	struct lm3530_als_data als;

	memset(&als, 0, sizeof(struct lm3530_als_data));

	gen_config = (pdata->brt_ramp_law << LM3530_RAMP_LAW_SHIFT) |
			((pdata->max_current & 7) << LM3530_MAX_CURR_SHIFT);

	switch (drvdata->mode) {
	case LM3530_BL_MODE_MANUAL:
		gen_config |= LM3530_ENABLE_I2C;
		break;
	case LM3530_BL_MODE_ALS:
		gen_config |= LM3530_ENABLE_I2C;
		lm3530_als_configure(pdata, &als);
		break;
	case LM3530_BL_MODE_PWM:
		gen_config |= LM3530_ENABLE_PWM | LM3530_ENABLE_PWM_SIMPLE |
			      (pdata->pwm_pol_hi << LM3530_PWM_POL_SHIFT);
		break;
	}

	brt_ramp = (pdata->brt_ramp_fall << LM3530_BRT_RAMP_FALL_SHIFT) |
			(pdata->brt_ramp_rise << LM3530_BRT_RAMP_RISE_SHIFT);

	if (drvdata->brightness)
		brightness = drvdata->brightness;
	else
		brightness = drvdata->brightness = pdata->brt_val;

	if (brightness > drvdata->led_dev.max_brightness)
		brightness = drvdata->led_dev.max_brightness;

	reg_val[0] = gen_config;	/* LM3530_GEN_CONFIG */
	reg_val[1] = als.config;	/* LM3530_ALS_CONFIG */
	reg_val[2] = brt_ramp;		/* LM3530_BRT_RAMP_RATE */
	reg_val[3] = als.imp_sel;	/* LM3530_ALS_IMP_SELECT */
	reg_val[4] = brightness;	/* LM3530_BRT_CTRL_REG */
	reg_val[5] = als.zones[0];	/* LM3530_ALS_ZB0_REG */
	reg_val[6] = als.zones[1];	/* LM3530_ALS_ZB1_REG */
	reg_val[7] = als.zones[2];	/* LM3530_ALS_ZB2_REG */
	reg_val[8] = als.zones[3];	/* LM3530_ALS_ZB3_REG */
	reg_val[9] = LM3530_DEF_ZT_0;	/* LM3530_ALS_Z0T_REG */
	reg_val[10] = LM3530_DEF_ZT_1;	/* LM3530_ALS_Z1T_REG */
	reg_val[11] = LM3530_DEF_ZT_2;	/* LM3530_ALS_Z2T_REG */
	reg_val[12] = LM3530_DEF_ZT_3;	/* LM3530_ALS_Z3T_REG */
	reg_val[13] = LM3530_DEF_ZT_4;	/* LM3530_ALS_Z4T_REG */

	ret = lm3530_led_enable(drvdata);
	if (ret)
		return ret;

	for (i = 0; i < LM3530_REG_MAX; i++) {
		/* do not update brightness register when pwm mode */
		if (lm3530_reg[i] == LM3530_BRT_CTRL_REG &&
		    drvdata->mode == LM3530_BL_MODE_PWM) {
			if (pwm->pwm_set_intensity)
				pwm->pwm_set_intensity(reg_val[i],
					drvdata->led_dev.max_brightness);
			continue;
		}

		ret = i2c_smbus_write_byte_data(client,
				lm3530_reg[i], reg_val[i]);
		if (ret)
			break;
	}

	return ret;
}