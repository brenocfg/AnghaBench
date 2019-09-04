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
typedef  int u16 ;
struct w83627ehf_sio_data {scalar_t__ kind; } ;
struct w83627ehf_data {int valid; int in_num; int* in; int* in_min; int* in_max; int has_fan; int* REG_FAN; int* fan_div; int has_fan_min; int* fan_min; int* REG_FAN_MIN; int pwm_num; int* fan_start_output; int* REG_FAN_START_OUTPUT; int* fan_stop_output; int* REG_FAN_STOP_OUTPUT; int* fan_stop_time; int* REG_FAN_STOP_TIME; int* REG_FAN_MAX_OUTPUT; int* fan_max_output; int* REG_FAN_STEP_OUTPUT; int* fan_step_output; int* target_temp; int* REG_TARGET; int* pwm_mode; int have_temp; int have_temp_offset; int* temp_offset; int alarms; int caseopen; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; scalar_t__* reg_temp_hyst; void** temp_max_hyst; scalar_t__* reg_temp_over; void** temp_max; scalar_t__* reg_temp; void** temp; scalar_t__ has_fan_div; int /*<<< orphan*/  (* fan_from_reg ) (int,int) ;int /*<<< orphan*/ * rpm; scalar_t__ in6_skip; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int NUM_REG_TEMP ; 
 int W83627EHF_REG_ALARM1 ; 
 int W83627EHF_REG_ALARM2 ; 
 int W83627EHF_REG_ALARM3 ; 
 int W83627EHF_REG_CASEOPEN_DET ; 
 int W83627EHF_REG_IN (int) ; 
 int W83627EHF_REG_IN_MAX (int) ; 
 int W83627EHF_REG_IN_MIN (int) ; 
 int* W83627EHF_REG_TEMP_OFFSET ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct w83627ehf_data* dev_get_drvdata (struct device*) ; 
 struct w83627ehf_sio_data* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  div_from_reg (int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ nct6775 ; 
 int /*<<< orphan*/  stub1 (int,int) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 void* w83627ehf_read_temp (struct w83627ehf_data*,scalar_t__) ; 
 int w83627ehf_read_value (struct w83627ehf_data*,int) ; 
 int /*<<< orphan*/  w83627ehf_update_fan_div_common (struct device*,struct w83627ehf_data*) ; 
 int /*<<< orphan*/  w83627ehf_update_pwm_common (struct device*,struct w83627ehf_data*) ; 
 int /*<<< orphan*/  w83627ehf_write_fan_div_common (struct device*,struct w83627ehf_data*,int) ; 
 int /*<<< orphan*/  w83627ehf_write_value (struct w83627ehf_data*,int,int) ; 

__attribute__((used)) static struct w83627ehf_data *w83627ehf_update_device(struct device *dev)
{
	struct w83627ehf_data *data = dev_get_drvdata(dev);
	struct w83627ehf_sio_data *sio_data = dev_get_platdata(dev);

	int i;

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + HZ + HZ/2)
	 || !data->valid) {
		/* Fan clock dividers */
		w83627ehf_update_fan_div_common(dev, data);

		/* Measured voltages and limits */
		for (i = 0; i < data->in_num; i++) {
			if ((i == 6) && data->in6_skip)
				continue;

			data->in[i] = w83627ehf_read_value(data,
				      W83627EHF_REG_IN(i));
			data->in_min[i] = w83627ehf_read_value(data,
					  W83627EHF_REG_IN_MIN(i));
			data->in_max[i] = w83627ehf_read_value(data,
					  W83627EHF_REG_IN_MAX(i));
		}

		/* Measured fan speeds and limits */
		for (i = 0; i < 5; i++) {
			u16 reg;

			if (!(data->has_fan & (1 << i)))
				continue;

			reg = w83627ehf_read_value(data, data->REG_FAN[i]);
			data->rpm[i] = data->fan_from_reg(reg,
							  data->fan_div[i]);

			if (data->has_fan_min & (1 << i))
				data->fan_min[i] = w83627ehf_read_value(data,
					   data->REG_FAN_MIN[i]);

			/*
			 * If we failed to measure the fan speed and clock
			 * divider can be increased, let's try that for next
			 * time
			 */
			if (data->has_fan_div
			    && (reg >= 0xff || (sio_data->kind == nct6775
						&& reg == 0x00))
			    && data->fan_div[i] < 0x07) {
				dev_dbg(dev,
					"Increasing fan%d clock divider from %u to %u\n",
					i + 1, div_from_reg(data->fan_div[i]),
					div_from_reg(data->fan_div[i] + 1));
				data->fan_div[i]++;
				w83627ehf_write_fan_div_common(dev, data, i);
				/* Preserve min limit if possible */
				if ((data->has_fan_min & (1 << i))
				 && data->fan_min[i] >= 2
				 && data->fan_min[i] != 255)
					w83627ehf_write_value(data,
						data->REG_FAN_MIN[i],
						(data->fan_min[i] /= 2));
			}
		}

		w83627ehf_update_pwm_common(dev, data);

		for (i = 0; i < data->pwm_num; i++) {
			if (!(data->has_fan & (1 << i)))
				continue;

			data->fan_start_output[i] =
			  w83627ehf_read_value(data,
					       data->REG_FAN_START_OUTPUT[i]);
			data->fan_stop_output[i] =
			  w83627ehf_read_value(data,
					       data->REG_FAN_STOP_OUTPUT[i]);
			data->fan_stop_time[i] =
			  w83627ehf_read_value(data,
					       data->REG_FAN_STOP_TIME[i]);

			if (data->REG_FAN_MAX_OUTPUT &&
			    data->REG_FAN_MAX_OUTPUT[i] != 0xff)
				data->fan_max_output[i] =
				  w83627ehf_read_value(data,
						data->REG_FAN_MAX_OUTPUT[i]);

			if (data->REG_FAN_STEP_OUTPUT &&
			    data->REG_FAN_STEP_OUTPUT[i] != 0xff)
				data->fan_step_output[i] =
				  w83627ehf_read_value(data,
						data->REG_FAN_STEP_OUTPUT[i]);

			data->target_temp[i] =
				w83627ehf_read_value(data,
					data->REG_TARGET[i]) &
					(data->pwm_mode[i] == 1 ? 0x7f : 0xff);
		}

		/* Measured temperatures and limits */
		for (i = 0; i < NUM_REG_TEMP; i++) {
			if (!(data->have_temp & (1 << i)))
				continue;
			data->temp[i] = w83627ehf_read_temp(data,
						data->reg_temp[i]);
			if (data->reg_temp_over[i])
				data->temp_max[i]
				  = w83627ehf_read_temp(data,
						data->reg_temp_over[i]);
			if (data->reg_temp_hyst[i])
				data->temp_max_hyst[i]
				  = w83627ehf_read_temp(data,
						data->reg_temp_hyst[i]);
			if (i > 2)
				continue;
			if (data->have_temp_offset & (1 << i))
				data->temp_offset[i]
				  = w83627ehf_read_value(data,
						W83627EHF_REG_TEMP_OFFSET[i]);
		}

		data->alarms = w83627ehf_read_value(data,
					W83627EHF_REG_ALARM1) |
			       (w83627ehf_read_value(data,
					W83627EHF_REG_ALARM2) << 8) |
			       (w83627ehf_read_value(data,
					W83627EHF_REG_ALARM3) << 16);

		data->caseopen = w83627ehf_read_value(data,
						W83627EHF_REG_CASEOPEN_DET);

		data->last_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);
	return data;
}