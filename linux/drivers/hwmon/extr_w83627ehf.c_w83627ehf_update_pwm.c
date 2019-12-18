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
struct w83627ehf_data {int pwm_num; int has_fan; int* pwm_mode; int* pwm_enable; int* tolerance; int /*<<< orphan*/ * REG_PWM; void** pwm; } ;

/* Variables and functions */
 int* W83627EHF_PWM_ENABLE_SHIFT ; 
 int* W83627EHF_PWM_MODE_SHIFT ; 
 int /*<<< orphan*/ * W83627EHF_REG_PWM_ENABLE ; 
 int /*<<< orphan*/ * W83627EHF_REG_TOLERANCE ; 
 void* w83627ehf_read_value (struct w83627ehf_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void w83627ehf_update_pwm(struct w83627ehf_data *data)
{
	int i;
	int pwmcfg = 0, tolerance = 0; /* shut up the compiler */

	for (i = 0; i < data->pwm_num; i++) {
		if (!(data->has_fan & (1 << i)))
			continue;

		/* pwmcfg, tolerance mapped for i=0, i=1 to same reg */
		if (i != 1) {
			pwmcfg = w83627ehf_read_value(data,
					W83627EHF_REG_PWM_ENABLE[i]);
			tolerance = w83627ehf_read_value(data,
					W83627EHF_REG_TOLERANCE[i]);
		}
		data->pwm_mode[i] =
			((pwmcfg >> W83627EHF_PWM_MODE_SHIFT[i]) & 1) ? 0 : 1;
		data->pwm_enable[i] = ((pwmcfg >> W83627EHF_PWM_ENABLE_SHIFT[i])
				       & 3) + 1;
		data->pwm[i] = w83627ehf_read_value(data, data->REG_PWM[i]);

		data->tolerance[i] = (tolerance >> (i == 1 ? 4 : 0)) & 0x0f;
	}
}