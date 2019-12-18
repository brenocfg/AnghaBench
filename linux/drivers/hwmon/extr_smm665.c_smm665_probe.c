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
struct smm665_data {int type; struct i2c_client* cmdreg; void** alarm_max_limit; void** critical_max_limit; void** alarm_min_limit; void** critical_min_limit; int /*<<< orphan*/  conversion_time; struct i2c_client* client; int /*<<< orphan*/  update_lock; } ;
struct i2c_device_id {int driver_data; } ;
struct i2c_client {int addr; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int dummy; } ;
struct device {int addr; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; struct i2c_adapter* adapter; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_FUNC_SMBUS_BYTE_DATA ; 
 int I2C_FUNC_SMBUS_WORD_DATA ; 
 scalar_t__ IS_ERR (struct i2c_client*) ; 
 int PTR_ERR (struct i2c_client*) ; 
 int /*<<< orphan*/  SMM665_ADC_WAIT_SMM665 ; 
 int /*<<< orphan*/  SMM665_ADC_WAIT_SMM766 ; 
 int /*<<< orphan*/  SMM665_ADOC_ENABLE ; 
 int SMM665_CMDREG_BASE ; 
 scalar_t__ SMM665_LIMIT_BASE ; 
 int /*<<< orphan*/  SMM665_MISC8_CMD_STS ; 
 int SMM665_NUM_ADC ; 
 int SMM665_REGMASK ; 
 struct i2c_client* devm_hwmon_device_register_with_groups (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct smm665_data*,int /*<<< orphan*/ ) ; 
 struct smm665_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int) ; 
 struct i2c_client* i2c_new_dummy_device (struct i2c_adapter*,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct smm665_data*) ; 
 scalar_t__ i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_unregister_device (struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
#define  smm465 132 
#define  smm665 131 
 void* smm665_convert (int,int) ; 
 int /*<<< orphan*/  smm665_groups ; 
 scalar_t__ smm665_is_critical (int) ; 
 int smm665_read16 (struct i2c_client*,scalar_t__) ; 
#define  smm665c 130 
#define  smm764 129 
#define  smm766 128 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int smm665_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct i2c_adapter *adapter = client->adapter;
	struct smm665_data *data;
	struct device *hwmon_dev;
	int i, ret;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA
				     | I2C_FUNC_SMBUS_WORD_DATA))
		return -ENODEV;

	if (i2c_smbus_read_byte_data(client, SMM665_ADOC_ENABLE) < 0)
		return -ENODEV;

	data = devm_kzalloc(&client->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);

	data->client = client;
	data->type = id->driver_data;
	data->cmdreg = i2c_new_dummy_device(adapter, (client->addr & ~SMM665_REGMASK)
				     | SMM665_CMDREG_BASE);
	if (IS_ERR(data->cmdreg))
		return PTR_ERR(data->cmdreg);

	switch (data->type) {
	case smm465:
	case smm665:
		data->conversion_time = SMM665_ADC_WAIT_SMM665;
		break;
	case smm665c:
	case smm764:
	case smm766:
		data->conversion_time = SMM665_ADC_WAIT_SMM766;
		break;
	}

	ret = -ENODEV;
	if (i2c_smbus_read_byte_data(data->cmdreg, SMM665_MISC8_CMD_STS) < 0)
		goto out_unregister;

	/*
	 * Read limits.
	 *
	 * Limit registers start with register SMM665_LIMIT_BASE.
	 * Each channel uses 8 registers, providing four limit values
	 * per channel. Each limit value requires two registers, with the
	 * high byte in the first register and the low byte in the second
	 * register. The first two limits are under limit values, followed
	 * by two over limit values.
	 *
	 * Limit register order matches the ADC register order, so we use
	 * ADC register defines throughout the code to index limit registers.
	 *
	 * We save the first retrieved value both as "critical" and "alarm"
	 * value. The second value overwrites either the critical or the
	 * alarm value, depending on its configuration. This ensures that both
	 * critical and alarm values are initialized, even if both registers are
	 * configured as critical or non-critical.
	 */
	for (i = 0; i < SMM665_NUM_ADC; i++) {
		int val;

		val = smm665_read16(client, SMM665_LIMIT_BASE + i * 8);
		if (unlikely(val < 0))
			goto out_unregister;
		data->critical_min_limit[i] = data->alarm_min_limit[i]
		  = smm665_convert(val, i);
		val = smm665_read16(client, SMM665_LIMIT_BASE + i * 8 + 2);
		if (unlikely(val < 0))
			goto out_unregister;
		if (smm665_is_critical(val))
			data->critical_min_limit[i] = smm665_convert(val, i);
		else
			data->alarm_min_limit[i] = smm665_convert(val, i);
		val = smm665_read16(client, SMM665_LIMIT_BASE + i * 8 + 4);
		if (unlikely(val < 0))
			goto out_unregister;
		data->critical_max_limit[i] = data->alarm_max_limit[i]
		  = smm665_convert(val, i);
		val = smm665_read16(client, SMM665_LIMIT_BASE + i * 8 + 6);
		if (unlikely(val < 0))
			goto out_unregister;
		if (smm665_is_critical(val))
			data->critical_max_limit[i] = smm665_convert(val, i);
		else
			data->alarm_max_limit[i] = smm665_convert(val, i);
	}

	hwmon_dev = devm_hwmon_device_register_with_groups(&client->dev,
							   client->name, data,
							   smm665_groups);
	if (IS_ERR(hwmon_dev)) {
		ret = PTR_ERR(hwmon_dev);
		goto out_unregister;
	}

	return 0;

out_unregister:
	i2c_unregister_device(data->cmdreg);
	return ret;
}