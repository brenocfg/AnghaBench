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
typedef  int u16 ;
struct nct6775_data {int pwm_num; int has_pwm; int** fan_time; int* target_temp; scalar_t__* pwm_enable; int target_temp_mask; int* target_speed; int auto_pwm_num; int** auto_pwm; int** auto_temp; int kind; int CRITICAL_PWM_ENABLE_MASK; int /*<<< orphan*/ * REG_CRITICAL_PWM; int /*<<< orphan*/ * REG_CRITICAL_PWM_ENABLE; int /*<<< orphan*/ * REG_CRITICAL_TEMP; int /*<<< orphan*/ * REG_TOLERANCE_H; int /*<<< orphan*/ * REG_TARGET; int /*<<< orphan*/ ** REG_FAN_TIME; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int**) ; 
 int BIT (int) ; 
 int /*<<< orphan*/  NCT6775_AUTO_PWM (struct nct6775_data*,int,int) ; 
 int /*<<< orphan*/  NCT6775_AUTO_TEMP (struct nct6775_data*,int,int) ; 
 int /*<<< orphan*/ * NCT6775_REG_CRITICAL_ENAB ; 
 struct nct6775_data* dev_get_drvdata (struct device*) ; 
#define  nct6106 139 
#define  nct6116 138 
#define  nct6775 137 
 int nct6775_read_value (struct nct6775_data*,int /*<<< orphan*/ ) ; 
#define  nct6776 136 
#define  nct6779 135 
#define  nct6791 134 
#define  nct6792 133 
#define  nct6793 132 
#define  nct6795 131 
#define  nct6796 130 
#define  nct6797 129 
#define  nct6798 128 
 scalar_t__ speed_cruise ; 
 scalar_t__ thermal_cruise ; 

__attribute__((used)) static void nct6775_update_pwm_limits(struct device *dev)
{
	struct nct6775_data *data = dev_get_drvdata(dev);
	int i, j;
	u8 reg;
	u16 reg_t;

	for (i = 0; i < data->pwm_num; i++) {
		if (!(data->has_pwm & BIT(i)))
			continue;

		for (j = 0; j < ARRAY_SIZE(data->fan_time); j++) {
			data->fan_time[j][i] =
			  nct6775_read_value(data, data->REG_FAN_TIME[j][i]);
		}

		reg_t = nct6775_read_value(data, data->REG_TARGET[i]);
		/* Update only in matching mode or if never updated */
		if (!data->target_temp[i] ||
		    data->pwm_enable[i] == thermal_cruise)
			data->target_temp[i] = reg_t & data->target_temp_mask;
		if (!data->target_speed[i] ||
		    data->pwm_enable[i] == speed_cruise) {
			if (data->REG_TOLERANCE_H) {
				reg_t |= (nct6775_read_value(data,
					data->REG_TOLERANCE_H[i]) & 0x0f) << 8;
			}
			data->target_speed[i] = reg_t;
		}

		for (j = 0; j < data->auto_pwm_num; j++) {
			data->auto_pwm[i][j] =
			  nct6775_read_value(data,
					     NCT6775_AUTO_PWM(data, i, j));
			data->auto_temp[i][j] =
			  nct6775_read_value(data,
					     NCT6775_AUTO_TEMP(data, i, j));
		}

		/* critical auto_pwm temperature data */
		data->auto_temp[i][data->auto_pwm_num] =
			nct6775_read_value(data, data->REG_CRITICAL_TEMP[i]);

		switch (data->kind) {
		case nct6775:
			reg = nct6775_read_value(data,
						 NCT6775_REG_CRITICAL_ENAB[i]);
			data->auto_pwm[i][data->auto_pwm_num] =
						(reg & 0x02) ? 0xff : 0x00;
			break;
		case nct6776:
			data->auto_pwm[i][data->auto_pwm_num] = 0xff;
			break;
		case nct6106:
		case nct6116:
		case nct6779:
		case nct6791:
		case nct6792:
		case nct6793:
		case nct6795:
		case nct6796:
		case nct6797:
		case nct6798:
			reg = nct6775_read_value(data,
					data->REG_CRITICAL_PWM_ENABLE[i]);
			if (reg & data->CRITICAL_PWM_ENABLE_MASK)
				reg = nct6775_read_value(data,
					data->REG_CRITICAL_PWM[i]);
			else
				reg = 0xff;
			data->auto_pwm[i][data->auto_pwm_num] = reg;
			break;
		}
	}
}