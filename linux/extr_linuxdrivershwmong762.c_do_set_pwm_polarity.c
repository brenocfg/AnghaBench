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
struct g762_data {int valid; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  fan_cmd1; int /*<<< orphan*/  client; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  G762_PWM_POLARITY_NEGATIVE 129 
#define  G762_PWM_POLARITY_POSITIVE 128 
 int /*<<< orphan*/  G762_REG_FAN_CMD1 ; 
 int /*<<< orphan*/  G762_REG_FAN_CMD1_PWM_POLARITY ; 
 scalar_t__ IS_ERR (struct g762_data*) ; 
 int PTR_ERR (struct g762_data*) ; 
 struct g762_data* g762_update_client (struct device*) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_set_pwm_polarity(struct device *dev, unsigned long val)
{
	struct g762_data *data = g762_update_client(dev);
	int ret;

	if (IS_ERR(data))
		return PTR_ERR(data);

	mutex_lock(&data->update_lock);
	switch (val) {
	case G762_PWM_POLARITY_POSITIVE:
		data->fan_cmd1 &= ~G762_REG_FAN_CMD1_PWM_POLARITY;
		break;
	case G762_PWM_POLARITY_NEGATIVE:
		data->fan_cmd1 |=  G762_REG_FAN_CMD1_PWM_POLARITY;
		break;
	default:
		ret = -EINVAL;
		goto out;
	}
	ret = i2c_smbus_write_byte_data(data->client, G762_REG_FAN_CMD1,
					data->fan_cmd1);
	data->valid = false;
 out:
	mutex_unlock(&data->update_lock);

	return ret;
}