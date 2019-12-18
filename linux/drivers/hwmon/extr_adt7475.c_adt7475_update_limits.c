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
struct i2c_client {int dummy; } ;
struct adt7475_data {int config4; int config5; int has_voltage; int** voltage; int** temp; int** tach; int** pwm; int* range; int /*<<< orphan*/  has_pwm2; int /*<<< orphan*/  has_fan4; } ;

/* Variables and functions */
 int ADT7475_PWM_COUNT ; 
 int ADT7475_TACH_COUNT ; 
 int ADT7475_TEMP_COUNT ; 
 int ADT7475_VOLTAGE_COUNT ; 
 size_t AUTOMIN ; 
 size_t MAX ; 
 size_t MIN ; 
 size_t OFFSET ; 
 int /*<<< orphan*/  PWM_MAX_REG (int) ; 
 int /*<<< orphan*/  PWM_MIN_REG (int) ; 
 int /*<<< orphan*/  REG_CONFIG4 ; 
 int /*<<< orphan*/  REG_CONFIG5 ; 
 int /*<<< orphan*/  REG_VTT_MAX ; 
 int /*<<< orphan*/  REG_VTT_MIN ; 
 int /*<<< orphan*/  TACH_MIN_REG (int) ; 
 int /*<<< orphan*/  TEMP_MAX_REG (int) ; 
 int /*<<< orphan*/  TEMP_MIN_REG (int) ; 
 int /*<<< orphan*/  TEMP_OFFSET_REG (int) ; 
 int /*<<< orphan*/  TEMP_THERM_REG (int) ; 
 int /*<<< orphan*/  TEMP_TMIN_REG (int) ; 
 int /*<<< orphan*/  TEMP_TRANGE_REG (int) ; 
 size_t THERM ; 
 int /*<<< orphan*/  VOLTAGE_MAX_REG (int) ; 
 int /*<<< orphan*/  VOLTAGE_MIN_REG (int) ; 
 int adt7475_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adt7475_read_hystersis (struct i2c_client*) ; 
 int /*<<< orphan*/  adt7475_read_pwm (struct i2c_client*,int) ; 
 int adt7475_read_word (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct adt7475_data* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static int adt7475_update_limits(struct i2c_client *client)
{
	struct adt7475_data *data = i2c_get_clientdata(client);
	int i;
	int ret;

	ret = adt7475_read(REG_CONFIG4);
	if (ret < 0)
		return ret;
	data->config4 = ret;

	ret = adt7475_read(REG_CONFIG5);
	if (ret < 0)
		return ret;
	data->config5 = ret;

	for (i = 0; i < ADT7475_VOLTAGE_COUNT; i++) {
		if (!(data->has_voltage & (1 << i)))
			continue;
		/* Adjust values so they match the input precision */
		ret = adt7475_read(VOLTAGE_MIN_REG(i));
		if (ret < 0)
			return ret;
		data->voltage[MIN][i] = ret << 2;

		ret = adt7475_read(VOLTAGE_MAX_REG(i));
		if (ret < 0)
			return ret;
		data->voltage[MAX][i] = ret << 2;
	}

	if (data->has_voltage & (1 << 5)) {
		ret = adt7475_read(REG_VTT_MIN);
		if (ret < 0)
			return ret;
		data->voltage[MIN][5] = ret << 2;

		ret = adt7475_read(REG_VTT_MAX);
		if (ret < 0)
			return ret;
		data->voltage[MAX][5] = ret << 2;
	}

	for (i = 0; i < ADT7475_TEMP_COUNT; i++) {
		/* Adjust values so they match the input precision */
		ret = adt7475_read(TEMP_MIN_REG(i));
		if (ret < 0)
			return ret;
		data->temp[MIN][i] = ret << 2;

		ret = adt7475_read(TEMP_MAX_REG(i));
		if (ret < 0)
			return ret;
		data->temp[MAX][i] = ret << 2;

		ret = adt7475_read(TEMP_TMIN_REG(i));
		if (ret < 0)
			return ret;
		data->temp[AUTOMIN][i] = ret << 2;

		ret = adt7475_read(TEMP_THERM_REG(i));
		if (ret < 0)
			return ret;
		data->temp[THERM][i] = ret << 2;

		ret = adt7475_read(TEMP_OFFSET_REG(i));
		if (ret < 0)
			return ret;
		data->temp[OFFSET][i] = ret;
	}
	adt7475_read_hystersis(client);

	for (i = 0; i < ADT7475_TACH_COUNT; i++) {
		if (i == 3 && !data->has_fan4)
			continue;
		ret = adt7475_read_word(client, TACH_MIN_REG(i));
		if (ret < 0)
			return ret;
		data->tach[MIN][i] = ret;
	}

	for (i = 0; i < ADT7475_PWM_COUNT; i++) {
		if (i == 1 && !data->has_pwm2)
			continue;
		ret = adt7475_read(PWM_MAX_REG(i));
		if (ret < 0)
			return ret;
		data->pwm[MAX][i] = ret;

		ret = adt7475_read(PWM_MIN_REG(i));
		if (ret < 0)
			return ret;
		data->pwm[MIN][i] = ret;
		/* Set the channel and control information */
		adt7475_read_pwm(client, i);
	}

	ret = adt7475_read(TEMP_TRANGE_REG(0));
	if (ret < 0)
		return ret;
	data->range[0] = ret;

	ret = adt7475_read(TEMP_TRANGE_REG(1));
	if (ret < 0)
		return ret;
	data->range[1] = ret;

	ret = adt7475_read(TEMP_TRANGE_REG(2));
	if (ret < 0)
		return ret;
	data->range[2] = ret;

	return 0;
}