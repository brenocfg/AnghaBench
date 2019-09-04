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
struct smsc47m1_data {scalar_t__ type; int* fan; int* fan_preload; int* pwm; int* fan_div; int alarms; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  SMSC47M1_REG_ALARM ; 
 int /*<<< orphan*/ * SMSC47M1_REG_FAN ; 
 int /*<<< orphan*/  SMSC47M1_REG_FANDIV ; 
 int /*<<< orphan*/ * SMSC47M1_REG_FAN_PRELOAD ; 
 int /*<<< orphan*/ * SMSC47M1_REG_PWM ; 
 int /*<<< orphan*/  SMSC47M2_REG_ALARM6 ; 
 int /*<<< orphan*/  SMSC47M2_REG_FANDIV3 ; 
 struct smsc47m1_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int smsc47m1_read_value (struct smsc47m1_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc47m1_write_value (struct smsc47m1_data*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ smsc47m2 ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct smsc47m1_data *smsc47m1_update_device(struct device *dev,
		int init)
{
	struct smsc47m1_data *data = dev_get_drvdata(dev);

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + HZ + HZ / 2) || init) {
		int i, fan_nr;
		fan_nr = data->type == smsc47m2 ? 3 : 2;

		for (i = 0; i < fan_nr; i++) {
			data->fan[i] = smsc47m1_read_value(data,
				       SMSC47M1_REG_FAN[i]);
			data->fan_preload[i] = smsc47m1_read_value(data,
					       SMSC47M1_REG_FAN_PRELOAD[i]);
			data->pwm[i] = smsc47m1_read_value(data,
				       SMSC47M1_REG_PWM[i]);
		}

		i = smsc47m1_read_value(data, SMSC47M1_REG_FANDIV);
		data->fan_div[0] = (i >> 4) & 0x03;
		data->fan_div[1] = i >> 6;

		data->alarms = smsc47m1_read_value(data,
			       SMSC47M1_REG_ALARM) >> 6;
		/* Clear alarms if needed */
		if (data->alarms)
			smsc47m1_write_value(data, SMSC47M1_REG_ALARM, 0xC0);

		if (fan_nr >= 3) {
			data->fan_div[2] = (smsc47m1_read_value(data,
					    SMSC47M2_REG_FANDIV3) >> 4) & 0x03;
			data->alarms |= (smsc47m1_read_value(data,
					 SMSC47M2_REG_ALARM6) & 0x40) >> 4;
			/* Clear alarm if needed */
			if (data->alarms & 0x04)
				smsc47m1_write_value(data,
						     SMSC47M2_REG_ALARM6,
						     0x40);
		}

		data->last_updated = jiffies;
	}

	mutex_unlock(&data->update_lock);
	return data;
}