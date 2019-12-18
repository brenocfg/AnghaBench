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
struct nct6775_data {int pwm_num; int has_pwm; int* REG_PWM_MODE; int* PWM_MODE_MASK; int* pwm_mode; int* REG_FAN_MODE; int** REG_PWM; int** pwm; scalar_t__* pwm_enable; int** temp_tolerance; int* target_speed_tolerance; int* REG_TOLERANCE_H; int* REG_CRITICAL_TEMP_TOLERANCE; int* REG_TEMP_SEL; int* pwm_temp_sel; int* REG_WEIGHT_TEMP_SEL; int* pwm_weight_temp_sel; int** weight_temp; int** REG_WEIGHT_TEMP; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int**) ; 
 int BIT (int) ; 
 struct nct6775_data* dev_get_drvdata (struct device*) ; 
 int nct6775_read_value (struct nct6775_data*,int) ; 
 scalar_t__ reg_to_pwm_enable (int,int) ; 
 scalar_t__ speed_cruise ; 

__attribute__((used)) static void nct6775_update_pwm(struct device *dev)
{
	struct nct6775_data *data = dev_get_drvdata(dev);
	int i, j;
	int fanmodecfg, reg;
	bool duty_is_dc;

	for (i = 0; i < data->pwm_num; i++) {
		if (!(data->has_pwm & BIT(i)))
			continue;

		duty_is_dc = data->REG_PWM_MODE[i] &&
		  (nct6775_read_value(data, data->REG_PWM_MODE[i])
		   & data->PWM_MODE_MASK[i]);
		data->pwm_mode[i] = !duty_is_dc;

		fanmodecfg = nct6775_read_value(data, data->REG_FAN_MODE[i]);
		for (j = 0; j < ARRAY_SIZE(data->REG_PWM); j++) {
			if (data->REG_PWM[j] && data->REG_PWM[j][i]) {
				data->pwm[j][i]
				  = nct6775_read_value(data,
						       data->REG_PWM[j][i]);
			}
		}

		data->pwm_enable[i] = reg_to_pwm_enable(data->pwm[0][i],
							(fanmodecfg >> 4) & 7);

		if (!data->temp_tolerance[0][i] ||
		    data->pwm_enable[i] != speed_cruise)
			data->temp_tolerance[0][i] = fanmodecfg & 0x0f;
		if (!data->target_speed_tolerance[i] ||
		    data->pwm_enable[i] == speed_cruise) {
			u8 t = fanmodecfg & 0x0f;

			if (data->REG_TOLERANCE_H) {
				t |= (nct6775_read_value(data,
				      data->REG_TOLERANCE_H[i]) & 0x70) >> 1;
			}
			data->target_speed_tolerance[i] = t;
		}

		data->temp_tolerance[1][i] =
			nct6775_read_value(data,
					data->REG_CRITICAL_TEMP_TOLERANCE[i]);

		reg = nct6775_read_value(data, data->REG_TEMP_SEL[i]);
		data->pwm_temp_sel[i] = reg & 0x1f;
		/* If fan can stop, report floor as 0 */
		if (reg & 0x80)
			data->pwm[2][i] = 0;

		if (!data->REG_WEIGHT_TEMP_SEL[i])
			continue;

		reg = nct6775_read_value(data, data->REG_WEIGHT_TEMP_SEL[i]);
		data->pwm_weight_temp_sel[i] = reg & 0x1f;
		/* If weight is disabled, report weight source as 0 */
		if (!(reg & 0x80))
			data->pwm_weight_temp_sel[i] = 0;

		/* Weight temp data */
		for (j = 0; j < ARRAY_SIZE(data->weight_temp); j++) {
			data->weight_temp[j][i]
			  = nct6775_read_value(data,
					       data->REG_WEIGHT_TEMP[j][i]);
		}
	}
}