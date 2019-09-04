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
typedef  int /*<<< orphan*/  u8 ;
struct lm93_data {int /*<<< orphan*/  block1; void* sf_tach_to_pwm; void* sfc2; void* sfc1; void* pwm_ramp_ctl; void** auto_pwm_min_hyst; void** boost_hyst; void** boost; void* prochot_interval; void* prochot_override; void* gpi; void** vccp_limits; void** prochot_max; void** vid; void* config; TYPE_1__* temp_lim; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {void* max; void* min; } ;

/* Variables and functions */
 int /*<<< orphan*/  LM93_REG_BOOST (int) ; 
 int /*<<< orphan*/  LM93_REG_BOOST_HYST_12 ; 
 int /*<<< orphan*/  LM93_REG_BOOST_HYST_34 ; 
 int /*<<< orphan*/  LM93_REG_CONFIG ; 
 int /*<<< orphan*/  LM93_REG_GPI ; 
 scalar_t__ LM93_REG_HOST_ERROR_1 ; 
 int /*<<< orphan*/  LM93_REG_PROCHOT_INTERVAL ; 
 int /*<<< orphan*/  LM93_REG_PROCHOT_MAX (int) ; 
 int /*<<< orphan*/  LM93_REG_PROCHOT_OVERRIDE ; 
 int /*<<< orphan*/  LM93_REG_PWM_MIN_HYST_12 ; 
 int /*<<< orphan*/  LM93_REG_PWM_MIN_HYST_34 ; 
 int /*<<< orphan*/  LM93_REG_PWM_RAMP_CTL ; 
 int /*<<< orphan*/  LM93_REG_SFC1 ; 
 int /*<<< orphan*/  LM93_REG_SFC2 ; 
 int /*<<< orphan*/  LM93_REG_SF_TACH_TO_PWM ; 
 int /*<<< orphan*/  LM93_REG_TEMP_MAX (int) ; 
 int /*<<< orphan*/  LM93_REG_TEMP_MIN (int) ; 
 int /*<<< orphan*/  LM93_REG_VCCP_LIMIT_OFF (int) ; 
 int /*<<< orphan*/  LM93_REG_VID (int) ; 
 void* lm93_read_byte (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lm93_write_byte (struct i2c_client*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lm93_update_client_common(struct lm93_data *data,
				      struct i2c_client *client)
{
	int i;
	u8 *ptr;

	/* temp1 - temp4: limits */
	for (i = 0; i < 4; i++) {
		data->temp_lim[i].min =
			lm93_read_byte(client, LM93_REG_TEMP_MIN(i));
		data->temp_lim[i].max =
			lm93_read_byte(client, LM93_REG_TEMP_MAX(i));
	}

	/* config register */
	data->config = lm93_read_byte(client, LM93_REG_CONFIG);

	/* vid1 - vid2: values */
	for (i = 0; i < 2; i++)
		data->vid[i] = lm93_read_byte(client, LM93_REG_VID(i));

	/* prochot1 - prochot2: limits */
	for (i = 0; i < 2; i++)
		data->prochot_max[i] = lm93_read_byte(client,
				LM93_REG_PROCHOT_MAX(i));

	/* vccp1 - vccp2: VID relative limits */
	for (i = 0; i < 2; i++)
		data->vccp_limits[i] = lm93_read_byte(client,
				LM93_REG_VCCP_LIMIT_OFF(i));

	/* GPIO input state */
	data->gpi = lm93_read_byte(client, LM93_REG_GPI);

	/* #PROCHOT override state */
	data->prochot_override = lm93_read_byte(client,
			LM93_REG_PROCHOT_OVERRIDE);

	/* #PROCHOT intervals */
	data->prochot_interval = lm93_read_byte(client,
			LM93_REG_PROCHOT_INTERVAL);

	/* Fan Boost Temperature registers */
	for (i = 0; i < 4; i++)
		data->boost[i] = lm93_read_byte(client, LM93_REG_BOOST(i));

	/* Fan Boost Temperature Hyst. registers */
	data->boost_hyst[0] = lm93_read_byte(client, LM93_REG_BOOST_HYST_12);
	data->boost_hyst[1] = lm93_read_byte(client, LM93_REG_BOOST_HYST_34);

	/* Temperature Zone Min. PWM & Hysteresis registers */
	data->auto_pwm_min_hyst[0] =
			lm93_read_byte(client, LM93_REG_PWM_MIN_HYST_12);
	data->auto_pwm_min_hyst[1] =
			lm93_read_byte(client, LM93_REG_PWM_MIN_HYST_34);

	/* #PROCHOT & #VRDHOT PWM Ramp Control register */
	data->pwm_ramp_ctl = lm93_read_byte(client, LM93_REG_PWM_RAMP_CTL);

	/* misc setup registers */
	data->sfc1 = lm93_read_byte(client, LM93_REG_SFC1);
	data->sfc2 = lm93_read_byte(client, LM93_REG_SFC2);
	data->sf_tach_to_pwm = lm93_read_byte(client,
			LM93_REG_SF_TACH_TO_PWM);

	/* write back alarm values to clear */
	for (i = 0, ptr = (u8 *)(&data->block1); i < 8; i++)
		lm93_write_byte(client, LM93_REG_HOST_ERROR_1 + i, *(ptr + i));
}